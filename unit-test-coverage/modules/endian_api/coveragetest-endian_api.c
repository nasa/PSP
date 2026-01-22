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
 * HOW THIS WORKS:
 *
 * For each of the test cases, the test vector will be passed to the
 * actual implementation used in FSW, and this becomes the reference value for
 * a direct call to the two impls which are compiled with coverage testing flags.
 *
 * This obtains an element of correctness testing by comparing the generic
 * conversion impl result to the FSW result, assuming that the latter was
 * compiled with the endian.h version, thereby confirming both impls give
 * the same result.
 *
 * However, on platforms that do not have endian.h and thus use the generic
 * version only, it ends up comparing to itself.  This is not really a
 * correctness test because there is no way to check if the
 * result is correct, but it still gets coverage, and at least verifies
 * the result is consistent with itself, even if its not able to confirm
 * that the result is correct.
 *
 * In both cases it can also be compiled with the "ubsan" to gain confidence
 * that neither routine induces undefined behavior.
 */

#include "utassert.h"
#include "utstubs.h"
#include "uttest.h"
#include "utgenstub.h"

#include "cfe_psp_endian.h"
#include "PCS_endian.h"

/* This compiles in both the generic and platform-specific implementations
 * with different name prefixes, as well as the real (non-stub) implementation */

extern uint16 UT_WRAPPED_HtoBE16(uint16 host_16bits);
extern uint16 UT_WRAPPED_HtoLE16(uint16 host_16bits);
extern uint16 UT_WRAPPED_BE16toH(uint16 big_endian_16bits);
extern uint16 UT_WRAPPED_LE16toH(uint16 little_endian_16bits);

extern uint32 UT_WRAPPED_HtoBE32(uint32 host_32bits);
extern uint32 UT_WRAPPED_HtoLE32(uint32 host_32bits);
extern uint32 UT_WRAPPED_BE32toH(uint32 big_endian_32bits);
extern uint32 UT_WRAPPED_LE32toH(uint32 little_endian_32bits);

extern uint64 UT_WRAPPED_HtoBE64(uint64 host_64bits);
extern uint64 UT_WRAPPED_HtoLE64(uint64 host_64bits);
extern uint64 UT_WRAPPED_BE64toH(uint64 big_endian_64bits);
extern uint64 UT_WRAPPED_LE64toH(uint64 little_endian_64bits);

extern uint16 UT_GENERIC_HtoBE16(uint16 host_16bits);
extern uint16 UT_GENERIC_HtoLE16(uint16 host_16bits);
extern uint16 UT_GENERIC_BE16toH(uint16 big_endian_16bits);
extern uint16 UT_GENERIC_LE16toH(uint16 little_endian_16bits);

extern uint32 UT_GENERIC_HtoBE32(uint32 host_32bits);
extern uint32 UT_GENERIC_HtoLE32(uint32 host_32bits);
extern uint32 UT_GENERIC_BE32toH(uint32 big_endian_32bits);
extern uint32 UT_GENERIC_LE32toH(uint32 little_endian_32bits);

extern uint64 UT_GENERIC_HtoBE64(uint64 host_64bits);
extern uint64 UT_GENERIC_HtoLE64(uint64 host_64bits);
extern uint64 UT_GENERIC_BE64toH(uint64 big_endian_64bits);
extern uint64 UT_GENERIC_LE64toH(uint64 little_endian_64bits);

/* Internal values from the impl that need to be accessed here */
extern uint8_t CFE_PSP_ENDIAN_INDICATOR;

#define CFE_PSP_BIG_INDICATOR    0x25
#define CFE_PSP_LITTLE_INDICATOR 0x9a

extern void endian_api_Init(uint32 PspModuleId);
extern void CFE_PSP_ReportEndian(uint8 CheckValue);

/* Define a handler for all the conversions that invokes the generic version */
/* This means that the two implementations can be correlated */

/*
 * ----------------------------------------------------
 * Handler for PCS_be16toh()
 * ----------------------------------------------------
 */
void UT_Handler_PCS_be16toh(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint16_t PCS_be16toh(uint16_t big_endian_16bits) */
    uint16_t val = UT_Hook_GetArgValueByName(Context, "big_endian_16bits", uint16_t);
    val          = UT_GENERIC_BE16toH(val);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/*
 * ----------------------------------------------------
 * Handler for PCS_be32toh()
 * ----------------------------------------------------
 */
void UT_Handler_PCS_be32toh(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint32_t PCS_be32toh(uint32_t big_endian_32bits) */
    uint32_t val = UT_Hook_GetArgValueByName(Context, "big_endian_32bits", uint32_t);
    val          = UT_GENERIC_BE32toH(val);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/*
 * ----------------------------------------------------
 * Handler for PCS_be64toh()
 * ----------------------------------------------------
 */
void UT_Handler_PCS_be64toh(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint64_t PCS_be64toh(uint64_t big_endian_64bits) */
    uint64_t val = UT_Hook_GetArgValueByName(Context, "big_endian_64bits", uint64_t);
    val          = UT_GENERIC_BE64toH(val);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/*
 * ----------------------------------------------------
 * Handler for PCS_htobe16()
 * ----------------------------------------------------
 */
void UT_Handler_PCS_htobe16(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint16_t PCS_htobe16(uint16_t host_16bits) */
    uint16_t val = UT_Hook_GetArgValueByName(Context, "host_16bits", uint16_t);
    val          = UT_GENERIC_HtoBE16(val);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/*
 * ----------------------------------------------------
 * Handler for PCS_htobe32()
 * ----------------------------------------------------
 */
void UT_Handler_PCS_htobe32(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint32_t PCS_htobe32(uint32_t host_32bits) */
    uint32_t val = UT_Hook_GetArgValueByName(Context, "host_32bits", uint32_t);
    val          = UT_GENERIC_HtoBE32(val);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/*
 * ----------------------------------------------------
 * Handler for PCS_htobe64()
 * ----------------------------------------------------
 */
void UT_Handler_PCS_htobe64(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint64_t PCS_htobe64(uint64_t host_64bits) */
    uint64_t val = UT_Hook_GetArgValueByName(Context, "host_64bits", uint64_t);
    val          = UT_GENERIC_HtoBE64(val);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/*
 * ----------------------------------------------------
 * Handler for PCS_htole16()
 * ----------------------------------------------------
 */
void UT_Handler_PCS_htole16(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint16_t PCS_htole16(uint16_t host_16bits) */
    uint16_t val = UT_Hook_GetArgValueByName(Context, "host_16bits", uint16_t);
    val          = UT_GENERIC_HtoLE16(val);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/*
 * ----------------------------------------------------
 * Handler for PCS_htole32()
 * ----------------------------------------------------
 */
void UT_Handler_PCS_htole32(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint32_t PCS_htole32(uint32_t host_32bits) */
    uint32_t val = UT_Hook_GetArgValueByName(Context, "host_32bits", uint32_t);
    val          = UT_GENERIC_HtoLE32(val);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/*
 * ----------------------------------------------------
 * Handler for PCS_htole64()
 * ----------------------------------------------------
 */
void UT_Handler_PCS_htole64(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint64_t PCS_htole64(uint64_t host_64bits) */
    uint64_t val = UT_Hook_GetArgValueByName(Context, "host_64bits", uint64_t);
    val          = UT_GENERIC_HtoLE64(val);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/*
 * ----------------------------------------------------
 * Handler for PCS_le16toh()
 * ----------------------------------------------------
 */
void UT_Handler_PCS_le16toh(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint16_t PCS_le16toh(uint16_t little_endian_16bits) */
    uint16_t val = UT_Hook_GetArgValueByName(Context, "little_endian_16bits", uint16_t);
    val          = UT_GENERIC_LE16toH(val);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/*
 * ----------------------------------------------------
 * Handler for PCS_le32toh()
 * ----------------------------------------------------
 */
void UT_Handler_PCS_le32toh(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint32_t PCS_le32toh(uint32_t little_endian_32bits) */
    uint32_t val = UT_Hook_GetArgValueByName(Context, "little_endian_32bits", uint32_t);
    val          = UT_GENERIC_LE32toH(val);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/*
 * ----------------------------------------------------
 * Handler for PCS_le64toh()
 * ----------------------------------------------------
 */
void UT_Handler_PCS_le64toh(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* uint64_t PCS_le64toh(uint64_t little_endian_64bits) */
    uint64_t val = UT_Hook_GetArgValueByName(Context, "little_endian_64bits", uint64_t);
    val          = UT_GENERIC_LE64toH(val);
    UT_Stub_SetReturnValue(FuncKey, val);
}

/********** TEST FUNCTIONS BEGIN HERE *************/

/*
 * ----------------------------------------------------
 * Test Case For: CFE_PSP_HtoBE16:
 * uint16 CFE_PSP_HtoBE16(uint16 host_16bits);
 * ----------------------------------------------------
 */
void Test_CFE_PSP_HtoBE16(void)
{
    uint16       host_16bits;
    uint16       result;
    const uint16 test_values[] = {0x1234, 0x5678, 0x9ABC, 0xDEF0};
    uint16       i;

    UT_SetHandlerFunction(UT_KEY(PCS_htobe16), UT_Handler_PCS_htobe16, NULL);

    for (i = 0; i < sizeof(test_values) / sizeof(test_values[0]); ++i)
    {
        host_16bits = test_values[i];
        result      = CFE_PSP_HtoBE16(host_16bits);
        UtAssert_EQ(uint16, UT_GENERIC_HtoBE16(host_16bits), result);
        UtAssert_EQ(uint16, UT_WRAPPED_HtoBE16(host_16bits), result);
    }
}

/*
 * ----------------------------------------------------
 * Test Case For: CFE_PSP_HtoLE16:
 * uint16 CFE_PSP_HtoLE16(uint16 host_16bits);
 * ----------------------------------------------------
 */
void Test_CFE_PSP_HtoLE16(void)
{
    uint16       host_16bits;
    const uint16 test_values[] = {0x1234, 0x5678, 0x9ABC, 0xDEF0};
    uint16       result;
    uint16       i;

    UT_SetHandlerFunction(UT_KEY(PCS_htole16), UT_Handler_PCS_htole16, NULL);

    for (i = 0; i < sizeof(test_values) / sizeof(test_values[0]); ++i)
    {
        host_16bits = test_values[i];
        result      = CFE_PSP_HtoLE16(host_16bits);
        UtAssert_EQ(uint16, UT_GENERIC_HtoLE16(host_16bits), result);
        UtAssert_EQ(uint16, UT_WRAPPED_HtoLE16(host_16bits), result);
    }
}

/*
 * ----------------------------------------------------
 * Test Case For: CFE_PSP_BE16toH:
 * uint16 CFE_PSP_BE16toH(uint16 big_endian_16bits)
 * ----------------------------------------------------
 */
void Test_CFE_PSP_BE16toH(void)
{
    uint16       big_endian_16bits;
    const uint16 test_values[] = {0x1234, 0x5678, 0x9ABC, 0xDEF0};
    uint16       result;
    uint16       i;

    UT_SetHandlerFunction(UT_KEY(PCS_be16toh), UT_Handler_PCS_be16toh, NULL);

    for (i = 0; i < sizeof(test_values) / sizeof(test_values[0]); ++i)
    {
        big_endian_16bits = test_values[i];
        result            = CFE_PSP_BE16toH(big_endian_16bits);
        UtAssert_EQ(uint16, UT_GENERIC_BE16toH(big_endian_16bits), result);
        UtAssert_EQ(uint16, UT_WRAPPED_BE16toH(big_endian_16bits), result);
    }
}

/*
 * ----------------------------------------------------
 * Test Case For: CFE_PSP_LE16toH:
 * uint16 CFE_PSP_LE16toH(uint16 little_endian_16bi
 * ----------------------------------------------------
 */
void Test_CFE_PSP_LE16toH(void)
{
    uint16       little_endian_16bits;
    const uint16 test_values[] = {0x1234, 0x5678, 0x9ABC, 0xDEF0};
    uint16       result;
    uint16       i;

    UT_SetHandlerFunction(UT_KEY(PCS_le16toh), UT_Handler_PCS_le16toh, NULL);

    for (i = 0; i < sizeof(test_values) / sizeof(test_values[0]); ++i)
    {
        little_endian_16bits = test_values[i];
        result               = CFE_PSP_LE16toH(little_endian_16bits);
        UtAssert_EQ(uint16, UT_GENERIC_LE16toH(little_endian_16bits), result);
        UtAssert_EQ(uint16, UT_WRAPPED_LE16toH(little_endian_16bits), result);
    }
}

/*
 * ----------------------------------------------------
 * Test Case For: CFE_PSP_HtoBE32:
 * uint32 CFE_PSP_HtoBE32(uint32 host_32bits);
 * ----------------------------------------------------
 */
void Test_CFE_PSP_HtoBE32(void)
{
    uint32       host_32bits;
    const uint32 test_values[] = {0x12345678, 0x9ABCDEF0, 0x3456789A, 0xBCDEF012};
    uint32       result;
    uint16       i;

    UT_SetHandlerFunction(UT_KEY(PCS_htobe32), UT_Handler_PCS_htobe32, NULL);

    for (i = 0; i < sizeof(test_values) / sizeof(test_values[0]); ++i)
    {
        host_32bits = test_values[i];
        result      = CFE_PSP_HtoBE32(host_32bits);
        UtAssert_EQ(uint32, UT_GENERIC_HtoBE32(host_32bits), result);
        UtAssert_EQ(uint32, UT_WRAPPED_HtoBE32(host_32bits), result);
    }
}

/*
 * ----------------------------------------------------
 * Test Case For: CFE_PSP_HtoLE32:
 * uint32 CFE_PSP_HtoLE32(uint32 host_32bits);
 * ----------------------------------------------------
 */
void Test_CFE_PSP_HtoLE32(void)
{
    uint32       host_32bits;
    const uint32 test_values[] = {0x12345678, 0x9ABCDEF0, 0x3456789A, 0xBCDEF012};
    uint32       result;
    uint16       i;

    UT_SetHandlerFunction(UT_KEY(PCS_htole32), UT_Handler_PCS_htole32, NULL);

    for (i = 0; i < sizeof(test_values) / sizeof(test_values[0]); ++i)
    {
        host_32bits = test_values[i];
        result      = CFE_PSP_HtoLE32(host_32bits);
        UtAssert_EQ(uint32, UT_GENERIC_HtoLE32(host_32bits), result);
        UtAssert_EQ(uint32, UT_WRAPPED_HtoLE32(host_32bits), result);
    }
}

/*
 * ----------------------------------------------------
 * Test Case For: CFE_PSP_BE32toH:
 * uint32 CFE_PSP_BE32toH(uint32 big_endian_32bits)
 * ----------------------------------------------------
 */
void Test_CFE_PSP_BE32toH(void)
{
    uint32       big_endian_32bits;
    const uint32 test_values[] = {0x12345678, 0x9ABCDEF0, 0x3456789A, 0xBCDEF012};
    uint32       result;
    uint16       i;

    UT_SetHandlerFunction(UT_KEY(PCS_be32toh), UT_Handler_PCS_be32toh, NULL);

    for (i = 0; i < sizeof(test_values) / sizeof(test_values[0]); ++i)
    {
        big_endian_32bits = test_values[i];
        result            = CFE_PSP_BE32toH(big_endian_32bits);
        UtAssert_EQ(uint32, UT_GENERIC_BE32toH(big_endian_32bits), result);
        UtAssert_EQ(uint32, UT_WRAPPED_BE32toH(big_endian_32bits), result);
    }
}

/*
 * ----------------------------------------------------
 * Test Case For: CFE_PSP_LE32toH:
 * uint32 CFE_PSP_LE32toH(uint32 little_endian_32bi
 * ----------------------------------------------------
 */
void Test_CFE_PSP_LE32toH(void)
{
    uint32       little_endian_32bits;
    const uint32 test_values[] = {0x12345678, 0x9ABCDEF0, 0x3456789A, 0xBCDEF012};
    uint32       result;
    uint16       i;

    UT_SetHandlerFunction(UT_KEY(PCS_le32toh), UT_Handler_PCS_le32toh, NULL);

    for (i = 0; i < sizeof(test_values) / sizeof(test_values[0]); ++i)
    {
        little_endian_32bits = test_values[i];
        result               = CFE_PSP_LE32toH(little_endian_32bits);
        UtAssert_EQ(uint32, UT_GENERIC_LE32toH(little_endian_32bits), result);
        UtAssert_EQ(uint32, UT_WRAPPED_LE32toH(little_endian_32bits), result);
    }
}

/*
 * ----------------------------------------------------
 * Test Case For: CFE_PSP_HtoBE64:
 * uint64 CFE_PSP_HtoBE64(uint64 host_64bits);
 * ----------------------------------------------------
 */
void Test_CFE_PSP_HtoBE64(void)
{
    uint64       host_64bits;
    const uint64 test_values[] = {0x123456789ABCDEF0, 0x56789ABCDEF01234, 0x9ABCDEF012345678, 0xDEF0123456789ABC};
    uint64       result;
    uint16       i;

    UT_SetHandlerFunction(UT_KEY(PCS_htobe64), UT_Handler_PCS_htobe64, NULL);

    for (i = 0; i < sizeof(test_values) / sizeof(test_values[0]); ++i)
    {
        host_64bits = test_values[i];
        result      = CFE_PSP_HtoBE64(host_64bits);
        UtAssert_EQ(uint64, UT_GENERIC_HtoBE64(host_64bits), result);
        UtAssert_EQ(uint64, UT_WRAPPED_HtoBE64(host_64bits), result);
    }
}

/*
 * ----------------------------------------------------
 * Test Case For: CFE_PSP_HtoLE64:
 * uint64 CFE_PSP_HtoLE64(uint64 host_64bits);
 * ----------------------------------------------------
 */
void Test_CFE_PSP_HtoLE64(void)
{
    uint64       host_64bits;
    const uint64 test_values[] = {0x123456789ABCDEF0, 0x56789ABCDEF01234, 0x9ABCDEF012345678, 0xDEF0123456789ABC};
    uint64       result;
    uint16       i;

    UT_SetHandlerFunction(UT_KEY(PCS_htole64), UT_Handler_PCS_htole64, NULL);

    for (i = 0; i < sizeof(test_values) / sizeof(test_values[0]); ++i)
    {
        host_64bits = test_values[i];
        result      = CFE_PSP_HtoLE64(host_64bits);
        UtAssert_EQ(uint64, UT_GENERIC_HtoLE64(host_64bits), result);
        UtAssert_EQ(uint64, UT_WRAPPED_HtoLE64(host_64bits), result);
    }
}

/*
 * ----------------------------------------------------
 * Test Case For: CFE_PSP_BE64toH:
 * uint64 CFE_PSP_BE64toH(uint64 big_endian_64bits)
 * ----------------------------------------------------
 */
void Test_CFE_PSP_BE64toH(void)
{
    uint64       big_endian_64bits;
    const uint64 test_values[] = {0x123456789ABCDEF0, 0x56789ABCDEF01234, 0x9ABCDEF012345678, 0xDEF0123456789ABC};
    uint64       result;
    uint16       i;

    UT_SetHandlerFunction(UT_KEY(PCS_be64toh), UT_Handler_PCS_be64toh, NULL);

    for (i = 0; i < sizeof(test_values) / sizeof(test_values[0]); ++i)
    {
        big_endian_64bits = test_values[i];
        result            = CFE_PSP_BE64toH(big_endian_64bits);
        UtAssert_EQ(uint64, UT_GENERIC_BE64toH(big_endian_64bits), result);
        UtAssert_EQ(uint64, UT_WRAPPED_BE64toH(big_endian_64bits), result);
    }
}

/*
 * ----------------------------------------------------
 * Test Case For: CFE_PSP_LE64toH:
 * uint64 CFE_PSP_LE64toH(uint64 little_endian_64bi
 * ----------------------------------------------------
 */
void Test_CFE_PSP_LE64toH(void)
{
    uint64       little_endian_64bits;
    const uint64 test_values[] = {0x123456789ABCDEF0, 0x56789ABCDEF01234, 0x9ABCDEF012345678, 0xDEF0123456789ABC};
    uint64       result;
    uint16       i;

    UT_SetHandlerFunction(UT_KEY(PCS_le64toh), UT_Handler_PCS_le64toh, NULL);

    for (i = 0; i < sizeof(test_values) / sizeof(test_values[0]); ++i)
    {
        little_endian_64bits = test_values[i];
        result               = CFE_PSP_LE64toH(little_endian_64bits);
        UtAssert_EQ(uint64, UT_GENERIC_LE64toH(little_endian_64bits), result);
        UtAssert_EQ(uint64, UT_WRAPPED_LE64toH(little_endian_64bits), result);
    }
}

/*
 * ----------------------------------------------------
 * Test Case For: CFE_PSP_IsBigEndian
 * bool CFE_PSP_IsBigEndian(void)
 * ----------------------------------------------------
 */
void Test_CFE_PSP_IsBigEndian(void)
{
    CFE_PSP_ENDIAN_INDICATOR = 0;
    UtAssert_BOOL_FALSE(CFE_PSP_IsBigEndian());
    CFE_PSP_ENDIAN_INDICATOR = CFE_PSP_LITTLE_INDICATOR;
    UtAssert_BOOL_FALSE(CFE_PSP_IsBigEndian());
    CFE_PSP_ENDIAN_INDICATOR = CFE_PSP_BIG_INDICATOR;
    UtAssert_BOOL_TRUE(CFE_PSP_IsBigEndian());
}

/*
 * ----------------------------------------------------
 * Test Case For: CFE_PSP_IsLittleEndian
 * bool CFE_PSP_IsLittleEndian(void)
 * ----------------------------------------------------
 */
void Test_CFE_PSP_IsLittleEndian(void)
{
    CFE_PSP_ENDIAN_INDICATOR = 0;
    UtAssert_BOOL_FALSE(CFE_PSP_IsLittleEndian());
    CFE_PSP_ENDIAN_INDICATOR = CFE_PSP_LITTLE_INDICATOR;
    UtAssert_BOOL_TRUE(CFE_PSP_IsLittleEndian());
    CFE_PSP_ENDIAN_INDICATOR = CFE_PSP_BIG_INDICATOR;
    UtAssert_BOOL_FALSE(CFE_PSP_IsLittleEndian());
}

/*
 * ----------------------------------------------------
 * Test Case For: CFE_PSP_ReportEndian
 * void CFE_PSP_ReportEndian(uint8 CheckValue)
 * ----------------------------------------------------
 */
void Test_CFE_PSP_ReportEndian(void)
{
    /* this has no outputs but prints a different message depending on the check value */
    UtAssert_VOIDCALL(CFE_PSP_ReportEndian(0));
    UtAssert_VOIDCALL(CFE_PSP_ReportEndian(CFE_PSP_LITTLE_INDICATOR));
    UtAssert_VOIDCALL(CFE_PSP_ReportEndian(CFE_PSP_BIG_INDICATOR));
}

/*
 * ----------------------------------------------------
 * Test Case For: endian_api_Init
 * void endian_api_Init(uint32 PspModuleId)
 * ----------------------------------------------------
 */
void Test_endian_api_Init(void)
{
    /* no branches here and nothing to check; called for coverage */
    UtAssert_VOIDCALL(endian_api_Init(1));
}

/*
 * Macro to add a test case to the list of tests to execute
 */
#define ADD_TEST(test) UtTest_Add(test, ResetTest, NULL, #test)

void ResetTest(void)
{
    UT_ResetState(0);
}

/*
 * Register the test cases to execute with the unit test tool
 */
void UtTest_Setup(void)
{
    ADD_TEST(Test_endian_api_Init);
    ADD_TEST(Test_CFE_PSP_ReportEndian);
    ADD_TEST(Test_CFE_PSP_IsBigEndian);
    ADD_TEST(Test_CFE_PSP_IsLittleEndian);

    ADD_TEST(Test_CFE_PSP_HtoBE16);
    ADD_TEST(Test_CFE_PSP_HtoLE16);
    ADD_TEST(Test_CFE_PSP_BE16toH);
    ADD_TEST(Test_CFE_PSP_LE16toH);
    ADD_TEST(Test_CFE_PSP_HtoBE32);
    ADD_TEST(Test_CFE_PSP_HtoLE32);
    ADD_TEST(Test_CFE_PSP_BE32toH);
    ADD_TEST(Test_CFE_PSP_LE32toH);
    ADD_TEST(Test_CFE_PSP_HtoBE64);
    ADD_TEST(Test_CFE_PSP_HtoLE64);
    ADD_TEST(Test_CFE_PSP_BE64toH);
    ADD_TEST(Test_CFE_PSP_LE64toH);
}
