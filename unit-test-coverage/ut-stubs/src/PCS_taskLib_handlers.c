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
#include <string.h>
#include <stdlib.h>
#include "utstubs.h"

#include "PCS_taskLib.h"
#include "PCS_errnoLib.h"

static PCS_WIND_TCB PCS_LOCAL_TASK = {0};

void UT_DefaultHandler_PCS_taskPriorityGet(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* PCS_STATUS PCS_taskPriorityGet(PCS_TASK_ID tid, int *pPriority) */
    int * pPriority = UT_Hook_GetArgValueByName(Context, "pPriority", int *);
    int32 iStatus;

    UT_Stub_GetInt32StatusCode(Context, &iStatus);
    if (iStatus >= 0)
    {
        UT_Stub_CopyToLocal(UT_KEY(PCS_taskPriorityGet), (int32 *)pPriority, sizeof(*pPriority));
    }
}

void UT_DefaultHandler_PCS_taskName(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* const char *PCS_taskName(PCS_TASK_ID task_id) */

    const char *retval;
    void *      bufptr;
    size_t      bufsz;
    int32       status;

    retval = NULL;
    UT_Stub_GetInt32StatusCode(Context, &status);

    if (status >= 0)
    {
        UT_GetDataBuffer(FuncKey, &bufptr, &bufsz, NULL);
        retval = bufptr;
    }

    UT_Stub_SetReturnValue(FuncKey, retval);
}

void UT_DefaultHandler_PCS_taskIdSelf(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* PCS_TASK_ID PCS_taskIdSelf(void) */
    PCS_TASK_ID retval;
    int32       status;

    UT_Stub_GetInt32StatusCode(Context, &status);

    if (status >= 0)
    {
        retval = &PCS_LOCAL_TASK;
        UT_Stub_SetReturnValue(FuncKey, retval);
    }
}

void UT_DefaultHandler_PCS_taskNameToId(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* PCS_TASK_ID PCS_taskNameToId(const char *name) */
    PCS_TASK_ID retval;
    int32       status;

    UT_Stub_GetInt32StatusCode(Context, &status);

    if (status >= 0)
    {
        retval = &PCS_LOCAL_TASK;
        UT_Stub_SetReturnValue(FuncKey, retval);
    }
}

void UT_DefaultHandler_PCS_taskSpawn(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* PCS_TASK_ID PCS_taskSpawn(char *name, int priority, int options, int stackSize, PCS_FUNCPTR entryPt, int arg1,
       int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10) */
    PCS_TASK_ID retval;
    int32       status;

    UT_Stub_GetInt32StatusCode(Context, &status);

    if (status >= 0)
    {
        retval = &PCS_LOCAL_TASK;
        UT_Stub_SetReturnValue(FuncKey, retval);
    }
}

void UT_DefaultHandler_PCS_taskTcb(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* PCS_WIND_TCB *PCS_taskTcb(PCS_TASK_ID tid) */
    PCS_TASK_ID   tid = UT_Hook_GetArgValueByName(Context, "tid", PCS_TASK_ID);
    PCS_WIND_TCB *LocalTcb;
    int32         status;

    UT_Stub_GetInt32StatusCode(Context, &status);

    if (status >= 0)
    {
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
    }
    else
    {
        LocalTcb = NULL;
    }

    UT_Stub_SetReturnValue(FuncKey, LocalTcb);
}
