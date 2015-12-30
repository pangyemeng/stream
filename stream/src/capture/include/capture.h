/* capture.h
 * author: pangyemeng
 * date: 2015-12-29
 */

#ifndef __CAPTURE_H__
#define __CAPTURE_H__

#define CAPT_OPTIONS_FUN        "CaptDisOptions"
#define CAPT_OPTIONS_HELP_FUN   "CaptDisOptionsHelp"
#define CAPT_MAIN_FUN           "CaptDisMain"
#define CAPT_SOURCE_FUN         "CaptDisSource"

int CapInit(const char *file_cfg, const char *cap);
char* CapOptions(void);
void CapOptionsHelp(void);
int CapMain();
const char *CapSource(void);

#endif /* __CAPTURE_H__ */
