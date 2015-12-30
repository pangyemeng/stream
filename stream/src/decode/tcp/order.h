/* order.h
 * structures to support tcp order packets
 *
 * author: pangyemeng
 */


#ifndef __ORDER_H__
#define __ORDER_H__

#include "packet.h"
#include "configs.h"

#define TCP_SUBDIS_MONO_PKT_LIMIT  80 /* limit of queue in monodirectiona stream */
#define TCP_SUBDIS_MONO_PKT_MARG   40 /* ack margin in mono stream */


struct seq {
    packet *pkt;            /* packet */
    unsigned long seq;      /* seq order */
    unsigned long nxt_seq;  /* next in seq order */
    struct seq *next;       /* next in seq order */
    bool ack;               /* acknowled */
    bool cng;               /* time sequence */
};


/** data to order a tcp stream */
typedef struct _order order;
struct _order {
    bool port_diff;       /* different src and dst port */
    unsigned short port;  /* source port */
    bool ipv6;            /* ipv6 or ipv4 */
    ftval ip;             /* ip source */
#if SNIFFER_EVASION
    bool first;           /* first packet */
    bool hl_s_on;         /* enabled ttl check */
    ftval ttl_hl_s;       /* time to live or hop limit from src to dst*/
    ftval id_s1;          /* ip identification src */
    ftval id_s2;          /* ip identification src */
    ftval id_d1;          /* ip identification dst */
    ftval id_d2;          /* ip identification dst */
#endif
    bool src_put;         /* queue in put */
    unsigned long seq_s;  /* last seq source sent to flow */
    unsigned long seq_d;  /* last seq destination sent to flow */
    bool mono;            /* stream monodirectional */
    struct seq *src;      /* source packet list ordered */
    struct seq *dst;      /* destination packet list ordered */
    unsigned long num;    /* number of packet in queues */
    unsigned long fin_s;  /* seq fin source */
    unsigned long fin_d;  /* seq fin destination */
    bool rst;             /* reset */
    struct seq *last_src; /* last in src queue inserted */
    struct seq *last_dst; /* last in dst queue inserted */
    bool lins_src;        /* last in the queue inserd type */
    pstack_f *stk_s;      /* stack frame src */
    pstack_f *stk_d;      /* stack frame dst */
    packet *ack_d;        /* last dst ack packet */
    packet *ack_s;        /* last src ack packet */
};


#endif /* __ORDER_H__ */
