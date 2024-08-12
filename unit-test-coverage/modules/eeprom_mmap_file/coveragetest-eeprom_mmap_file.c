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

#include "PCS_sys_stat.h"
#include "PCS_sys_mman.h"
#include "PCS_unistd.h"

extern void eeprom_mmap_file_Init(uint32 PspModuleId);

#define UT_RAMBLOCK_SIZE 32

static union
{
    uint8  u8[UT_RAMBLOCK_SIZE];
    uint16 u16[UT_RAMBLOCK_SIZE / sizeof(uint16)];
    uint32 u32[UT_RAMBLOCK_SIZE / sizeof(uint32)];
} UT_RAM_BLOCK;

void Test_eeprom_mmap_file_Init(void)
{
    /*
    void eeprom_mmap_file_Init(uint32 PspModuleId)
    */

    /* nominal */
    UtAssert_VOIDCALL(eeprom_mmap_file_Init(1));

    /* fail to mmap file */
    UT_SetDeferredRetcode(UT_KEY(PCS_mmap), 1, -1);
    UtAssert_VOIDCALL(eeprom_mmap_file_Init(1));

    /* fail to create new file file */
    UT_SetDeferredRetcode(UT_KEY(PCS_open), 1, -1);
    UtAssert_VOIDCALL(eeprom_mmap_file_Init(1));

    /* file exists */
    UT_SetDefaultReturnValue(UT_KEY(PCS_stat), -1);
    UtAssert_VOIDCALL(eeprom_mmap_file_Init(1));

    /* fail to open existing file */
    UT_SetDeferredRetcode(UT_KEY(PCS_open), 1, -1);
    UtAssert_VOIDCALL(eeprom_mmap_file_Init(1));

    /* fail to seek in existing file */
    UT_SetDeferredRetcode(UT_KEY(PCS_lseek), 1, -1);
    UtAssert_VOIDCALL(eeprom_mmap_file_Init(1));

    /* write success in existing file */
    UT_SetDeferredRetcode(UT_KEY(PCS_write), 1, 1);
    UtAssert_VOIDCALL(eeprom_mmap_file_Init(1));

    /* fail to write a byte in existing file */
    UT_SetDeferredRetcode(UT_KEY(PCS_write), 1, -1);
    UtAssert_VOIDCALL(eeprom_mmap_file_Init(1));
}

void Test_CFE_PSP_EepromWrite32(void)
{
    /*
    int32 CFE_PSP_EepromWrite32(cpuaddr MemoryAddress, uint32 uint32Value)
    */

    cpuaddr UtAddress1;
    cpuaddr UtAddress2;

    UtAddress1 = (cpuaddr)&UT_RAM_BLOCK.u32[2];
    UtAddress2 = (cpuaddr)&UT_RAM_BLOCK.u32[3];

    UtAssert_INT32_EQ(CFE_PSP_EepromWrite32(UtAddress1, 0xBB997755), CFE_PSP_SUCCESS);
    UtAssert_INT32_EQ(CFE_PSP_EepromWrite32(UtAddress2, 0xCCAA8866), CFE_PSP_SUCCESS);
    UtAssert_UINT32_EQ(UT_RAM_BLOCK.u32[2], 0xBB997755);
    UtAssert_UINT32_EQ(UT_RAM_BLOCK.u32[3], 0xCCAA8866);
}

void Test_CFE_PSP_EepromWrite16(void)
{
    /*
    int32 CFE_PSP_EepromWrite16(cpuaddr MemoryAddress, uint16 uint16Value)
    */

    cpuaddr UtAddress1;
    cpuaddr UtAddress2;

    UtAddress1 = (cpuaddr)&UT_RAM_BLOCK.u16[6];
    UtAddress2 = (cpuaddr)&UT_RAM_BLOCK.u16[7];

    UtAssert_INT32_EQ(CFE_PSP_EepromWrite16(UtAddress1, 0xBBDD), CFE_PSP_SUCCESS);
    UtAssert_INT32_EQ(CFE_PSP_EepromWrite16(UtAddress2, 0xCCEE), CFE_PSP_SUCCESS);
    UtAssert_UINT16_EQ(UT_RAM_BLOCK.u16[6], 0xBBDD);
    UtAssert_UINT16_EQ(UT_RAM_BLOCK.u16[7], 0xCCEE);
}

void Test_CFE_PSP_EepromWrite8(void)
{
    /*
    int32 CFE_PSP_EepromWrite8(cpuaddr MemoryAddress, uint8 ByteValue)
     */

    cpuaddr UtAddress1;
    cpuaddr UtAddress2;

    UtAddress1 = (cpuaddr)&UT_RAM_BLOCK.u8[4];
    UtAddress2 = (cpuaddr)&UT_RAM_BLOCK.u8[5];

    UtAssert_INT32_EQ(CFE_PSP_EepromWrite8(UtAddress1, 0xBB), CFE_PSP_SUCCESS);
    UtAssert_INT32_EQ(CFE_PSP_EepromWrite8(UtAddress2, 0xCC), CFE_PSP_SUCCESS);
    UtAssert_UINT8_EQ(UT_RAM_BLOCK.u8[4], 0xBB);
    UtAssert_UINT8_EQ(UT_RAM_BLOCK.u8[5], 0xCC);
}

void Test_CFE_PSP_EepromWriteEnable(void)
{
    /*
    int32 CFE_PSP_EepromWriteEnable(uint32 Bank)
    */
    UtAssert_INT32_EQ(CFE_PSP_EepromWriteEnable(1), CFE_PSP_ERROR_NOT_IMPLEMENTED);
}

void Test_CFE_PSP_EepromWriteDisable(void)
{
    /*
    int32 CFE_PSP_EepromWriteDisable(uint32 Bank)
    */
    UtAssert_INT32_EQ(CFE_PSP_EepromWriteDisable(1), CFE_PSP_ERROR_NOT_IMPLEMENTED);
}

void Test_CFE_PSP_EepromPowerUp(void)
{
    /*
    int32 CFE_PSP_EepromPowerUp(uint32 Bank)
    */
    UtAssert_INT32_EQ(CFE_PSP_EepromPowerUp(1), CFE_PSP_SUCCESS);
}

void Test_CFE_PSP_EepromPowerDown(void)
{
    /*
    int32 CFE_PSP_EepromPowerDown(uint32 Bank)
    */
    UtAssert_INT32_EQ(CFE_PSP_EepromPowerDown(1), CFE_PSP_SUCCESS);
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
    ADD_TEST(Test_eeprom_mmap_file_Init);
    ADD_TEST(Test_CFE_PSP_EepromWrite32);
    ADD_TEST(Test_CFE_PSP_EepromWrite16);
    ADD_TEST(Test_CFE_PSP_EepromWrite8);
    ADD_TEST(Test_CFE_PSP_EepromWriteEnable);
    ADD_TEST(Test_CFE_PSP_EepromWriteDisable);
    ADD_TEST(Test_CFE_PSP_EepromPowerUp);
    ADD_TEST(Test_CFE_PSP_EepromPowerDown);
}
