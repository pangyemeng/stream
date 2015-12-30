/* config_param.h
 * Parameters of config file
 * author: pangyemeng
 */


#ifndef __CONFIG_PARAM_H__
#define __CONFIG_PARAM_H__

#include "istypes.h"

/* cfg line */
#define CFG_LINE_COMMENT           '#'
#define CFG_LINE_MAX_SIZE          512


/* directory paths */
#define CFG_PAR_TMP_DIR_PATH       "TMP_DIR_PATH"

/* log dir and name template */
#define CFG_PAR_LOG_DIR_PATH       "LOG_DIR_PATH"
#define CFG_PAR_LOG_NAME_TMP       "LOG_BASE_NAME"

/* flow and protocols params */
#define CFG_PAR_FLOW_TIMEOUT       "FLOW_SILENCE_TIMEOUT"

/* modules param */
#define CFG_PAR_MODULES_DIR        "MODULES_DIR"
#define CFG_PAR_MODULE_NAME        "MODULE"
#define CFG_PAR_MODULE_LOG         "LOG"
#define CFG_PAR_MODULE_LOG_LV_1    'F'
#define CFG_PAR_MODULE_LOG_LV_2    'E'
#define CFG_PAR_MODULE_LOG_LV_3    'W'
#define CFG_PAR_MODULE_LOG_LV_4    'I'
#define CFG_PAR_MODULE_LOG_LV_5    'T'
#define CFG_PAR_MODULE_LOG_LV_6    'D'
#define CFG_PAR_MODULE_LOG_LV_7    'S'

/* dispatcher */
#define CFG_PAR_DISPATCH           "DISPATCH"
#define CFG_PAR_DISPATCH_PARAL     "DISPATCH_PARALLEL"
#define CFG_PAR_DISPATCH_MANIP_NAME "MANIP"
#define CFG_PAR_DISPATCH_MANIP_HOST "MPHOST"
#define CFG_PAR_DISPATCH_MANIP_BIN  "MPBIN"
#define CFG_PAR_DISPATCH_MANIP_PORT "MPPORT"

/* geomap */
#define CFG_PAR_GEO_LAT            "DISPATCH_GEPMAP_LAT"
#define CFG_PAR_GEO_LONG           "DISPATCH_GEPMAP_LONG"

/* log mask */
#define CFG_PAR_CORE_LOG           "CORE_LOG"
#define CFG_PAR_CAPTURE_LOG        "CAPTURE_LOG"


bool CfgParIsComment(char *line);
unsigned short CfgParLogMask(char *mask, int line_num);


#endif /* __CONFIG_PARAM_H__ */
