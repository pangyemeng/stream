/* fthread.h
 * flow thread functions and structures
 *
 * author: pangyemeng
 */


#ifndef __FTHREAD_H__
#define __FTHREAD_H__

#include <pthread.h>


#define FTHD_TBL_ELEMENT_DELTA   100
#define FTHD_STACK_SIZE          (145*1024)
#define FTHD_STACK_SIZE_PARAM    "THREAD_STACK_SIZE"



typedef void* (*start_routine)(void*);

int FthreadInit(const char *cfg_file);
int FthreadCreate(int flow_id, start_routine fun, void *arg);
void FthreadSync(void);
int FthreadChFlow(int fthd_id, int flow_id);
int FthreadFlow(int fthd_id);
int FthreadSelfFlowId(void);
void FthreadEnd(void);
unsigned long FthreadRunning(void);
unsigned long FthreadTblDim(void);

#endif /* __FTHREAD_H__ */
