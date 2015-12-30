/* pcap_gfile.h
 *
 * Author: pangyemeng
 */


/* "libpcap" record header. */
struct pcappkt_hdr {
    unsigned int tv_sec;      /* timestamp seconds */
    unsigned int tv_usec;     /* timestamp microseconds */
    unsigned int caplen;      /* number of octets of packet saved in file */
    unsigned int len;	      /* actual length of packet */
};
