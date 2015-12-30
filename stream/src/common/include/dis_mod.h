/* dis_mod.h
 * Dissector modules definition
 * author: pangyemeng
 */


#ifndef __DIS_MOD_H__
#define __DIS_MOD_H__

#define DISMOD_REGIST_FUN        "DissecRegist"
#define DISMOD_MULTI_REGIST_FUN  "DissecMultiRegist"
#define DISMOD_INIT_FUN          "DissectInit"
#define DISMOD_LOG_FUN           "DissectLog"
#define DISMOD_FLOW_HASH         "DissectFlowHash"
#define DISMOD_FLOW_CMP          "DissectFlowCmp"
#define DISMOD_FLOW_CMPFREE      "DissectFlowCmpFree"



/** Dissector register */
typedef int (*DisRegist)(const char *file_cfg);

/** Dissector multiple register */
typedef int (*DisMultiRegist)(const char *file_cfg);

/** Dissector inizialization */
typedef int (*DisInit)(void);

/** Dissector Log */
typedef void (*DisLog)(int);


int DisModLoad(char *file_cfg);
int DisModInit(void);
int DisModClose(void);
void DisModProtGraph(void);
void DisModProtInfo(const char *iana_name);

#endif /* __DIS_MOD_H__ */
