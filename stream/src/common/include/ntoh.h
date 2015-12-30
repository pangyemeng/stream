/* ntoh.h
 * author: pangyemeng
 */


#ifndef __NTOH_H__
#define __NTOH_H__



#define pntoh24(p)  ((unsigned int)*((const unsigned char *)(p)+0)<<16| \
                     (unsigned int)*((const unsigned char *)(p)+1)<<8|  \
                     (unsigned int)*((const unsigned char *)(p)+2)<<0)


#define kswaps(p)  ((unsigned short)                                   \
                     ((unsigned short)*((const unsigned char *)(p)+1)<<8|  \
                      (unsigned short)*((const unsigned char *)(p)+0)<<0))


#define kswapsl(p)  ((unsigned int)*((const unsigned char *)(p)+3)<<24| \
                     (unsigned int)*((const unsigned char *)(p)+2)<<16| \
                     (unsigned int)*((const unsigned char *)(p)+1)<<8|  \
                     (unsigned int)*((const unsigned char *)(p)+0)<<0)

#define getu16(p, b) (*(unsigned short *)(((unsigned char*)p) + b))


#endif /* __NTOH_H__ */
