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
 * \ingroup  shared
 */

#include "utassert.h"
#include "utstubs.h"

#include "cfe_psp_version_api.h"

void Test_CFE_PSP_GetVersionString(void)
{
    /* Test Case For:
     * const char *CFE_PSP_GetVersionString(void)
     */

    UtAssert_NOT_NULL(CFE_PSP_GetVersionString());
}

void Test_CFE_PSP_GetVersionCodeName(void)
{
    /* Test Case For:
     * const char *CFE_PSP_GetVersionCodeName(void)
     */

    UtAssert_NOT_NULL(CFE_PSP_GetVersionCodeName());
}

void Test_CFE_PSP_GetVersionNumber(void)
{
    /* Test Case For:
     * void CFE_PSP_GetVersionNumber(uint8 VersionNumbers[4])
     */
    uint8 VersionNumbers[4] = {0, 0, 0, 0};

    UtAssert_VOIDCALL(CFE_PSP_GetVersionNumber(VersionNumbers));

    /* Only sanity-check the major version, everything else can be validly zero */
    UtAssert_NONZERO(VersionNumbers[0]);
}

void Test_CFE_PSP_GetBuildNumber(void)
{
    /* Test Case For:
     * uint32 CFE_PSP_GetBuildNumber(void)
     */

    UtAssert_NONZERO(CFE_PSP_GetBuildNumber());
}
