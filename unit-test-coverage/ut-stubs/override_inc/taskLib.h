/*
 *      Copyright (c) 2019, United States government as represented by the
 *      administrator of the National Aeronautics Space Administration.
 *      All rights reserved. This software was created at NASA Goddard
 *      Space Flight Center pursuant to government contracts.
 *
 *      This is governed by the NASA Open Source Agreement and may be used,
 *      distributed and modified only according to the terms of that agreement.
 */

/* PSP coverage stub replacement for taskLib.h */
#ifndef _PSP_OVERRIDE_TASKLIB_H_
#define _PSP_OVERRIDE_TASKLIB_H_

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

#endif /* _PSP_OVERRIDE_TASKLIB_H_ */
