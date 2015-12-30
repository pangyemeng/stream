/* genfun.c
 * author: pangyemeng
 */

#include <time.h>

#include "genfun.h"

#ifndef XP_CAPTURE_UTC
# error "configs.h error: you must define XP_CAPTURE_UTC as 0 or 1"
#endif


static int hdelta;


#if XP_CAPTURE_UTC == 0
int XTimeOffest(void)
{
    return hdelta;
}
#endif


void genfun_link(void)
{
    time_t now;
    struct tm lcl;;
    struct tm gmt;
    
    now = time(NULL);
    localtime_r(&now, &lcl);
    gmtime_r(&now, &gmt);

    hdelta = lcl.tm_hour - gmt.tm_hour;
}
