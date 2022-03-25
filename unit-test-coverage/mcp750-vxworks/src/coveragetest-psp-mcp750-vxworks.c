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

#include "coveragetest-psp-mcp750-vxworks.h"

/* Psp_Test_Setup
 *
 * Purpose:
 *   Called by the unit test tool to set up the app prior to each test
 */
void Psp_Test_Setup(void)
{
    UT_ResetState(0);
}

/*
 * Test_Teardown
 *
 * Purpose:
 *   Called by the unit test tool to tear down the app after each test
 */
void Psp_Test_Teardown(void) {}

/* UtTest_Setup
 *
 * Purpose:
 *   Registers the test cases to execute with the unit test tool
 */
void UtTest_Setup(void)
{
    ADD_TEST(OS_Application_Run);
    ADD_TEST(OS_Application_Startup);

    ADD_TEST(CFE_PSP_Restart);
    ADD_TEST(CFE_PSP_Panic);
    ADD_TEST(CFE_PSP_FlushCaches);
    ADD_TEST(CFE_PSP_GetProcessorId);
    ADD_TEST(CFE_PSP_GetSpacecraftId);

    ADD_TEST(CFE_PSP_Exception_GetBuffer);
    ADD_TEST(CFE_PSP_Exception_GetNextContextBuffer);
    ADD_TEST(CFE_PSP_Exception_GetSummary);
    ADD_TEST(CFE_PSP_Exception_CopyContext);
}
