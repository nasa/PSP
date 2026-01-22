/************************************************************************
 * NASA Docket No. GSC-19,200-1, and identified as "cFS Draco"
 *
 * Copyright (c) 2023 United States Government as represented by the
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
 * Auto-Generated stub implementations for functions defined in
 * cfe_psp_backtrace header
 */

#include "cfe_psp_backtrace.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_Backtrace()
 * ----------------------------------------------------
 */
int32 CFE_PSP_Backtrace(CFE_PSP_BacktraceEntry_t *Entry, void *ContextPtr,
                        int32 MaxEntries) {
  UT_GenStub_SetupReturnBuffer(CFE_PSP_Backtrace, int32);

  UT_GenStub_AddParam(CFE_PSP_Backtrace, CFE_PSP_BacktraceEntry_t *, Entry);
  UT_GenStub_AddParam(CFE_PSP_Backtrace, void *, ContextPtr);
  UT_GenStub_AddParam(CFE_PSP_Backtrace, int32, MaxEntries);

  UT_GenStub_Execute(CFE_PSP_Backtrace, Basic, NULL);

  return UT_GenStub_GetReturnValue(CFE_PSP_Backtrace, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_Backtrace_Init()
 * ----------------------------------------------------
 */
void CFE_PSP_Backtrace_Init(void) {

  UT_GenStub_Execute(CFE_PSP_Backtrace_Init, Basic, NULL);
}
