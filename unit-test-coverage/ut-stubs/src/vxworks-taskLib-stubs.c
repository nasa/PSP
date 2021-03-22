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
#include <string.h>
#include <stdlib.h>
#include "utstubs.h"

#include "PCS_taskLib.h"
#include "PCS_errnoLib.h"

static PCS_WIND_TCB PCS_LOCAL_TASK = {0};

const char *PCS_taskName(PCS_TASK_ID task_id)
{
    const char *retval;
    int32       Status;

    retval = NULL;
    Status = UT_DEFAULT_IMPL(PCS_taskName);
    if (Status == 0)
    {
        UT_Stub_CopyToLocal(UT_KEY(PCS_taskName), &retval, sizeof(retval));
    }

    return retval;
}
void PCS_taskExit(int code)
{
    UT_DEFAULT_IMPL(PCS_taskExit);
}
PCS_TASK_ID PCS_taskIdSelf(void)
{
    int32 Status;

    Status = UT_DEFAULT_IMPL(PCS_taskIdSelf);
    if (Status != 0)
    {
        return ((PCS_TASK_ID)PCS_ERROR);
    }

    return &PCS_LOCAL_TASK;
}
PCS_TASK_ID PCS_taskNameToId(const char *name)
{
    int32 Status;

    Status = UT_DEFAULT_IMPL(PCS_taskNameToId);
    if (Status != 0)
    {
        return ((PCS_TASK_ID)PCS_ERROR);
    }

    return &PCS_LOCAL_TASK;
}
PCS_STATUS PCS_taskDelay(int ticks)
{
    return (UT_DEFAULT_IMPL(PCS_taskDelay));
}
PCS_STATUS PCS_taskDelete(PCS_TASK_ID tid)
{
    return (UT_DEFAULT_IMPL(PCS_taskDelete));
}
PCS_STATUS PCS_taskDeleteForce(PCS_TASK_ID tid)
{
    return (UT_DEFAULT_IMPL(PCS_taskDeleteForce));
}
PCS_STATUS PCS_taskSuspend(PCS_TASK_ID tid)
{
    return (UT_DEFAULT_IMPL(PCS_taskSuspend));
}
PCS_STATUS PCS_taskResume(PCS_TASK_ID tid)
{
    return (UT_DEFAULT_IMPL(PCS_taskResume));
}
PCS_STATUS PCS_taskPrioritySet(PCS_TASK_ID tid, int newPriority)
{
    return (UT_DEFAULT_IMPL(PCS_taskPrioritySet));
}

PCS_STATUS PCS_taskInit(PCS_WIND_TCB *pTcb, char *name, int priority, int options, char *pStackBase, int stackSize,
                        PCS_FUNCPTR entryPt, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7,
                        int arg8, int arg9, int arg10)
{
    return (UT_DEFAULT_IMPL(PCS_taskInit));
}

PCS_TASK_ID PCS_taskSpawn(char *name, int priority, int options, int stackSize, PCS_FUNCPTR entryPt, int arg1, int arg2,
                          int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10)

{
    int32 Status;

    Status = UT_DEFAULT_IMPL(PCS_taskSpawn);
    if (Status != 0)
    {
        return ((PCS_TASK_ID)PCS_ERROR);
    }

    return &PCS_LOCAL_TASK;
}

PCS_STATUS PCS_taskActivate(PCS_TASK_ID tid)
{
    int32 Status;

    Status = UT_DEFAULT_IMPL(PCS_taskActivate);

    return Status;
}

PCS_WIND_TCB *PCS_taskTcb(PCS_TASK_ID tid)
{
    int32         Status;
    PCS_WIND_TCB *LocalTcb;

    Status = UT_DEFAULT_IMPL(PCS_taskTcb);
    if (Status != 0)
    {
        return (NULL);
    }

    if (UT_Stub_CopyToLocal(UT_KEY(PCS_taskTcb), &LocalTcb, sizeof(LocalTcb)) < sizeof(LocalTcb))
    {
        /*
         * On VxWorks the TASK_ID is defined as a direct type cast
         * of the TCB address.  This is actually documented
         * in the API and application code that works with TCBs
         * certainly will depend on this being the case.
         */
        LocalTcb = (PCS_WIND_TCB *)tid;
    }

    return LocalTcb;
}
