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
 * Auto-Generated stub implementations for functions defined in cfe_psp_exception_api header
 */

#include "cfe_psp_exception_api.h"
#include "utgenstub.h"

void UT_DefaultHandler_CFE_PSP_Exception_CopyContext(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_Exception_GetSummary(void *, UT_EntryKey_t, const UT_StubContext_t *);

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_AttachExceptions()
 * ----------------------------------------------------
 */
void CFE_PSP_AttachExceptions(void)
{

    UT_GenStub_Execute(CFE_PSP_AttachExceptions, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_Exception_CopyContext()
 * ----------------------------------------------------
 */
int32 CFE_PSP_Exception_CopyContext(uint32 ContextLogId, void *ContextBuf, uint32 ContextSize)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_Exception_CopyContext, int32);

    UT_GenStub_AddParam(CFE_PSP_Exception_CopyContext, uint32, ContextLogId);
    UT_GenStub_AddParam(CFE_PSP_Exception_CopyContext, void *, ContextBuf);
    UT_GenStub_AddParam(CFE_PSP_Exception_CopyContext, uint32, ContextSize);

    UT_GenStub_Execute(CFE_PSP_Exception_CopyContext, Basic, UT_DefaultHandler_CFE_PSP_Exception_CopyContext);

    return UT_GenStub_GetReturnValue(CFE_PSP_Exception_CopyContext, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_Exception_GetCount()
 * ----------------------------------------------------
 */
uint32 CFE_PSP_Exception_GetCount(void)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_Exception_GetCount, uint32);

    UT_GenStub_Execute(CFE_PSP_Exception_GetCount, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_Exception_GetCount, uint32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_Exception_GetSummary()
 * ----------------------------------------------------
 */
int32 CFE_PSP_Exception_GetSummary(uint32 *ContextLogId, osal_id_t *TaskId, char *ReasonBuf, uint32 ReasonSize)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_Exception_GetSummary, int32);

    UT_GenStub_AddParam(CFE_PSP_Exception_GetSummary, uint32 *, ContextLogId);
    UT_GenStub_AddParam(CFE_PSP_Exception_GetSummary, osal_id_t *, TaskId);
    UT_GenStub_AddParam(CFE_PSP_Exception_GetSummary, char *, ReasonBuf);
    UT_GenStub_AddParam(CFE_PSP_Exception_GetSummary, uint32, ReasonSize);

    UT_GenStub_Execute(CFE_PSP_Exception_GetSummary, Basic, UT_DefaultHandler_CFE_PSP_Exception_GetSummary);

    return UT_GenStub_GetReturnValue(CFE_PSP_Exception_GetSummary, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_SetDefaultExceptionEnvironment()
 * ----------------------------------------------------
 */
void CFE_PSP_SetDefaultExceptionEnvironment(void)
{

    UT_GenStub_Execute(CFE_PSP_SetDefaultExceptionEnvironment, Basic, NULL);
}
