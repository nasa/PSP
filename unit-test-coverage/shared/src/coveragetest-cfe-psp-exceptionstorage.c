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

/*
 *
 *    Copyright (c) 2020, United States government as represented by the
 *    administrator of the National Aeronautics Space Administration.
 *    All rights reserved. This software was created at NASA Goddard
 *    Space Flight Center pursuant to government contracts.
 *
 *    This is governed by the NASA Open Source Agreement and may be used,
 *    distributed and modified only according to the terms of that agreement.
 *
 */

/**
 * \file
 * \ingroup  vxworks
 * \author   joseph.p.hickey@nasa.gov
 *
 */

#include "utassert.h"
#include "utstubs.h"
#include "ut-adaptor-exceptions.h"

#include "cfe_psp.h"
#include "cfe_psp_exceptionstorage_api.h"

#ifdef jphfix
#include "PCS_stdlib.h"
#include "PCS_rebootLib.h"
#include "PCS_cacheLib.h"
#include "PCS_cfe_configdata.h"
#endif

void Test_CFE_PSP_Exception_GetBuffer(void)
{
    /*
     * Test Case For:
     * CFE_PSP_Exception_LogData_t* CFE_PSP_Exception_GetBuffer(uint32 seq)
     */
    struct CFE_PSP_Exception_LogData *Ptr0;
    struct CFE_PSP_Exception_LogData *Ptr1;

    Ptr0 = CFE_PSP_Exception_GetBuffer(0);
    UtAssert_True(Ptr0 != NULL, "CFE_PSP_Exception_GetBuffer(0) (%p) != NULL", (void *)Ptr0);
    Ptr1 = CFE_PSP_Exception_GetBuffer(1);
    UtAssert_True(Ptr1 != NULL, "CFE_PSP_Exception_GetBuffer(1) (%p) != NULL", (void *)Ptr1);

    UtAssert_True(Ptr0 != Ptr1, "CFE_PSP_Exception_GetBuffer(0) (%p) != CFE_PSP_Exception_GetBuffer(1) (%p)",
                  (void *)Ptr0, (void *)Ptr1);
}
void Test_CFE_PSP_Exception_GetNextContextBuffer(void)
{
    /*
     * Test Case For:
     *
     * void CFE_PSP_Exception_Reset(void)
     * CFE_PSP_Exception_LogData_t* CFE_PSP_Exception_GetNextContextBuffer(void)
     * void CFE_PSP_Exception_WriteComplete(void)
     * uint32 CFE_PSP_Exception_GetCount(void)
     */
    uint32 NumEntries;
    uint32 Count;

    CFE_PSP_Exception_Reset();
    UtAssert_ZERO(CFE_PSP_Exception_GetCount());
    NumEntries = UT_Get_Exception_MaxEntries();

    for (Count = 1; Count <= NumEntries; ++Count)
    {
        UtAssert_NOT_NULL(CFE_PSP_Exception_GetNextContextBuffer());
        CFE_PSP_Exception_WriteComplete();

        UtAssert_UINT32_EQ(CFE_PSP_Exception_GetCount(), Count);
    }

    /* Final call should return NULL */
    UtAssert_NULL(CFE_PSP_Exception_GetNextContextBuffer());
    CFE_PSP_Exception_Reset();
    UtAssert_ZERO(CFE_PSP_Exception_GetCount());
}

void Test_CFE_PSP_Exception_GetSummary(void)
{
    /*
     * Test Case For:
     * int32 CFE_PSP_Exception_GetSummary(uint32 *ContextLogId, uint32 *TaskId, char *ReasonBuf, uint32 ReasonSize)
     */
    char      ReasonBuf[128];
    uint32    LogId;
    osal_id_t TaskId;
    osal_id_t TestId;

    /* Nominal - no exceptions pending should return CFE_PSP_NO_EXCEPTION_DATA */
    CFE_PSP_Exception_Reset();
    UtAssert_INT32_EQ(CFE_PSP_Exception_GetSummary(&LogId, &TaskId, ReasonBuf, sizeof(ReasonBuf)),
                      CFE_PSP_NO_EXCEPTION_DATA);

    /* Set up an entry and then run again */
    TestId = OS_ObjectIdFromInteger(2857);
    UT_SetDataBuffer(UT_KEY(OS_TaskFindIdBySystemData), &TestId, sizeof(TestId), false);
    UtAssert_NOT_NULL(CFE_PSP_Exception_GetNextContextBuffer());
    CFE_PSP_Exception_WriteComplete();
    UtAssert_INT32_EQ(CFE_PSP_Exception_GetSummary(&LogId, &TaskId, ReasonBuf, sizeof(ReasonBuf)), CFE_PSP_SUCCESS);
    UtAssert_NONZERO(LogId);
    UtAssert_UINT32_EQ(OS_ObjectIdToInteger(TaskId), OS_ObjectIdToInteger(TestId));
    UtAssert_ZERO(CFE_PSP_Exception_GetCount());

    /* Get an entry with failure to obtain task ID */
    UtAssert_NOT_NULL(CFE_PSP_Exception_GetNextContextBuffer());
    CFE_PSP_Exception_WriteComplete();
    UT_SetDefaultReturnValue(UT_KEY(OS_TaskFindIdBySystemData), OS_ERROR);
    UtAssert_INT32_EQ(CFE_PSP_Exception_GetSummary(&LogId, &TaskId, ReasonBuf, sizeof(ReasonBuf)), CFE_PSP_SUCCESS);
    UT_ClearDefaultReturnValue(UT_KEY(OS_TaskFindIdBySystemData));
    UtAssert_NONZERO(LogId);
    UtAssert_ZERO(OS_ObjectIdToInteger(TaskId));

    UtAssert_NOT_NULL(CFE_PSP_Exception_GetNextContextBuffer());
    CFE_PSP_Exception_WriteComplete();
    UtAssert_INT32_EQ(CFE_PSP_Exception_GetSummary(&LogId, &TaskId, NULL, 0), CFE_PSP_SUCCESS);

    UtAssert_NOT_NULL(CFE_PSP_Exception_GetNextContextBuffer());
    CFE_PSP_Exception_WriteComplete();
    UtAssert_INT32_EQ(CFE_PSP_Exception_GetSummary(&LogId, NULL, ReasonBuf, sizeof(ReasonBuf)), CFE_PSP_SUCCESS);
}

void Test_CFE_PSP_Exception_CopyContext(void)
{
    /*
     * Test Case For:
     * int32 CFE_PSP_Exception_CopyContext(uint32 ContextLogId, void *ContextBuf, uint32 ContextSize)
     */
    struct CFE_PSP_Exception_LogData *Ptr;
    uint32                            LogId;
    uint32                            NumEntries;
    uint32                            Count;
    uint32                            SmallBuf[1];
    uint32                            LargeBuf[4];

    CFE_PSP_Exception_Reset();
    UtAssert_INT32_EQ(CFE_PSP_Exception_CopyContext(0, SmallBuf, sizeof(SmallBuf)), CFE_PSP_NO_EXCEPTION_DATA);

    Ptr = CFE_PSP_Exception_GetNextContextBuffer();
    UtAssert_True(Ptr != NULL, "CFE_PSP_Exception_GetNextContextBuffer() (%p) != NULL", (void *)Ptr);
    LogId = UT_Get_Exception_Id(Ptr);
    UT_Generate_Exception_Context(Ptr, sizeof(LargeBuf));
    CFE_PSP_Exception_WriteComplete();
    UtAssert_NONZERO(LogId);

    /* Read first entry  - remove from ring */
    UtAssert_INT32_EQ(CFE_PSP_Exception_GetSummary(NULL, NULL, NULL, 0), CFE_PSP_SUCCESS);

    /* Passing in a too-small buffer will work but will truncate the data */
    UtAssert_INT32_EQ(CFE_PSP_Exception_CopyContext(LogId, SmallBuf, sizeof(SmallBuf)), sizeof(SmallBuf));
    UtAssert_STUB_COUNT(OS_printf, 1);

    UtAssert_INT32_EQ(CFE_PSP_Exception_CopyContext(LogId, LargeBuf, sizeof(LargeBuf)), sizeof(LargeBuf));
    UtAssert_STUB_COUNT(OS_printf, 1);

    /* Test wrap-around/overwrite       */
    /* Fill the remainder of entries    */
    NumEntries = UT_Get_Exception_MaxEntries();
    for (Count = 0; Count < NumEntries; ++Count)
    {
        CFE_PSP_Exception_GetNextContextBuffer();
        CFE_PSP_Exception_WriteComplete();
    }

    UtAssert_UINT32_EQ(CFE_PSP_Exception_GetCount(), NumEntries);
    UtAssert_INT32_EQ(CFE_PSP_Exception_CopyContext(LogId, SmallBuf, sizeof(SmallBuf)), CFE_PSP_NO_EXCEPTION_DATA);
}
