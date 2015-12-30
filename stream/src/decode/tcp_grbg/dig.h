/* dig.h
 * Part of tcp_grbg dissector
 * Author:pangyemeng
 */


#ifndef __DIG_H__
#define __DIG_H__

#include "etypes.h"
#include "tcp_garbage.h"
#include "packet.h"


#define TCP_GRB_FILE_EXT_SIZE   10
#define TG_MULTI_END_NUM        10

typedef struct _dig_file_t dig_file;
struct _dig_file_t {
    char ename[TCP_GRB_FILE_EXT_SIZE];  /* file type, its extension */
    unsigned long msize;    /* max size */           
    bool sreg;              /* regular expression */
    char *starttxt;
    char *start;
    unsigned short slen;
    bool ereg;              /* regular expression */
    char *endtxt;
    char *end;
    bool stend;             /* the start condiction can complete the file */
    unsigned short elen;
    short end_id[TG_MULTI_END_NUM];      /* id to find the end -1 => no id */
};


typedef struct _dig_t dig;
struct _dig_t {
    dig_file *ft;        /* file type    */
    unsigned short fs;   /* search fase  */
    bool head;           /* head found   */
    int dig_sync;        /* id match */
    packet *pkt;         /* pkt in srch active fase */
    unsigned int pkt_offset;  /* pkt offset in srch active fase */
    char filename[TCP_GRB_FILENAME_PATH_SIZE];   /* file name */
    FILE *fp;            /* file */
    unsigned long fsize; /* file size */
    unsigned long serial;/* serial number of packet (will be used in PEI) */
    time_t start_cap;    /* first packet */
    time_t end_cap;      /* last packet */
};

#endif  /* __DIG_H__ */



