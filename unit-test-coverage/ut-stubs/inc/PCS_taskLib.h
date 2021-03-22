/* PSP coverage stub replacement for taskLib.h */
#ifndef _PSP_STUB_TASKLIB_H_
#define _PSP_STUB_TASKLIB_H_

#include "PCS_basetypes.h"
#include "PCS_vxWorks.h"

/* ----------------------------------------- */
/* constants normally defined in taskLib.h */
/* ----------------------------------------- */
#define PCS_VX_FP_TASK 0x1b01 /* execute with floating-point coprocessor support. */

/* ----------------------------------------- */
/* types normally defined in taskLib.h */
/* ----------------------------------------- */
typedef struct PCS_WIND_TCB
{
    int data;
} PCS_WIND_TCB;

typedef struct PCS_WIND_TCB *PCS_TASK_ID;

typedef struct PCS_TASK_DESC
{
    PCS_TASK_ID tid;
} PCS_TASK_DESC;

/* ----------------------------------------- */
/* prototypes normally declared in taskInfo.h */
/* ----------------------------------------- */

extern const char *PCS_taskName(PCS_TASK_ID task_id);
extern PCS_TASK_ID PCS_taskNameToId(const char *name);
extern PCS_TASK_ID PCS_taskIdDefault(PCS_TASK_ID task_id);
extern PCS_BOOL    PCS_taskIsReady(PCS_TASK_ID task_id);
extern PCS_BOOL    PCS_taskIsSuspended(PCS_TASK_ID task_id);
extern PCS_STATUS  PCS_taskGetInfo(PCS_TASK_ID task_id, PCS_TASK_DESC *desc);

/* ----------------------------------------- */
/* prototypes normally declared in taskLib.h */
/* ----------------------------------------- */

extern PCS_STATUS  PCS_taskActivate(PCS_TASK_ID tid);
extern void        PCS_taskExit(int code);
extern PCS_TASK_ID PCS_taskIdSelf(void);
extern PCS_STATUS  PCS_taskDelay(int ticks);
extern PCS_STATUS  PCS_taskDelete(PCS_TASK_ID tid);
extern PCS_STATUS  PCS_taskDeleteForce(PCS_TASK_ID tid);
extern PCS_STATUS  PCS_taskSuspend(PCS_TASK_ID tid);
extern PCS_STATUS  PCS_taskResume(PCS_TASK_ID tid);
extern PCS_STATUS  PCS_taskPrioritySet(PCS_TASK_ID tid, int newPriority);
extern PCS_TASK_ID PCS_taskSpawn(char *name, int priority, int options, int stackSize, PCS_FUNCPTR entryPt, int arg1,
                                 int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9,
                                 int arg10);

PCS_STATUS PCS_taskInit(PCS_WIND_TCB *pTcb, char *name, int priority, int options, char *pStackBase, int stackSize,
                        PCS_FUNCPTR entryPt, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7,
                        int arg8, int arg9, int arg10);

PCS_WIND_TCB *PCS_taskTcb(PCS_TASK_ID tid);

#endif /* _PSP_STUB_TASKLIB_H_ */
