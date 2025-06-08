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
** File: cfe_psp_watchdog_api_handlers.c
**
** Purpose:
** Unit test stubs for BSP routines
**
** Notes:
** Minimal work is done, only what is required for unit testing
**
*/

/*
** Includes
*/

#include "cfe_psp.h"
#include "utstubs.h"
#include <string.h>

/*
** Functions
*/

void UT_DefaultHandler_CFE_PSP_Panic(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* void CFE_PSP_Panic(int32 ErrorCode) */
    int32 ErrorCode = UT_Hook_GetArgValueByName(Context, "ErrorCode", int32);

    UT_Stub_CopyFromLocal(UT_KEY(CFE_PSP_Panic), (uint8 *)&ErrorCode, sizeof(ErrorCode));
}

void UT_DefaultHandler_CFE_PSP_Restart(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* void CFE_PSP_Restart(uint32 resetType) */
    uint32 resetType = UT_Hook_GetArgValueByName(Context, "resetType", uint32);

    UT_Stub_CopyFromLocal(UT_KEY(CFE_PSP_Restart), (uint8 *)&resetType, sizeof(resetType));
}
