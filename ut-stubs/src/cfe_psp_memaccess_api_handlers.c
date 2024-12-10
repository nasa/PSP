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
 * Purpose:
 * Unit test stubs for BSP routines
 *
 * NOTE: functions in here need to perform the real operation by default.
 * If a fuction invokes CFE_PSP_MemSet() with the expectation that it will
 * set an object to safe initial values, then behavior will be undefined
 * if this is not actually done.
 */

/*
** Includes
*/

#include <string.h>
#include "cfe_psp_memaccess_api.h"

#include "utstubs.h"

/*
 * ----------------------------------------------------
 * Default Handler function for CFE_PSP_MemCpy()
 * ----------------------------------------------------
 */
void UT_DefaultHandler_CFE_PSP_MemCpy(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* CFE_PSP_MemCpy(void *dest, const void *src, uint32 size) */
    void *      dest = UT_Hook_GetArgValueByName(Context, "dest", void *);
    const void *src  = UT_Hook_GetArgValueByName(Context, "src", const void *);
    uint32      n    = UT_Hook_GetArgValueByName(Context, "n", uint32);
    int32       Status;

    UT_Stub_GetInt32StatusCode(Context, &Status);
    if (Status >= 0)
    {
        memcpy(dest, src, n);
    }
}

/*
 * ----------------------------------------------------
 * Default Handler function for CFE_PSP_MemSet()
 * ----------------------------------------------------
 */
void UT_DefaultHandler_CFE_PSP_MemSet(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* int32 CFE_PSP_MemSet(void *dest, uint8 value, uint32 size) */
    void * dest  = UT_Hook_GetArgValueByName(Context, "dest", void *);
    uint8  value = UT_Hook_GetArgValueByName(Context, "value", uint8);
    uint32 n     = UT_Hook_GetArgValueByName(Context, "n", uint32);
    int32  Status;

    UT_Stub_GetInt32StatusCode(Context, &Status);
    if (Status >= 0)
    {
        memset(dest, value, n);
    }
}

/*
 * ----------------------------------------------------
 * Default Handler function for CFE_PSP_MemRead8()
 *  NOTE: historically this was the only "mem read" stub in PSP, and it output a value of 1.
 * ----------------------------------------------------
 */
void UT_DefaultHandler_CFE_PSP_MemRead8(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* int32 CFE_PSP_MemRead8(cpuaddr MemoryAddress, uint8 *ByteValue) */
    uint8 *outptr = UT_Hook_GetArgValueByName(Context, "ByteValue", uint8 *);
    int32  Status;

    UT_Stub_GetInt32StatusCode(Context, &Status);
    if (Status == CFE_PSP_SUCCESS && outptr != NULL)
    {
        if (UT_Stub_CopyToLocal(FuncKey, outptr, sizeof(*outptr)) != sizeof(*outptr))
        {
            *outptr = 1;
        }
    }
}

/*
 * ----------------------------------------------------
 * Default Handler function for CFE_PSP_MemRead16()
 * ----------------------------------------------------
 */
void UT_DefaultHandler_CFE_PSP_MemRead16(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* int32 CFE_PSP_MemRead16(cpuaddr MemoryAddress, uint16 *uint16Value) */
    uint16 *outptr = UT_Hook_GetArgValueByName(Context, "uint16Value", uint16 *);
    int32   Status;

    UT_Stub_GetInt32StatusCode(Context, &Status);
    if (Status == CFE_PSP_SUCCESS && outptr != NULL)
    {
        if (UT_Stub_CopyToLocal(FuncKey, outptr, sizeof(*outptr)) != sizeof(*outptr))
        {
            *outptr = 0;
        }
    }
}

/*
 * ----------------------------------------------------
 * Default Handler function for CFE_PSP_MemRead32()
 * ----------------------------------------------------
 */
void UT_DefaultHandler_CFE_PSP_MemRead32(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* int32 CFE_PSP_MemRead32(cpuaddr MemoryAddress, uint32 *uint32Value) */
    uint32 *outptr = UT_Hook_GetArgValueByName(Context, "uint32Value", uint32 *);
    int32   Status;

    UT_Stub_GetInt32StatusCode(Context, &Status);
    if (Status == CFE_PSP_SUCCESS && outptr != NULL)
    {
        if (UT_Stub_CopyToLocal(FuncKey, outptr, sizeof(*outptr)) != sizeof(*outptr))
        {
            *outptr = 0;
        }
    }
}
