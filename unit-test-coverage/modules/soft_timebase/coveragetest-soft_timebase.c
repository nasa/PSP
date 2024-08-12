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
 * \ingroup  modules
 *
 * Coverage test for soft timebase module implementation
 */

#include "utassert.h"
#include "utstubs.h"
#include "uttest.h"

#include "cfe_psp.h"
#include "cfe_psp_config.h"
#include "cfe_psp_module.h"

extern void soft_timebase_Init(uint32 PspModuleId);

UT_PSP_Soft_TimeBase_TestConfig_t UT_PSP_SOFT_TIMEBASE_TESTCONFIG;

void Test_soft_timebase_Init(void)
{
    /* Test for:
        void soft_timebase_Init(uint32 PspModuleId)
    */

    /* nominal */
    UtAssert_VOIDCALL(soft_timebase_Init(1));

    /* OS_TimeBaseSet() fail */
    UT_SetDefaultReturnValue(UT_KEY(OS_TimeBaseSet), OS_ERROR);
    UtAssert_VOIDCALL(soft_timebase_Init(2));

    /* OS_TimeBaseCreate() fail */
    UT_SetDefaultReturnValue(UT_KEY(OS_TimeBaseCreate), OS_ERROR);
    UtAssert_VOIDCALL(soft_timebase_Init(3));
}

/*
 * Macro to add a test case to the list of tests to execute
 */
#define ADD_TEST(test) UtTest_Add(test, ResetTest, NULL, #test)

void ResetTest(void)
{
    UT_ResetState(0);
}

/*
 * Register the test cases to execute with the unit test tool
 */
void UtTest_Setup(void)
{
    ADD_TEST(Test_soft_timebase_Init);
}
