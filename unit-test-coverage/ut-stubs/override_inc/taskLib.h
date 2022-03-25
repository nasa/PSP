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
#ifndef OVERRIDE_TASKLIB_H
#define OVERRIDE_TASKLIB_H

#include "PCS_taskLib.h"
#include <vxWorks.h>

/* ----------------------------------------- */
/* mappings for declarations in taskLib.h */
/* ----------------------------------------- */
#define VX_FP_TASK PCS_VX_FP_TASK
#define TASK_ID    PCS_TASK_ID
#define WIND_TCB   PCS_WIND_TCB
#define TASK_DESC  PCS_TASK_DESC

#define taskName        PCS_taskName
#define taskNameToId    PCS_taskNameToId
#define taskIdDefault   PCS_taskIdDefault
#define taskIsReady     PCS_taskIsReady
#define taskIsSuspended PCS_taskIsSuspended
#define taskGetInfo     PCS_taskGetInfo

#define taskActivate    PCS_taskActivate
#define taskExit        PCS_taskExit
#define taskIdSelf      PCS_taskIdSelf
#define taskDelay       PCS_taskDelay
#define taskDelete      PCS_taskDelete
#define taskDeleteForce PCS_taskDeleteForce
#define taskSuspend     PCS_taskSuspend
#define taskResume      PCS_taskResume
#define taskPrioritySet PCS_taskPrioritySet
#define taskSpawn       PCS_taskSpawn
#define taskInit        PCS_taskInit
#define taskTcb         PCS_taskTcb

#endif
