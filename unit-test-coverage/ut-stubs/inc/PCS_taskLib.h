/************************************************************************
 * NASA Docket No. GSC-18,719-1, and identified as “core Flight System: Bootes”
 *
 * Copyright (c) 2020 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

/* PSP coverage stub replacement for taskLib.h */
#ifndef PCS_TASKLIB_H
#define PCS_TASKLIB_H

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

#endif
