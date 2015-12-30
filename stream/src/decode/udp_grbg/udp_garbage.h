/* udp_garbage.h
 * Dissector to group together packet of udp flow that haven't a specific dissector
 * Author: pangyemeng
 */

#include <sys/types.h>

#ifndef __UDP_GARBAGE_H__
#define __UDP_GARBAGE_H__

/* threshold limit */
#define UDP_GRB_PERCENTAGE              80

/* path & buffer size */
#define UDP_GRB_THRESHOLD               (10*1024)
#define UDP_GRB_FILENAME_PATH_SIZE      256

/* packets limit for dependency */
#define UDP_GRB_PKT_LIMIT               50
#define UDP_GRB_PKT_LIMIT_CFG           "UDP_GRB_PKT_LIMIT"


typedef struct _ugrb_priv ugrb_priv;
struct _ugrb_priv {
    bool port_diff;         /* connection with different port */
    bool ipv6;              /* ipv6 or ipv4 */
    ftval ip_s;             /* ip source */
    ftval ip_d;             /* ip destination */
    unsigned short port_s;  /* source port */
    unsigned short port_d;  /* destination port */
    const pstack_f *stack;  /* protocol stack */
};

#endif /* __UDP_GARBAGE_H__ */
