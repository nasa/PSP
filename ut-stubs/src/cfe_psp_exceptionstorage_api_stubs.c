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
 * Auto-Generated stub implementations for functions defined in cfe_psp_exceptionstorage_api header
 */

#include "cfe_psp_exceptionstorage_api.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_ExceptionGetSummary_Impl()
 * ----------------------------------------------------
 */
int32 CFE_PSP_ExceptionGetSummary_Impl(const struct CFE_PSP_Exception_LogData *Buffer, char *ReasonBuf,
                                       uint32 ReasonSize)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_ExceptionGetSummary_Impl, int32);

    UT_GenStub_AddParam(CFE_PSP_ExceptionGetSummary_Impl, const struct CFE_PSP_Exception_LogData *, Buffer);
    UT_GenStub_AddParam(CFE_PSP_ExceptionGetSummary_Impl, char *, ReasonBuf);
    UT_GenStub_AddParam(CFE_PSP_ExceptionGetSummary_Impl, uint32, ReasonSize);

    UT_GenStub_Execute(CFE_PSP_ExceptionGetSummary_Impl, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_ExceptionGetSummary_Impl, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_Exception_GetBuffer()
 * ----------------------------------------------------
 */
struct CFE_PSP_Exception_LogData *CFE_PSP_Exception_GetBuffer(uint32 seq)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_Exception_GetBuffer, struct CFE_PSP_Exception_LogData *);

    UT_GenStub_AddParam(CFE_PSP_Exception_GetBuffer, uint32, seq);

    UT_GenStub_Execute(CFE_PSP_Exception_GetBuffer, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_Exception_GetBuffer, struct CFE_PSP_Exception_LogData *);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_Exception_GetNextContextBuffer()
 * ----------------------------------------------------
 */
struct CFE_PSP_Exception_LogData *CFE_PSP_Exception_GetNextContextBuffer(void)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_Exception_GetNextContextBuffer, struct CFE_PSP_Exception_LogData *);

    UT_GenStub_Execute(CFE_PSP_Exception_GetNextContextBuffer, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_Exception_GetNextContextBuffer, struct CFE_PSP_Exception_LogData *);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_Exception_Reset()
 * ----------------------------------------------------
 */
void CFE_PSP_Exception_Reset(void)
{

    UT_GenStub_Execute(CFE_PSP_Exception_Reset, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_Exception_WriteComplete()
 * ----------------------------------------------------
 */
void CFE_PSP_Exception_WriteComplete(void)
{

    UT_GenStub_Execute(CFE_PSP_Exception_WriteComplete, Basic, NULL);
}