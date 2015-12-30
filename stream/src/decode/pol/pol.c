/* pol.c
 * POL (point of listen)  dissector
 * Author: pangyemeng
 */

#include <stdio.h>
#include <pcap.h>
#include <string.h>

#include "proto.h"
#include "dmemory.h"
#include "etypes.h"

static int prot_id;
static int layer1_id;
static int count_id;
static int offset_id;
static int file_id;
static int ses_id;
static int pol_id;


static packet* PolDissector(packet *pkt)
{
    pstack_f *frame;
    ftval val;
    int len, offset;

    offset = 0;

    /* new frame */
    frame = ProtCreateFrame(prot_id);
    ProtSetNxtFrame(frame, pkt->stk);
    pkt->stk = frame;
    
    /* set attribute */
    val.uint32 = *((unsigned long *)&(pkt->raw[pkt->raw_len]));
    ProtInsAttr(frame, layer1_id, &val);
    offset += sizeof(unsigned long);

    val.uint32 = *((unsigned long *)&(pkt->raw[pkt->raw_len+offset]));
    ProtInsAttr(frame, count_id, &val);
    offset += sizeof(unsigned long);

    len = strlen(*(char **)&(pkt->raw[pkt->raw_len+offset]))+1;
    val.str = DMemMalloc(len);
    strcpy(val.str, *(char **)&(pkt->raw[pkt->raw_len+offset]));
    ProtInsAttr(frame, file_id, &val);
    DMemFree(val.str);
    offset += sizeof(char *);

    val.uint32 = *((unsigned long *)&(pkt->raw[pkt->raw_len+offset]));
    ProtInsAttr(frame, ses_id, &val);
    offset += sizeof(unsigned long);

    val.uint32 = *((unsigned long *)&(pkt->raw[pkt->raw_len+offset]));
    ProtInsAttr(frame, pol_id, &val);
    offset += sizeof(unsigned long);
    /* null terminating */
    pkt->raw[pkt->raw_len] = '\0';

    val.size = *((size_t *)&(pkt->raw[pkt->raw_len+offset]));
    ProtInsAttr(frame, offset_id, &val);

    /* pdu */
    pkt->dat_base = pkt->raw;
    pkt->data = pkt->raw;
    pkt->len = pkt->raw_len;

    return pkt;
}


int DissecRegist(const char *file_cfg)
{
    proto_info info;
    proto_dep dep;

    memset(&info, 0, sizeof(proto_info));
    memset(&dep, 0, sizeof(proto_dep));

    /* protocol name */
    ProtName("Point of Listen", "pol");
    
    /* Physical Layer */
    info.name = "Physical Layer";
    info.abbrev = "pol.layer1";
    info.type = FT_UINT16;
    layer1_id = ProtInfo(&info);

    /* Packet counter */
    info.name = "Packet number";
    info.abbrev = "pol.count";
    info.type = FT_UINT32;
    count_id = ProtInfo(&info);

    /* Packet offset */
    info.name = "Packet offset";
    info.abbrev = "pol.offset";
    info.type = FT_SIZE;
    offset_id = ProtInfo(&info);

    /* File name */
    info.name = "File name";
    info.abbrev = "pol.file";
    info.type = FT_STRING;
    file_id = ProtInfo(&info);

    /* session id */
    info.name = "Session id";
    info.abbrev = "pol.sesid";
    info.type = FT_UINT32;
    ses_id = ProtInfo(&info);

    /* point of view id */
    info.name = "Pol id";
    info.abbrev = "pol.polid";
    info.type = FT_UINT32;
    pol_id = ProtInfo(&info);

    /* dissectors registration */
    ProtDissectors(PolDissector, NULL, NULL, NULL);

    return 0;
}


int DissectInit(void)
{
    /* protocol id */
    prot_id = ProtId("pol");
    
    return 0;
}
