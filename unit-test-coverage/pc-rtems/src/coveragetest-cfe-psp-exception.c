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

#include "coveragetest-psp-pc-rtems.h"

#include "cfe_psp.h"
#include "PCS_stdlib.h"

extern int32 CFE_PSP_ExceptionGetSummary_Impl(void *, char *, uint32);
extern void  CFE_PSP_SetupReservedMemoryMap(void);

uint32 UT_AttachExceptionsBuffer[1024];

void Test_CFE_PSP_AttachExceptions(void)
{
    /* Need to call CFE_PSP_SetupReservedMemoryMap here for initialization of CFE_PSP_ReservedMemoryMap */
    UT_SetDataBuffer(UT_KEY(PCS_malloc), UT_AttachExceptionsBuffer, sizeof(UT_AttachExceptionsBuffer), false);
    CFE_PSP_SetupReservedMemoryMap();
    UT_ResetState(UT_KEY(OS_printf)); /* Reset so calls to OS_printf in the setup above don't affect the actual test */

    /* Nominal path */
    CFE_PSP_AttachExceptions();
    UtAssert_STUB_COUNT(OS_printf, 1);
}

void Test_CFE_PSP_ExceptionGetSummary_Impl(void)
{
    /* Placeholder test to exercise function - amend tests if/when function is fully implemented */
    UtAssert_INT32_EQ(CFE_PSP_ExceptionGetSummary_Impl(NULL, NULL, 4), CFE_PSP_ERROR_NOT_IMPLEMENTED);
}

void Test_CFE_PSP_SetDefaultExceptionEnvironment(void)
{
    /* Placeholder test to exercise function - amend tests if/when function is fully implemented */
    CFE_PSP_SetDefaultExceptionEnvironment();
}
