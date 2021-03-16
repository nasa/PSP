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
 * \file     psp-mcp750-vxworks-coveragetest.h
 * \ingroup  vxworks
 * \author   joseph.p.hickey@nasa.gov
 *
 */

#ifndef INCLUDE_PSP_MCP750_VXWORKS_COVERAGETEST_H_
#define INCLUDE_PSP_MCP750_VXWORKS_COVERAGETEST_H_

#include "utassert.h"
#include "uttest.h"
#include "utstubs.h"

#include "coveragetest-psp-shared.h"

#define ADD_TEST(test) UtTest_Add((Test_##test), Psp_Test_Setup, Psp_Test_Teardown, #test)

/* Psp_Test_Setup
 *
 * Purpose:
 *   Called by the unit test tool to set up the app prior to each test
 */
void Psp_Test_Setup(void);
void Psp_Test_Teardown(void);

/*
 * Test routine dedicated to coverage of each of the PSP implementation functions
 */
void Test_CFE_PSP_Restart(void);
void Test_CFE_PSP_Panic(void);
void Test_CFE_PSP_FlushCaches(void);
void Test_CFE_PSP_GetProcessorId(void);
void Test_CFE_PSP_GetSpacecraftId(void);

void Test_OS_Application_Startup(void);
void Test_OS_Application_Run(void);

#endif /* INCLUDE_PSP_MCP750_VXWORKS_COVERAGETEST_H_ */
