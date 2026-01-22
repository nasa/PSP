/************************************************************************
 * NASA Docket No. GSC-19,200-1, and identified as "cFS Draco"
 *
 * Copyright (c) 2023 United States Government as represented by the
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

/**
 * @file
 *
 * The default implementation of the stubs just passes through the original value
 * This is exactly what would happen in the real impl on a big endian processor,
 * so it should satisfy the existing test cases.
 */

#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Handler for CFE_PSP_BE16toH()
 * ----------------------------------------------------
 */
void UT_DefaultHandler_CFE_PSP_BE16toH(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint16_t CFE_PSP_BE16toH(uint16_t big_endian_16bits) */
    uint16_t val = UT_Hook_GetArgValueByName(Context, "big_endian_16bits", uint16_t);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/*
 * ----------------------------------------------------
 * Handler for CFE_PSP_BE32toH()
 * ----------------------------------------------------
 */
void UT_DefaultHandler_CFE_PSP_BE32toH(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint32_t CFE_PSP_BE32toH(uint32_t big_endian_32bits) */
    uint32_t val = UT_Hook_GetArgValueByName(Context, "big_endian_32bits", uint32_t);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/*
 * ----------------------------------------------------
 * Handler for CFE_PSP_BE64toH()
 * ----------------------------------------------------
 */
void UT_DefaultHandler_CFE_PSP_BE64toH(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint64_t CFE_PSP_BE64toH(uint64_t big_endian_64bits) */
    uint64_t val = UT_Hook_GetArgValueByName(Context, "big_endian_64bits", uint64_t);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/*
 * ----------------------------------------------------
 * Handler for CFE_PSP_HtoBE16()
 * ----------------------------------------------------
 */
void UT_DefaultHandler_CFE_PSP_HtoBE16(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint16_t CFE_PSP_HtoBE16(uint16_t host_16bits) */
    uint16_t val = UT_Hook_GetArgValueByName(Context, "host_16bits", uint16_t);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/*
 * ----------------------------------------------------
 * Handler for CFE_PSP_HtoBE32()
 * ----------------------------------------------------
 */
void UT_DefaultHandler_CFE_PSP_HtoBE32(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint32_t CFE_PSP_HtoBE32(uint32_t host_32bits) */
    uint32_t val = UT_Hook_GetArgValueByName(Context, "host_32bits", uint32_t);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/*
 * ----------------------------------------------------
 * Handler for CFE_PSP_HtoBE64()
 * ----------------------------------------------------
 */
void UT_DefaultHandler_CFE_PSP_HtoBE64(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint64_t CFE_PSP_HtoBE64(uint64_t host_64bits) */
    uint64_t val = UT_Hook_GetArgValueByName(Context, "host_64bits", uint64_t);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/*
 * ----------------------------------------------------
 * Handler for CFE_PSP_HtoLE16()
 * ----------------------------------------------------
 */
void UT_DefaultHandler_CFE_PSP_HtoLE16(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint16_t CFE_PSP_HtoLE16(uint16_t host_16bits) */
    uint16_t val = UT_Hook_GetArgValueByName(Context, "host_16bits", uint16_t);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/*
 * ----------------------------------------------------
 * Handler for CFE_PSP_HtoLE32()
 * ----------------------------------------------------
 */
void UT_DefaultHandler_CFE_PSP_HtoLE32(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint32_t CFE_PSP_HtoLE32(uint32_t host_32bits) */
    uint32_t val = UT_Hook_GetArgValueByName(Context, "host_32bits", uint32_t);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/*
 * ----------------------------------------------------
 * Handler for CFE_PSP_HtoLE64()
 * ----------------------------------------------------
 */
void UT_DefaultHandler_CFE_PSP_HtoLE64(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint64_t CFE_PSP_HtoLE64(uint64_t host_64bits) */
    uint64_t val = UT_Hook_GetArgValueByName(Context, "host_64bits", uint64_t);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/*
 * ----------------------------------------------------
 * Handler for CFE_PSP_LE16toH()
 * ----------------------------------------------------
 */
void UT_DefaultHandler_CFE_PSP_LE16toH(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint16_t CFE_PSP_LE16toH(uint16_t little_endian_16bits) */
    uint16_t val = UT_Hook_GetArgValueByName(Context, "little_endian_16bits", uint16_t);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/*
 * ----------------------------------------------------
 * Handler for CFE_PSP_LE32toH()
 * ----------------------------------------------------
 */
void UT_DefaultHandler_CFE_PSP_LE32toH(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint32_t CFE_PSP_LE32toH(uint32_t little_endian_32bits) */
    uint32_t val = UT_Hook_GetArgValueByName(Context, "little_endian_32bits", uint32_t);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/*
 * ----------------------------------------------------
 * Handler for CFE_PSP_LE64toH()
 * ----------------------------------------------------
 */
void UT_DefaultHandler_CFE_PSP_LE64toH(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint64_t CFE_PSP_LE64toH(uint64_t little_endian_64bits) */
    uint64_t val = UT_Hook_GetArgValueByName(Context, "little_endian_64bits", uint64_t);
    UT_Stub_SetReturnValue(FuncKey, val);
}
