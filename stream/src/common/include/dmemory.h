/* dmemory.h
 * author: pangyemeng
 */


#ifndef __DMEMORY_H__
#define __DMEMORY_H__

#include <stdlib.h>

#include "configs.h"

void *XMalloc(size_t size, const char *function, int line);
void XFree(void *ptr, const char *function, int line);
void *XRealloc(void *ptr, size_t size, const char *function, int line);
void *XMemcpy(void *dest, const void *src, size_t n, const char *function, int line);
char *XStrcpy(char *dest, const char *src, const char *function, int line);

#if XP_MEM_DEBUG
# define xmalloc(size)           XMalloc(size, __FUNCTION__, __LINE__)
# define xcalloc(num, size)      calloc(num, size)
# define xfree(ptr)              XFree(ptr, __FUNCTION__, __LINE__)
# define xrealloc(ptr, size)     XRealloc(ptr, size, __FUNCTION__, __LINE__)
# define xmemcpy(dest, src, n)   XMemcpy(dest, src, n, __FUNCTION__, __LINE__)
# define xstrcpy(dest, src)      XStrcpy(dest, src, __FUNCTION__, __LINE__)
#else
# define xmalloc(size)           malloc(size)
# define xcalloc(num, size)      calloc(num, size)
# define xfree(ptr)              free(ptr)
# define xrealloc(ptr, size)     realloc(ptr, size)
# define xmemcpy(dest, src, n)   memcpy(dest, src, n)
# define xstrcpy(dest, src)      strcpy(dest, src);
#endif


#if XP_MEM_SPEED
int DMemInit(void);
void *DMemMalloc(size_t size);
void DMemFree(void *ptr);
void DMemEmpty(void);
void DMemState(void);
#else
# define DMemInit()   0
# define DMemMalloc(c) xmalloc(c)
# define DMemFree(c)   xfree(c)
# define DMemEmpty()
# define DMemState()
#endif


unsigned long ThreadStackSize(void);

#endif /* __DMEMORY_H__ */
