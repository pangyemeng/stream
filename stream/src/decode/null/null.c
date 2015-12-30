/* null.c
 * null packet dissector
 * Author: pangyemeng
 */

#include <pcap.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>

#include "proto.h"
#include "dmemory.h"
#include "etypes.h"
#include "log.h"
#include "configs.h"

/* info id */
static int prot_id;
static int family_id;

static packet* NullDissector(packet *pkt)
{
    pstack_f *frame;
    ftval val;
    unsigned int null_hdr;
    unsigned short len;

    /* check consistence */
    if (pkt->len < 4) {
        LogPrintf(LV_WARNING, "Null packet dimension overflow the real dimension of packet");
        //ProtStackFrmDisp(pkt->stk, TRUE);
        PktFree(pkt);
        return NULL;
    }

    /* check if there is PPP */
    if (ntohs(*((unsigned short *)pkt->data)) == 0xFF03) {
        LogPrintf(LV_WARNING, "Null packet contents is PPP (to develop)");
        return NULL;
    }
    len = sizeof(unsigned int);
    memcpy(&null_hdr, pkt->data, len);
    if ((null_hdr & 0xFFFF0000) != 0) {
        /* swap bytes */
#warning "to complete"
        return NULL;
    }

    if (null_hdr > IEEE_802_3_MAX_LEN) {
#warning "to complete"
        return NULL;
    }
    
    /* new frame */
    frame = ProtCreateFrame(prot_id);
    ProtSetNxtFrame(frame, pkt->stk);
    pkt->stk = frame;

    /* set attribute */
    val.uint32 = null_hdr;
    ProtInsAttr(frame, family_id, &val);

    /* pdu */
    pkt->data += len;
    pkt->len -= len;

    return pkt;
}


int DissecRegist(const char *file_cfg)
{
    proto_info info;
    proto_dep dep;

    memset(&info, 0, sizeof(proto_info));
    memset(&dep, 0, sizeof(proto_dep));
    family_id = -1;
    
    /* protocol name */
    ProtName("Null/Loopback", "null");
   
    /* protocol */
    info.name = "family type";
    info.abbrev = "null.family";
    info.type = FT_UINT32;
    family_id = ProtInfo(&info);

    /* pcapf dependence */
    dep.name = "pcapf";
    dep.attr = "pcapf.layer1";
    dep.type = FT_UINT16;
    dep.val.uint16 = DLT_NULL;
    ProtDep(&dep);

    /* pol dependence */
    dep.name = "pol";
    dep.attr = "pol.layer1";
    dep.type = FT_UINT16;
    dep.val.uint16 = DLT_NULL;
    ProtDep(&dep);

    /* dissectors registration */
    ProtDissectors(NullDissector, NULL, NULL, NULL);

    return 0;
}


int DissectInit(void)
{
    prot_id = ProtId("null");
    
    return 0;
}
