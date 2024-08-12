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
 * Coverage test for VxWorks timebase module implementation
 */

#include "utassert.h"
#include "utstubs.h"
#include "uttest.h"

#include "cfe_psp.h"
#include "cfe_psp_config.h"
#include "cfe_psp_module.h"

/* This does not have a prototype */
extern void port_direct_Init(uint32 PspModuleId);

#define UT_RAMBLOCK_SIZE 32

static union
{
    uint8  u8[UT_RAMBLOCK_SIZE];
    uint16 u16[UT_RAMBLOCK_SIZE / sizeof(uint16)];
    uint32 u32[UT_RAMBLOCK_SIZE / sizeof(uint32)];
} UT_RAM_BLOCK;

void Test_port_direct_Init(void)
{
    /*
    Test case for:
    void port_direct_Init(uint32 PspModuleId)
    */
    UtAssert_VOIDCALL(port_direct_Init(1));
}

void Test_CFE_PSP_PortRead8(void)
{
    /*
    Test Case for:
    int32 CFE_PSP_PortRead8(cpuaddr PortAddress, uint8 *ByteValue)
    */
    cpuaddr UtAddress1;
    cpuaddr UtAddress2;
    uint8   Value1;
    uint8   Value2;

    UtAddress1         = (cpuaddr)&UT_RAM_BLOCK.u8[5];
    UtAddress2         = (cpuaddr)&UT_RAM_BLOCK.u8[6];
    UT_RAM_BLOCK.u8[5] = 0xAA;
    UT_RAM_BLOCK.u8[6] = 0xBB;

    UtAssert_INT32_EQ(CFE_PSP_PortRead8(UtAddress1, NULL), CFE_PSP_INVALID_POINTER);
    UtAssert_INT32_EQ(CFE_PSP_PortRead8(UtAddress1, &Value1), CFE_PSP_SUCCESS);
    UtAssert_INT32_EQ(CFE_PSP_PortRead8(UtAddress2, &Value2), CFE_PSP_SUCCESS);
    UtAssert_UINT8_EQ(Value1, UT_RAM_BLOCK.u8[5]);
    UtAssert_UINT8_EQ(Value2, UT_RAM_BLOCK.u8[6]);

    UtAssert_INT32_EQ(CFE_PSP_PortRead8(0, &Value1), CFE_PSP_INVALID_MEM_ADDR);
}

void Test_CFE_PSP_PortWrite8(void)
{
    /*
    Test Case for:
    int32 CFE_PSP_PortWrite8(cpuaddr PortAddress, uint8 ByteValue)
    */
    cpuaddr UtAddress1;
    cpuaddr UtAddress2;

    UtAddress1 = (cpuaddr)&UT_RAM_BLOCK.u8[4];
    UtAddress2 = (cpuaddr)&UT_RAM_BLOCK.u8[5];

    UtAssert_INT32_EQ(CFE_PSP_PortWrite8(UtAddress1, 0xBB), CFE_PSP_SUCCESS);
    UtAssert_INT32_EQ(CFE_PSP_PortWrite8(UtAddress2, 0xCC), CFE_PSP_SUCCESS);
    UtAssert_UINT8_EQ(UT_RAM_BLOCK.u8[4], 0xBB);
    UtAssert_UINT8_EQ(UT_RAM_BLOCK.u8[5], 0xCC);

    UtAssert_INT32_EQ(CFE_PSP_PortWrite8(0, 0), CFE_PSP_INVALID_MEM_ADDR);
}

void Test_CFE_PSP_PortRead16(void)
{
    /*
    Test Case for:
    int32 CFE_PSP_PortRead16(cpuaddr PortAddress, uint16 *uint16Value)
    */
    uint16 Value1;
    uint16 Value2;

    cpuaddr UtAddress1;
    cpuaddr UtAddress2;

    UtAddress1 = (cpuaddr)&UT_RAM_BLOCK.u16[7];
    UtAddress2 = (cpuaddr)&UT_RAM_BLOCK.u16[8];

    UT_RAM_BLOCK.u16[7] = 0x3344;
    UT_RAM_BLOCK.u16[8] = 0x99AA;

    UtAssert_INT32_EQ(CFE_PSP_PortRead16(UtAddress1, NULL), CFE_PSP_INVALID_POINTER);
    UtAssert_INT32_EQ(CFE_PSP_PortRead16(UtAddress1, &Value1), CFE_PSP_SUCCESS);
    UtAssert_INT32_EQ(CFE_PSP_PortRead16(UtAddress2, &Value2), CFE_PSP_SUCCESS);
    UtAssert_UINT16_EQ(Value1, UT_RAM_BLOCK.u16[7]);
    UtAssert_UINT16_EQ(Value2, UT_RAM_BLOCK.u16[8]);

    UtAssert_INT32_EQ(CFE_PSP_PortRead16(UtAddress1 + 1, &Value1), CFE_PSP_ERROR_ADDRESS_MISALIGNED);

    UtAssert_INT32_EQ(CFE_PSP_PortRead16(0, &Value1), CFE_PSP_INVALID_MEM_ADDR);
}

void Test_CFE_PSP_PortWrite16(void)
{
    /*
    Test Case for:
    int32 CFE_PSP_PortWrite16(cpuaddr PortAddress, uint16 uint16Value)
    */
    cpuaddr UtAddress1;
    cpuaddr UtAddress2;

    UtAddress1 = (cpuaddr)&UT_RAM_BLOCK.u16[6];
    UtAddress2 = (cpuaddr)&UT_RAM_BLOCK.u16[7];

    UtAssert_INT32_EQ(CFE_PSP_PortWrite16(UtAddress1, 0xBBDD), CFE_PSP_SUCCESS);
    UtAssert_INT32_EQ(CFE_PSP_PortWrite16(UtAddress2, 0xCCEE), CFE_PSP_SUCCESS);
    UtAssert_UINT16_EQ(UT_RAM_BLOCK.u16[6], 0xBBDD);
    UtAssert_UINT16_EQ(UT_RAM_BLOCK.u16[7], 0xCCEE);

    UtAssert_INT32_EQ(CFE_PSP_PortWrite16(UtAddress1 + 1, 0xEEFF), CFE_PSP_ERROR_ADDRESS_MISALIGNED);

    UtAssert_INT32_EQ(CFE_PSP_PortWrite16(0, 0), CFE_PSP_INVALID_MEM_ADDR);
}

void Test_CFE_PSP_PortRead32(void)
{
    /*
    Test Case for:
    int32 CFE_PSP_PortRead32(cpuaddr PortAddress, uint32 *uint32Value)
    */
    uint32 Value1;
    uint32 Value2;

    cpuaddr UtAddress1;
    cpuaddr UtAddress2;

    UtAddress1 = (cpuaddr)&UT_RAM_BLOCK.u32[3];
    UtAddress2 = (cpuaddr)&UT_RAM_BLOCK.u32[4];

    UT_RAM_BLOCK.u32[3] = 0xAABBCCDD;
    UT_RAM_BLOCK.u32[3] = 0x44556677;

    UtAssert_INT32_EQ(CFE_PSP_PortRead32(UtAddress1, NULL), CFE_PSP_INVALID_POINTER);
    UtAssert_INT32_EQ(CFE_PSP_PortRead32(UtAddress1, &Value1), CFE_PSP_SUCCESS);
    UtAssert_INT32_EQ(CFE_PSP_PortRead32(UtAddress2, &Value2), CFE_PSP_SUCCESS);
    UtAssert_UINT32_EQ(Value1, UT_RAM_BLOCK.u32[3]);
    UtAssert_UINT32_EQ(Value2, UT_RAM_BLOCK.u32[4]);

    UtAssert_INT32_EQ(CFE_PSP_PortRead32(UtAddress1 + 3, &Value1), CFE_PSP_ERROR_ADDRESS_MISALIGNED);

    UtAssert_INT32_EQ(CFE_PSP_PortRead32(0, &Value1), CFE_PSP_INVALID_MEM_ADDR);
}

void Test_CFE_PSP_PortWrite32(void)
{
    /*
    Test Case for:
    int32 CFE_PSP_PortWrite32(cpuaddr PortAddress, uint32 uint32Value)
    */
    cpuaddr UtAddress1;
    cpuaddr UtAddress2;

    UtAddress1 = (cpuaddr)&UT_RAM_BLOCK.u32[2];
    UtAddress2 = (cpuaddr)&UT_RAM_BLOCK.u32[3];

    UtAssert_INT32_EQ(CFE_PSP_PortWrite32(UtAddress1, 0xBB997755), CFE_PSP_SUCCESS);
    UtAssert_INT32_EQ(CFE_PSP_PortWrite32(UtAddress2, 0xCCAA8866), CFE_PSP_SUCCESS);
    UtAssert_UINT32_EQ(UT_RAM_BLOCK.u32[2], 0xBB997755);
    UtAssert_UINT32_EQ(UT_RAM_BLOCK.u32[3], 0xCCAA8866);

    UtAssert_INT32_EQ(CFE_PSP_PortWrite32(UtAddress1 + 3, 0xDEADBEEF), CFE_PSP_ERROR_ADDRESS_MISALIGNED);

    UtAssert_INT32_EQ(CFE_PSP_PortWrite32(0, 0), CFE_PSP_INVALID_MEM_ADDR);
}

/*
 * Macro to add a test case to the list of tests to execute
 */
#define ADD_TEST(test) UtTest_Add(test, ResetTest, NULL, #test)

void ResetTest(void)
{
    UT_ResetState(0);
    memset(&UT_RAM_BLOCK, 0, sizeof(UT_RAM_BLOCK));
}

/*
 * Register the test cases to execute with the unit test tool
 */
void UtTest_Setup(void)
{
    ADD_TEST(Test_port_direct_Init);
    ADD_TEST(Test_CFE_PSP_PortRead8);
    ADD_TEST(Test_CFE_PSP_PortWrite8);
    ADD_TEST(Test_CFE_PSP_PortRead16);
    ADD_TEST(Test_CFE_PSP_PortWrite16);
    ADD_TEST(Test_CFE_PSP_PortRead32);
    ADD_TEST(Test_CFE_PSP_PortWrite32);
}
