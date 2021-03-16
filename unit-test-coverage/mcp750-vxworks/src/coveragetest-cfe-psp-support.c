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
#include "ut-adaptor-bootrec.h"

#include "cfe_psp.h"

#include "PCS_stdlib.h"
#include "PCS_rebootLib.h"
#include "PCS_cacheLib.h"
#include "PCS_cfe_configdata.h"

void Test_CFE_PSP_Restart(void)
{
    /*
     * Test Case For:
     * void CFE_PSP_Restart(uint32 reset_type)
     */

    UT_Setup_ReservedMem_BootRec();
    CFE_PSP_Restart(CFE_PSP_RST_TYPE_PROCESSOR);
    UtAssert_INT32_EQ(UT_Get_ReservedMem_BootType(), CFE_PSP_RST_TYPE_PROCESSOR);
    UtAssert_INT32_EQ(UT_GetStubCount(UT_KEY(PCS_cacheTextUpdate)), 1);
    UtAssert_INT32_EQ(UT_GetStubCount(UT_KEY(PCS_reboot)), 1);

    UT_Setup_ReservedMem_BootRec();
    CFE_PSP_Restart(CFE_PSP_RST_TYPE_POWERON);
    UtAssert_INT32_EQ(UT_Get_ReservedMem_BootType(), CFE_PSP_RST_TYPE_POWERON);
    UtAssert_INT32_EQ(UT_GetStubCount(UT_KEY(PCS_cacheTextUpdate)), 2);
    UtAssert_INT32_EQ(UT_GetStubCount(UT_KEY(PCS_reboot)), 2);
}

void Test_CFE_PSP_Panic(void)
{
    /*
     * Test Case For:
     * void CFE_PSP_Panic(int32 ErrorCode)
     */
    CFE_PSP_Panic(0);
    UtAssert_INT32_EQ(UT_GetStubCount(UT_KEY(PCS_exit)), 1);
}

void Test_CFE_PSP_FlushCaches(void)
{
    /*
     * Test Case For:
     * void CFE_PSP_FlushCaches(uint32 type, void* address, uint32 size)
     */

    CFE_PSP_FlushCaches(0, NULL, 0);
    UtAssert_INT32_EQ(UT_GetStubCount(UT_KEY(PCS_cacheTextUpdate)), 0);
    CFE_PSP_FlushCaches(1, NULL, 0);
    UtAssert_INT32_EQ(UT_GetStubCount(UT_KEY(PCS_cacheTextUpdate)), 1);
}

void Test_CFE_PSP_GetProcessorId(void)
{
    /*
     * Test Case For:
     * uint32 CFE_PSP_GetProcessorId    (void)
     */

    /*
     * Note - the data structure used here is declared as "const" internally so
     * there is no way to modify the value at runtime, even in unit test.
     */
    UtAssert_INT32_EQ(CFE_PSP_GetProcessorId(), PCS_CONFIG_CPUNUMBER);
}

void Test_CFE_PSP_GetSpacecraftId(void)
{
    /*
     * Test Case For:
     * uint32 CFE_PSP_GetSpacecraftId   (void)
     */

    /*
     * Note - the data structure used here is declared as "const" internally so
     * there is no way to modify the value at runtime, even in unit test.
     */
    UtAssert_INT32_EQ(CFE_PSP_GetSpacecraftId(), PCS_CONFIG_SPACECRAFT);
}
