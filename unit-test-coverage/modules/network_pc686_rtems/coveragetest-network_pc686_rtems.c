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

#include "utassert.h"
#include "utstubs.h"
#include "uttest.h"

#include "cfe_psp.h"
#include "cfe_psp_config.h"
#include "cfe_psp_module.h"

#include "PCS_rtems.h"
#include "PCS_bsdnet.h"
#include "PCS_stdlib.h"
#include "PCS_stdio.h"

/* This does not have a prototype */
extern void network_pc686_rtems_Init(uint32 PspModuleId);

void Test_network_pc686_rtems_Init(void)
{
    /*
    Test case for:
    void network_pc686_rtems_Init(uint32 PspModuleId)
    */
    UtAssert_VOIDCALL(network_pc686_rtems_Init(1));
    UtAssert_STUB_COUNT(PCS_printf, 1);

    /* Test for printf due to error from rtems_bsdnet_initialize_network  */
    UT_SetDefaultReturnValue(UT_KEY(PCS_rtems_bsdnet_initialize_network), -1);
    UtAssert_VOIDCALL(network_pc686_rtems_Init(1));
    UtAssert_STUB_COUNT(PCS_printf, 3);
}

/*
 * Macro to add a test case to the list of tests to execute
 */
#define ADD_TEST(test) UtTest_Add(test, NULL, NULL, #test)

/*
 * Register the test cases to execute with the unit test tool
 */
void UtTest_Setup(void)
{
    ADD_TEST(Test_network_pc686_rtems_Init);
}