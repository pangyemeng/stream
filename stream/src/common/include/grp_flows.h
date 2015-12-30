/* grp_flows.h
 *
 * author: pangyemeng
 */


#ifndef __GRP_FLOW_H__
#define __GRP_FLOW_H__

#include <pthread.h>
#include <sys/time.h>

#include "flow.h"
#include "proto.h"


/* define */
#define GRPFW_GROUP_DIM           100
#define GRPFW_TBL_ELEMENT_DELTA   100


/** group flow descriptor */
typedef struct _gflow gflow;
struct _gflow {
    bool fuse;        /**< all flows in the group to be compare as the same flow time line */
    bool sync;        /**< all flows in the group are syncronizated */
    bool elab;        /**< elaboration started */
    int fthd_id;      /**< group/flow thread id */
    int flow_list[GRPFW_GROUP_DIM];       /**< flow list in the group */
    bool flow_new[GRPFW_GROUP_DIM];       /**< flow list: id requested */
    struct timeval time[GRPFW_GROUP_DIM]; /**< time of next packet in the flow */
    int flow_ref;     /**< next packet flow reference */
    int fnum;         /**< number of flow */
    int read;         /**< read list of flow index */
    int last_read;    /**< last to read */
    pthread_mutex_t *mux;  /**< mutex to access fused packet */
    pthread_cond_t *cond;  /**< condiction to access fused packet */
};


/** group flow functions */
int GrpInit(void);
int GrpCreate(int flow_id);
int GrpAdd(int gflow_id, int flow_id);
int GrpFuse(int gflow_id, bool fuse);
int GrpSyncr(int gflow_id, bool sync);
int GrpElab(int gflow_id, int fthd_id, int flow_id);
int GrpLink(int gflow_id);
int GrpRm(int gflow_id, int flow_id);
void GrpFlowClosed(int gflow_id);
int GrpNewPkt(int gflow_id, int gref, const struct timeval *tpkt);
int GrpWaitPkt(int gflow_id, int gref);
bool GrpIsEmpty(int gflow_id);
bool GrpIsClose(int gflow_id);
int GrpFlowNum(int gflow_id);
int GrpLock(int gflow_id);
int GrpNext(int gflow_id);
int GrpUnlock(int gflow_id);
pstack_f* GrpStack(int gflow_id);


#endif /* __GRP_FLOW_H__ */
