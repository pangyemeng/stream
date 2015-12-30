/* genfun.h
 *
 * author: pangyemeng
 */


#ifndef __GENFUN_H__
#define __GENFUN_H__

#include "configs.h"

#ifndef XP_CAPTURE_UTC
# error "configs.h error: you must define XP_CAPTURE_UTC as 0 or 1"
#endif

#if XP_CAPTURE_UTC
#define XTimeOffest       0
#else
int XTimeOffest(void);
#endif

#endif
