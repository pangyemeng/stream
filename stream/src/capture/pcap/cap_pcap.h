/* cap_pcap.h
 *
 * author: pangyemeng
 */


#ifndef __PCAP_DEF_H__
#define __PCAP_DEF_H__
#define PCAP_PATH_DIM          4096
#define PCAP_DEVICE            "/dev/hda1"
#define PCAP_PID_FILE          "/var/run/flow.pid"


struct pcap_ref {
    unsigned int dlt;
    unsigned long cnt;
    char *dev;
};

#endif /* __PCAP_DEF_H__ */
