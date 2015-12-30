/* config.h
 *
 * author: pangyemeng
 */


#ifndef __CONFIGS_H__
#define __CONFIGS_H__


/* count any group flow with same protocol, the master protocol */
#define PROT_GRP_COUNT            1
/* enable or disable the geo ip localization */
#define XPL_GEO_IP                1
/* timeout at the end, for dissectors in loop */
#define XP_END_TO               600 /* sec */
/* time UTC/GMT or local time in dispatcher modules */
#define XP_CAPTURE_UTC            0
#define XP_DEFAULT_CFG            "../config/manage_cli.cfg"
/* memory debug and speed */
#define XP_MEM_DEBUG              1
#define XP_MEM_SPEED              0
/* tcp ack elaboration */
#define TCP_ENABLE_TCP_ACK        1

#endif /* __CONFIGS_H__ */
