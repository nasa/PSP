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
 * \file     coveragetest-binsem.c
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
