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
 * Auto-Generated stub implementations for functions defined in cfe_psp_endian header
 */

#include "cfe_psp_endian.h"
#include "utgenstub.h"

void UT_DefaultHandler_CFE_PSP_BE16toH(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_BE32toH(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_BE64toH(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_HtoBE16(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_HtoBE32(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_HtoBE64(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_HtoLE16(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_HtoLE32(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_HtoLE64(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_LE16toH(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_LE32toH(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_LE64toH(void *, UT_EntryKey_t, const UT_StubContext_t *);

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_BE16toH()
 * ----------------------------------------------------
 */
uint16 CFE_PSP_BE16toH(uint16 big_endian_16bits)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_BE16toH, uint16);

    UT_GenStub_AddParam(CFE_PSP_BE16toH, uint16, big_endian_16bits);

    UT_GenStub_Execute(CFE_PSP_BE16toH, Basic, UT_DefaultHandler_CFE_PSP_BE16toH);

    return UT_GenStub_GetReturnValue(CFE_PSP_BE16toH, uint16);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_BE32toH()
 * ----------------------------------------------------
 */
uint32 CFE_PSP_BE32toH(uint32 big_endian_32bits)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_BE32toH, uint32);

    UT_GenStub_AddParam(CFE_PSP_BE32toH, uint32, big_endian_32bits);

    UT_GenStub_Execute(CFE_PSP_BE32toH, Basic, UT_DefaultHandler_CFE_PSP_BE32toH);

    return UT_GenStub_GetReturnValue(CFE_PSP_BE32toH, uint32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_BE64toH()
 * ----------------------------------------------------
 */
uint64 CFE_PSP_BE64toH(uint64 big_endian_64bits)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_BE64toH, uint64);

    UT_GenStub_AddParam(CFE_PSP_BE64toH, uint64, big_endian_64bits);

    UT_GenStub_Execute(CFE_PSP_BE64toH, Basic, UT_DefaultHandler_CFE_PSP_BE64toH);

    return UT_GenStub_GetReturnValue(CFE_PSP_BE64toH, uint64);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_HtoBE16()
 * ----------------------------------------------------
 */
uint16 CFE_PSP_HtoBE16(uint16 host_16bits)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_HtoBE16, uint16);

    UT_GenStub_AddParam(CFE_PSP_HtoBE16, uint16, host_16bits);

    UT_GenStub_Execute(CFE_PSP_HtoBE16, Basic, UT_DefaultHandler_CFE_PSP_HtoBE16);

    return UT_GenStub_GetReturnValue(CFE_PSP_HtoBE16, uint16);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_HtoBE32()
 * ----------------------------------------------------
 */
uint32 CFE_PSP_HtoBE32(uint32 host_32bits)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_HtoBE32, uint32);

    UT_GenStub_AddParam(CFE_PSP_HtoBE32, uint32, host_32bits);

    UT_GenStub_Execute(CFE_PSP_HtoBE32, Basic, UT_DefaultHandler_CFE_PSP_HtoBE32);

    return UT_GenStub_GetReturnValue(CFE_PSP_HtoBE32, uint32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_HtoBE64()
 * ----------------------------------------------------
 */
uint64 CFE_PSP_HtoBE64(uint64 host_64bits)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_HtoBE64, uint64);

    UT_GenStub_AddParam(CFE_PSP_HtoBE64, uint64, host_64bits);

    UT_GenStub_Execute(CFE_PSP_HtoBE64, Basic, UT_DefaultHandler_CFE_PSP_HtoBE64);

    return UT_GenStub_GetReturnValue(CFE_PSP_HtoBE64, uint64);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_HtoLE16()
 * ----------------------------------------------------
 */
uint16 CFE_PSP_HtoLE16(uint16 host_16bits)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_HtoLE16, uint16);

    UT_GenStub_AddParam(CFE_PSP_HtoLE16, uint16, host_16bits);

    UT_GenStub_Execute(CFE_PSP_HtoLE16, Basic, UT_DefaultHandler_CFE_PSP_HtoLE16);

    return UT_GenStub_GetReturnValue(CFE_PSP_HtoLE16, uint16);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_HtoLE32()
 * ----------------------------------------------------
 */
uint32 CFE_PSP_HtoLE32(uint32 host_32bits)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_HtoLE32, uint32);

    UT_GenStub_AddParam(CFE_PSP_HtoLE32, uint32, host_32bits);

    UT_GenStub_Execute(CFE_PSP_HtoLE32, Basic, UT_DefaultHandler_CFE_PSP_HtoLE32);

    return UT_GenStub_GetReturnValue(CFE_PSP_HtoLE32, uint32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_HtoLE64()
 * ----------------------------------------------------
 */
uint64 CFE_PSP_HtoLE64(uint64 host_64bits)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_HtoLE64, uint64);

    UT_GenStub_AddParam(CFE_PSP_HtoLE64, uint64, host_64bits);

    UT_GenStub_Execute(CFE_PSP_HtoLE64, Basic, UT_DefaultHandler_CFE_PSP_HtoLE64);

    return UT_GenStub_GetReturnValue(CFE_PSP_HtoLE64, uint64);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_LE16toH()
 * ----------------------------------------------------
 */
uint16 CFE_PSP_LE16toH(uint16 little_endian_16bits)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_LE16toH, uint16);

    UT_GenStub_AddParam(CFE_PSP_LE16toH, uint16, little_endian_16bits);

    UT_GenStub_Execute(CFE_PSP_LE16toH, Basic, UT_DefaultHandler_CFE_PSP_LE16toH);

    return UT_GenStub_GetReturnValue(CFE_PSP_LE16toH, uint16);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_LE32toH()
 * ----------------------------------------------------
 */
uint32 CFE_PSP_LE32toH(uint32 little_endian_32bits)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_LE32toH, uint32);

    UT_GenStub_AddParam(CFE_PSP_LE32toH, uint32, little_endian_32bits);

    UT_GenStub_Execute(CFE_PSP_LE32toH, Basic, UT_DefaultHandler_CFE_PSP_LE32toH);

    return UT_GenStub_GetReturnValue(CFE_PSP_LE32toH, uint32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_LE64toH()
 * ----------------------------------------------------
 */
uint64 CFE_PSP_LE64toH(uint64 little_endian_64bits)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_LE64toH, uint64);

    UT_GenStub_AddParam(CFE_PSP_LE64toH, uint64, little_endian_64bits);

    UT_GenStub_Execute(CFE_PSP_LE64toH, Basic, UT_DefaultHandler_CFE_PSP_LE64toH);

    return UT_GenStub_GetReturnValue(CFE_PSP_LE64toH, uint64);
}
