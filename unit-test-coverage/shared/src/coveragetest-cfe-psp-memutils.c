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

#include "utassert.h"
#include "utstubs.h"

#include "cfe_psp_memaccess_api.h"

void Test_CFE_PSP_MemCpy(void)
{
    /* Test Case For:
     * int32 CFE_PSP_MemCpy(void *dest, const void *src, uint32 n)
     */
    const uint8 MySrcBuf[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    uint8       MyDstBuf[16];

    UtAssert_INT32_EQ(CFE_PSP_MemCpy(NULL, MySrcBuf, sizeof(MyDstBuf)), CFE_PSP_ERROR);
    UtAssert_INT32_EQ(CFE_PSP_MemCpy(MyDstBuf, NULL, sizeof(MyDstBuf)), CFE_PSP_ERROR);
    UtAssert_INT32_EQ(CFE_PSP_MemCpy(MyDstBuf, MySrcBuf, sizeof(MyDstBuf)), CFE_PSP_SUCCESS);
}

void Test_CFE_PSP_MemSet(void)
{
    /* Test Case For:
     * int32 CFE_PSP_MemSet(void *dest, uint8 value, uint32 n)
     */
    uint8 MyBuf[16];

    UtAssert_INT32_EQ(CFE_PSP_MemSet(NULL, 0x82, sizeof(MyBuf)), CFE_PSP_ERROR);
    UtAssert_INT32_EQ(CFE_PSP_MemSet(MyBuf, 0x82, sizeof(MyBuf)), CFE_PSP_SUCCESS);
}
