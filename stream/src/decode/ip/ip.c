/* ip.c
 * IP dissector
 * author: pangyemeng
 */

#include <pcap.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>

#include "proto.h"
#include "version.h"
#include "dmemory.h"
#include "etypes.h"
#include "ppptypes.h"
#include "in_cksum.h"
#include "log.h"
#include "embedded.h"
#include "configs.h"
#include "ipproto.h"
#include "bsdaftps.h"

#define GTP_MSG_TPDU                0xFF

/* info id */
static int iphdr_len;
static int prot_id;
static int ipv6_id;
static int proto_id;
static int src_id;
static int dst_id;
static int offset_id;
#if SNIFFER_EVASION
static int ttl_id;
static int id_id;
#endif

#ifdef XPL_X86
/*
 *	This is a version of ip_compute_csum() optimized for IP headers,
 *	which always checksum on 4 octet boundaries.
 *
 *	By Jorge Cwik <jorge@laser.satlink.net>, adapted for linux by
 *	Arnt Gulbrandsen.
 */
static inline unsigned short ip_fast_csum(unsigned char * iph,
					  unsigned int ihl)
{
	unsigned int sum;

	__asm__ __volatile__(
	    "movl (%1), %0	;\n"
	    "subl $4, %2	;\n"
	    "jbe 2f		;\n"
	    "addl 4(%1), %0	;\n"
	    "adcl 8(%1), %0	;\n"
	    "adcl 12(%1), %0	;\n"
"1:	    adcl 16(%1), %0	;\n"
	    "lea 4(%1), %1	;\n"
	    "decl %2		;\n"
	    "jne 1b		;\n"
	    "adcl $0, %0	;\n"
	    "movl %0, %2	;\n"
	    "shrl $16, %0	;\n"
	    "addw %w2, %w0	;\n"
	    "adcl $0, %0	;\n"
	    "notl %0		;\n"
"2:				;\n"
	/* Since the input registers which are loaded with iph and ihl
	   are modified, we must also specify them as outputs, or gcc
	   will assume they contain their original values. */
	: "=r" (sum), "=r" (iph), "=r" (ihl)
	: "1" (iph), "2" (ihl)
	: "memory");
	return(sum);
}
#else

static inline unsigned short ip_fast_csum(unsigned char *iph, unsigned int ihl)
{
    vec_t cksum_vec[1];
    
    cksum_vec[0].ptr = iph;
    cksum_vec[0].len = ihl << 2;
    return in_cksum(&cksum_vec[0], 1);
}

#endif /* XPL_X86 */


static packet* IpDissector(packet *pkt)
{
    pstack_f *frame;
    ftval val;
    struct iphdr *ip;
    unsigned short checksum_v;
    size_t iphdr_len;
    size_t ip_len;

    if (sizeof(struct iphdr) > pkt->len) {
        LogPrintf(LV_WARNING, "IP hedear packet dimension overflow the real dimension of packet");
        ProtStackFrmDisp(pkt->stk, TRUE);
        PktFree(pkt);
        return NULL;
    }

    ip = (struct iphdr *)pkt->data;
    /* IPv- or IPv4 */
    if (ip->version != 4) {
        if (ip->version == 6 && ipv6_id != -1)
            return ProtDissecPkt(ipv6_id, pkt);

        LogPrintf(LV_WARNING, "IP verision %i without dissector", ip->version);
        ProtStackFrmDisp(pkt->stk, TRUE);
        PktFree(pkt);
        return NULL;
    }
    /* IPv4 */
    iphdr_len = ip->ihl << 2;
    ip_len = ntohs(ip->tot_len);

    /* check consistence and checksum */
    if (ip_len > pkt->len) {
        //LogPrintf(LV_WARNING, "IP packet dimension overflow the real dimension of packet (%i>%i)", ip_len, pkt->len);
        LogPrintf(LV_WARNING, "IP packet dimension overflow the real dimension of packet");
        ProtStackFrmDisp(pkt->stk, TRUE);
        PktFree(pkt);
        return NULL;
    }

#if (XPL_DIS_IP_CHECKSUM == 0)
    if (ip_len <= iphdr_len) {
        LogPrintf(LV_WARNING, "Bogus IP length (%i, less than header length 20)", ip_len);
        ProtStackFrmDisp(pkt->stk, TRUE);
        PktFree(pkt);
        return NULL;
    }
    checksum_v = ip_fast_csum((unsigned char *)ip, ip->ihl);
    if (checksum_v != 0) {
        LogPrintf(LV_WARNING, "IP packet chechsum error (0x%x != 0x%x)", checksum_v, ip->check);
        //ProtStackFrmDisp(pkt->stk, TRUE);
        PktFree(pkt);
        return NULL;
    }
#else 
    if (ip_len <= iphdr_len) {
        ip_len = pkt->len;
    }
#endif
    
    /* fragment ip */
    if (ip->frag_off != 0 && ip->frag_off != 0x40) {
#warning only commercial version has ipv4 defragmentation!
        LogPrintf(LV_WARNING, "IP packet fragment contact g.costa@xplico.org");
        ProtStackFrmDisp(pkt->stk, TRUE);
        PktFree(pkt);
        return NULL;
    }

    /* new frame */
    frame = ProtCreateFrame(prot_id);
    ProtSetNxtFrame(frame, pkt->stk);
    pkt->stk = frame;

    /* set attributes */
    val.uint8 = ip->protocol;
    ProtInsAttr(frame, proto_id, &val);
#ifdef XPL_X86
    val.uint32 = ip->saddr;
#else
    val.uint32 = Emb32(&ip->saddr);
#endif
    ProtInsAttr(frame, src_id, &val);
#ifdef XPL_X86
    val.uint32 = ip->daddr;
#else
    val.uint32 = Emb32(&ip->daddr);
#endif
    ProtInsAttr(frame, dst_id, &val);
    if (pkt->raw != NULL)
        val.uint32 = (pkt->data - pkt->raw);
    else
        val.uint32 = 0;
    ProtInsAttr(frame, offset_id, &val);
#if SNIFFER_EVASION
    val.uint8 = ip->ttl;
    ProtInsAttr(frame, ttl_id, &val);
    val.uint16 = ntohs(ip->id);
    ProtInsAttr(frame, id_id, &val);
#endif

    /* pdu */
    pkt->data += iphdr_len;
    pkt->len = ip_len - iphdr_len;

    return pkt;
}


int DissecRegist(const char *file_cfg)
{
    proto_info info;
    proto_dep dep;

    memset(&info, 0, sizeof(proto_info));
    memset(&dep, 0, sizeof(proto_dep));

    /* protocol name */
    ProtName("Internet Protocol", "ip");
    
    /* protocol */
    info.name = "Protocol";
    info.abbrev = "ip.proto";
    info.type = FT_UINT8;
    proto_id = ProtInfo(&info);

    /* source */
    info.name = "Source";
    info.abbrev = "ip.src";
    info.type = FT_IPv4;
    src_id = ProtInfo(&info);

    /* destination */
    info.name = "Destination";
    info.abbrev = "ip.dst";
    info.type = FT_IPv4;
    dst_id = ProtInfo(&info);

    /* packet offset */
    info.name = "Packet Offset";
    info.abbrev = "ip.offset";
    info.type = FT_UINT32;
    offset_id = ProtInfo(&info);

#if SNIFFER_EVASION
    /* time to live */
    info.name = "Time To Live";
    info.abbrev = "ip.ttl";
    info.type = FT_UINT8;
    ttl_id = ProtInfo(&info);

    /* identification */
    info.name = "Identification";
    info.abbrev = "ip.id";
    info.type = FT_UINT16;
    id_id = ProtInfo(&info);
#endif

    /* ethernet dependence */
    dep.name = "eth";
    dep.attr = "eth.type";
    dep.type = FT_UINT16;
    dep.val.uint16 = ETHERTYPE_IP;
    ProtDep(&dep);

    /* llc dependence */
    dep.name = "llc";
    dep.attr = "llc.type";
    dep.type = FT_UINT16;
    dep.val.uint16 = ETHERTYPE_IP;
    ProtDep(&dep);

    /* sll dependence */
    dep.name = "sll";
    dep.attr = "sll.protocol";
    dep.type = FT_UINT16;
    dep.val.uint16 = ETHERTYPE_IP;
    ProtDep(&dep);

    /* ppp dependence */
    dep.name = "ppp";
    dep.attr = "ppp.protocol";
    dep.type = FT_UINT16;
    dep.val.uint16 = PPP_IP;
    ProtDep(&dep);

    dep.name = "ppp";
    dep.attr = "ppp.protocol";
    dep.type = FT_UINT16;
    dep.val.uint16 = ETHERTYPE_IP;
    ProtDep(&dep);

    /* pcapf dependence */
    dep.name = "pcapf";
    dep.attr = "pcapf.layer1";
    dep.type = FT_UINT16;
    dep.val.uint16 = DLT_RAW;
    ProtDep(&dep);
    dep.val.uint16 = DLT_IPV4;
    ProtDep(&dep);
    
    /* pol dependence */
    dep.name = "pol";
    dep.attr = "pol.layer1";
    dep.type = FT_UINT16;
    dep.val.uint16 = DLT_RAW;
    ProtDep(&dep);
    dep.val.uint16 = DLT_IPV4;
    ProtDep(&dep);
    
    /* ipv6 dependence */
    dep.name = "ipv6";
    dep.attr = "ipv6.nxt";
    dep.type = FT_UINT8;
    dep.val.uint8 = IP_PROTO_IPIP;
    ProtDep(&dep);

    /* vlan dependence */
    dep.name = "vlan";
    dep.attr = "vlan.type";
    dep.type = FT_UINT16;
    dep.val.uint16 = ETHERTYPE_IP;
    ProtDep(&dep);

    /* chdlc dependence */
    dep.name = "chdlc";
    dep.attr = "chdlc.protocol";
    dep.type = FT_UINT16;
    dep.val.uint16 = ETHERTYPE_IP;
    ProtDep(&dep);

    /* GTP dependence */
    dep.name = "gtp";
    dep.attr = "gtp.msg";
    dep.type = FT_UINT8;
    dep.val.uint8 = GTP_MSG_TPDU;
    ProtDep(&dep);
    
    /* udp dependence */
    dep.name = "null";
    dep.attr = "null.family";
    dep.type = FT_UINT32;
    dep.val.uint32 = BSD_AF_INET;
    ProtDep(&dep);
    
    dep.attr = "udp.dstport";
    ProtDep(&dep);
    
#if 0
    /* udp dependence */
    dep.name = "udp";
    dep.attr = "udp.srcport";
    dep.type = FT_UINT16;
    dep.val.uint16 = 34555;
    ProtDep(&dep);
    
    dep.attr = "udp.dstport";
    ProtDep(&dep);
#endif
    
    /* dissectors registration */
    ProtDissectors(IpDissector, NULL, NULL, NULL);

    return 0;
}


int DissectInit(void)
{
    prot_id = ProtId("ip");
    iphdr_len = sizeof(struct iphdr);
    ipv6_id = ProtId("ipv6");
    
    return 0;
}

