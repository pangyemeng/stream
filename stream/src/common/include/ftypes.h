/* ftypes.h
 * Definitions for field types
 * author: pangyemeng
 */


#ifndef __FTYPES_H__
#define __FTYPES_H__

#include <unistd.h>

#define FT_ETH_LEN     6


/** field types */
enum ftype {
    FT_NONE,
    FT_UINT8,
    FT_UINT16,
    FT_UINT24,
    FT_UINT32,
    FT_UINT64,
    FT_INT8,
    FT_INT16,
    FT_INT24,
    FT_INT32,
    FT_INT64,
    FT_SIZE,
    FT_FLOAT,
    FT_DOUBLE,
    FT_STRING,
    FT_IPv4,
    FT_IPv6,
    FT_ETHER
};


/** field types string operation */
#define FT_SOP_EQ     "=="
#define FT_SOP_DEQ    "!="
#define FT_SOP_MAJ    ">"
#define FT_SOP_MIN    "<"
#define FT_SOP_AND    "AND"
#define FT_SOP_OR     "OR"
#define FT_SOP_CNTD   "<>"    /* contained */
#define FT_SOP_REX    "REX"   /* regular expression, in compare is the first element to be analyzed */

/** field types operation */
enum ft_op {
    FT_OP_EQ = 0, /* default */
    FT_OP_DEQ,
    FT_OP_MAJ,
    FT_OP_MIN,
    FT_OP_AND,
    FT_OP_OR,
    FT_OP_CNTD,
    FT_OP_REX
};


typedef union _ftval ftval;
union _ftval {
    unsigned int uint32;
    unsigned char uint8;
    unsigned short uint16;
    char int8;
    short int16;
    int int32;
    size_t size;
    float flt;
    double dbl;
    char *str;
    unsigned char ipv6[16];
    unsigned char mac[FT_ETH_LEN];
} __attribute__ ((aligned(4)));


int FTCopy(ftval *d, const ftval *s, enum ftype type);
int FTCmp(const ftval *a, const ftval *b, enum ftype type, enum ft_op op, void *opd); /* in regex is 'a' the string compared */
char *FTString(const ftval *val, enum ftype type, char *buff);
int FTFree(ftval *a, enum ftype type);
unsigned long FTHash(ftval *a, enum ftype type);


#endif /* __FTYPES_H__ */
