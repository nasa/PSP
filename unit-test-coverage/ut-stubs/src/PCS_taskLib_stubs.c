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

/**
 * @file
 *
 * Auto-Generated stub implementations for functions defined in PCS_taskLib header
 */

#include "PCS_taskLib.h"
#include "utgenstub.h"

void UT_DefaultHandler_PCS_taskIdSelf(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_PCS_taskName(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_PCS_taskNameToId(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_PCS_taskPriorityGet(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_PCS_taskSpawn(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_PCS_taskTcb(void *, UT_EntryKey_t, const UT_StubContext_t *);

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_taskActivate()
 * ----------------------------------------------------
 */
PCS_STATUS PCS_taskActivate(PCS_TASK_ID tid)
{
    UT_GenStub_SetupReturnBuffer(PCS_taskActivate, PCS_STATUS);

    UT_GenStub_AddParam(PCS_taskActivate, PCS_TASK_ID, tid);

    UT_GenStub_Execute(PCS_taskActivate, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_taskActivate, PCS_STATUS);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_taskDelay()
 * ----------------------------------------------------
 */
PCS_STATUS PCS_taskDelay(int ticks)
{
    UT_GenStub_SetupReturnBuffer(PCS_taskDelay, PCS_STATUS);

    UT_GenStub_AddParam(PCS_taskDelay, int, ticks);

    UT_GenStub_Execute(PCS_taskDelay, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_taskDelay, PCS_STATUS);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_taskDelete()
 * ----------------------------------------------------
 */
PCS_STATUS PCS_taskDelete(PCS_TASK_ID tid)
{
    UT_GenStub_SetupReturnBuffer(PCS_taskDelete, PCS_STATUS);

    UT_GenStub_AddParam(PCS_taskDelete, PCS_TASK_ID, tid);

    UT_GenStub_Execute(PCS_taskDelete, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_taskDelete, PCS_STATUS);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_taskDeleteForce()
 * ----------------------------------------------------
 */
PCS_STATUS PCS_taskDeleteForce(PCS_TASK_ID tid)
{
    UT_GenStub_SetupReturnBuffer(PCS_taskDeleteForce, PCS_STATUS);

    UT_GenStub_AddParam(PCS_taskDeleteForce, PCS_TASK_ID, tid);

    UT_GenStub_Execute(PCS_taskDeleteForce, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_taskDeleteForce, PCS_STATUS);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_taskExit()
 * ----------------------------------------------------
 */
void PCS_taskExit(int code)
{
    UT_GenStub_AddParam(PCS_taskExit, int, code);

    UT_GenStub_Execute(PCS_taskExit, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_taskGetInfo()
 * ----------------------------------------------------
 */
PCS_STATUS PCS_taskGetInfo(PCS_TASK_ID task_id, PCS_TASK_DESC *desc)
{
    UT_GenStub_SetupReturnBuffer(PCS_taskGetInfo, PCS_STATUS);

    UT_GenStub_AddParam(PCS_taskGetInfo, PCS_TASK_ID, task_id);
    UT_GenStub_AddParam(PCS_taskGetInfo, PCS_TASK_DESC *, desc);

    UT_GenStub_Execute(PCS_taskGetInfo, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_taskGetInfo, PCS_STATUS);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_taskIdDefault()
 * ----------------------------------------------------
 */
PCS_TASK_ID PCS_taskIdDefault(PCS_TASK_ID task_id)
{
    UT_GenStub_SetupReturnBuffer(PCS_taskIdDefault, PCS_TASK_ID);

    UT_GenStub_AddParam(PCS_taskIdDefault, PCS_TASK_ID, task_id);

    UT_GenStub_Execute(PCS_taskIdDefault, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_taskIdDefault, PCS_TASK_ID);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_taskIdSelf()
 * ----------------------------------------------------
 */
PCS_TASK_ID PCS_taskIdSelf(void)
{
    UT_GenStub_SetupReturnBuffer(PCS_taskIdSelf, PCS_TASK_ID);

    UT_GenStub_Execute(PCS_taskIdSelf, Basic, UT_DefaultHandler_PCS_taskIdSelf);

    return UT_GenStub_GetReturnValue(PCS_taskIdSelf, PCS_TASK_ID);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_taskInit()
 * ----------------------------------------------------
 */
PCS_STATUS PCS_taskInit(PCS_WIND_TCB *pTcb, char *name, int priority, int options, char *pStackBase, int stackSize,
                        PCS_FUNCPTR entryPt, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7,
                        int arg8, int arg9, int arg10)
{
    UT_GenStub_SetupReturnBuffer(PCS_taskInit, PCS_STATUS);

    UT_GenStub_AddParam(PCS_taskInit, PCS_WIND_TCB *, pTcb);
    UT_GenStub_AddParam(PCS_taskInit, char *, name);
    UT_GenStub_AddParam(PCS_taskInit, int, priority);
    UT_GenStub_AddParam(PCS_taskInit, int, options);
    UT_GenStub_AddParam(PCS_taskInit, char *, pStackBase);
    UT_GenStub_AddParam(PCS_taskInit, int, stackSize);
    UT_GenStub_AddParam(PCS_taskInit, PCS_FUNCPTR, entryPt);
    UT_GenStub_AddParam(PCS_taskInit, int, arg1);
    UT_GenStub_AddParam(PCS_taskInit, int, arg2);
    UT_GenStub_AddParam(PCS_taskInit, int, arg3);
    UT_GenStub_AddParam(PCS_taskInit, int, arg4);
    UT_GenStub_AddParam(PCS_taskInit, int, arg5);
    UT_GenStub_AddParam(PCS_taskInit, int, arg6);
    UT_GenStub_AddParam(PCS_taskInit, int, arg7);
    UT_GenStub_AddParam(PCS_taskInit, int, arg8);
    UT_GenStub_AddParam(PCS_taskInit, int, arg9);
    UT_GenStub_AddParam(PCS_taskInit, int, arg10);

    UT_GenStub_Execute(PCS_taskInit, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_taskInit, PCS_STATUS);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_taskIsReady()
 * ----------------------------------------------------
 */
PCS_BOOL PCS_taskIsReady(PCS_TASK_ID task_id)
{
    UT_GenStub_SetupReturnBuffer(PCS_taskIsReady, PCS_BOOL);

    UT_GenStub_AddParam(PCS_taskIsReady, PCS_TASK_ID, task_id);

    UT_GenStub_Execute(PCS_taskIsReady, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_taskIsReady, PCS_BOOL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_taskIsSuspended()
 * ----------------------------------------------------
 */
PCS_BOOL PCS_taskIsSuspended(PCS_TASK_ID task_id)
{
    UT_GenStub_SetupReturnBuffer(PCS_taskIsSuspended, PCS_BOOL);

    UT_GenStub_AddParam(PCS_taskIsSuspended, PCS_TASK_ID, task_id);

    UT_GenStub_Execute(PCS_taskIsSuspended, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_taskIsSuspended, PCS_BOOL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_taskName()
 * ----------------------------------------------------
 */
const char *PCS_taskName(PCS_TASK_ID task_id)
{
    UT_GenStub_SetupReturnBuffer(PCS_taskName, const char *);

    UT_GenStub_AddParam(PCS_taskName, PCS_TASK_ID, task_id);

    UT_GenStub_Execute(PCS_taskName, Basic, UT_DefaultHandler_PCS_taskName);

    return UT_GenStub_GetReturnValue(PCS_taskName, const char *);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_taskNameToId()
 * ----------------------------------------------------
 */
PCS_TASK_ID PCS_taskNameToId(const char *name)
{
    UT_GenStub_SetupReturnBuffer(PCS_taskNameToId, PCS_TASK_ID);

    UT_GenStub_AddParam(PCS_taskNameToId, const char *, name);

    UT_GenStub_Execute(PCS_taskNameToId, Basic, UT_DefaultHandler_PCS_taskNameToId);

    return UT_GenStub_GetReturnValue(PCS_taskNameToId, PCS_TASK_ID);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_taskPriorityGet()
 * ----------------------------------------------------
 */
PCS_STATUS PCS_taskPriorityGet(PCS_TASK_ID tid, int *pPriority)
{
    UT_GenStub_SetupReturnBuffer(PCS_taskPriorityGet, PCS_STATUS);

    UT_GenStub_AddParam(PCS_taskPriorityGet, PCS_TASK_ID, tid);
    UT_GenStub_AddParam(PCS_taskPriorityGet, int *, pPriority);

    UT_GenStub_Execute(PCS_taskPriorityGet, Basic, UT_DefaultHandler_PCS_taskPriorityGet);

    return UT_GenStub_GetReturnValue(PCS_taskPriorityGet, PCS_STATUS);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_taskPrioritySet()
 * ----------------------------------------------------
 */
PCS_STATUS PCS_taskPrioritySet(PCS_TASK_ID tid, int newPriority)
{
    UT_GenStub_SetupReturnBuffer(PCS_taskPrioritySet, PCS_STATUS);

    UT_GenStub_AddParam(PCS_taskPrioritySet, PCS_TASK_ID, tid);
    UT_GenStub_AddParam(PCS_taskPrioritySet, int, newPriority);

    UT_GenStub_Execute(PCS_taskPrioritySet, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_taskPrioritySet, PCS_STATUS);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_taskResume()
 * ----------------------------------------------------
 */
PCS_STATUS PCS_taskResume(PCS_TASK_ID tid)
{
    UT_GenStub_SetupReturnBuffer(PCS_taskResume, PCS_STATUS);

    UT_GenStub_AddParam(PCS_taskResume, PCS_TASK_ID, tid);

    UT_GenStub_Execute(PCS_taskResume, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_taskResume, PCS_STATUS);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_taskSpawn()
 * ----------------------------------------------------
 */
PCS_TASK_ID PCS_taskSpawn(char *name, int priority, int options, int stackSize, PCS_FUNCPTR entryPt, int arg1, int arg2,
                          int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10)
{
    UT_GenStub_SetupReturnBuffer(PCS_taskSpawn, PCS_TASK_ID);

    UT_GenStub_AddParam(PCS_taskSpawn, char *, name);
    UT_GenStub_AddParam(PCS_taskSpawn, int, priority);
    UT_GenStub_AddParam(PCS_taskSpawn, int, options);
    UT_GenStub_AddParam(PCS_taskSpawn, int, stackSize);
    UT_GenStub_AddParam(PCS_taskSpawn, PCS_FUNCPTR, entryPt);
    UT_GenStub_AddParam(PCS_taskSpawn, int, arg1);
    UT_GenStub_AddParam(PCS_taskSpawn, int, arg2);
    UT_GenStub_AddParam(PCS_taskSpawn, int, arg3);
    UT_GenStub_AddParam(PCS_taskSpawn, int, arg4);
    UT_GenStub_AddParam(PCS_taskSpawn, int, arg5);
    UT_GenStub_AddParam(PCS_taskSpawn, int, arg6);
    UT_GenStub_AddParam(PCS_taskSpawn, int, arg7);
    UT_GenStub_AddParam(PCS_taskSpawn, int, arg8);
    UT_GenStub_AddParam(PCS_taskSpawn, int, arg9);
    UT_GenStub_AddParam(PCS_taskSpawn, int, arg10);

    UT_GenStub_Execute(PCS_taskSpawn, Basic, UT_DefaultHandler_PCS_taskSpawn);

    return UT_GenStub_GetReturnValue(PCS_taskSpawn, PCS_TASK_ID);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_taskSuspend()
 * ----------------------------------------------------
 */
PCS_STATUS PCS_taskSuspend(PCS_TASK_ID tid)
{
    UT_GenStub_SetupReturnBuffer(PCS_taskSuspend, PCS_STATUS);

    UT_GenStub_AddParam(PCS_taskSuspend, PCS_TASK_ID, tid);

    UT_GenStub_Execute(PCS_taskSuspend, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_taskSuspend, PCS_STATUS);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_taskTcb()
 * ----------------------------------------------------
 */
PCS_WIND_TCB *PCS_taskTcb(PCS_TASK_ID tid)
{
    UT_GenStub_SetupReturnBuffer(PCS_taskTcb, PCS_WIND_TCB *);

    UT_GenStub_AddParam(PCS_taskTcb, PCS_TASK_ID, tid);

    UT_GenStub_Execute(PCS_taskTcb, Basic, UT_DefaultHandler_PCS_taskTcb);

    return UT_GenStub_GetReturnValue(PCS_taskTcb, PCS_WIND_TCB *);
}
