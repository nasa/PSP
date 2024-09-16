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

/**
 * @file
 *
 * Auto-Generated stub implementations for functions defined in cfe_psp_memaccess_api header
 */

#include "cfe_psp_memaccess_api.h"
#include "utgenstub.h"

void UT_DefaultHandler_CFE_PSP_MemCpy(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_MemRead16(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_MemRead32(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_MemRead8(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_MemSet(void *, UT_EntryKey_t, const UT_StubContext_t *);

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_MemCpy()
 * ----------------------------------------------------
 */
int32 CFE_PSP_MemCpy(void *dest, const void *src, uint32 n)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_MemCpy, int32);

    UT_GenStub_AddParam(CFE_PSP_MemCpy, void *, dest);
    UT_GenStub_AddParam(CFE_PSP_MemCpy, const void *, src);
    UT_GenStub_AddParam(CFE_PSP_MemCpy, uint32, n);

    UT_GenStub_Execute(CFE_PSP_MemCpy, Basic, UT_DefaultHandler_CFE_PSP_MemCpy);

    return UT_GenStub_GetReturnValue(CFE_PSP_MemCpy, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_MemRead16()
 * ----------------------------------------------------
 */
int32 CFE_PSP_MemRead16(cpuaddr MemoryAddress, uint16 *uint16Value)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_MemRead16, int32);

    UT_GenStub_AddParam(CFE_PSP_MemRead16, cpuaddr, MemoryAddress);
    UT_GenStub_AddParam(CFE_PSP_MemRead16, uint16 *, uint16Value);

    UT_GenStub_Execute(CFE_PSP_MemRead16, Basic, UT_DefaultHandler_CFE_PSP_MemRead16);

    return UT_GenStub_GetReturnValue(CFE_PSP_MemRead16, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_MemRead32()
 * ----------------------------------------------------
 */
int32 CFE_PSP_MemRead32(cpuaddr MemoryAddress, uint32 *uint32Value)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_MemRead32, int32);

    UT_GenStub_AddParam(CFE_PSP_MemRead32, cpuaddr, MemoryAddress);
    UT_GenStub_AddParam(CFE_PSP_MemRead32, uint32 *, uint32Value);

    UT_GenStub_Execute(CFE_PSP_MemRead32, Basic, UT_DefaultHandler_CFE_PSP_MemRead32);

    return UT_GenStub_GetReturnValue(CFE_PSP_MemRead32, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_MemRead8()
 * ----------------------------------------------------
 */
int32 CFE_PSP_MemRead8(cpuaddr MemoryAddress, uint8 *ByteValue)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_MemRead8, int32);

    UT_GenStub_AddParam(CFE_PSP_MemRead8, cpuaddr, MemoryAddress);
    UT_GenStub_AddParam(CFE_PSP_MemRead8, uint8 *, ByteValue);

    UT_GenStub_Execute(CFE_PSP_MemRead8, Basic, UT_DefaultHandler_CFE_PSP_MemRead8);

    return UT_GenStub_GetReturnValue(CFE_PSP_MemRead8, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_MemSet()
 * ----------------------------------------------------
 */
int32 CFE_PSP_MemSet(void *dest, uint8 value, uint32 n)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_MemSet, int32);

    UT_GenStub_AddParam(CFE_PSP_MemSet, void *, dest);
    UT_GenStub_AddParam(CFE_PSP_MemSet, uint8, value);
    UT_GenStub_AddParam(CFE_PSP_MemSet, uint32, n);

    UT_GenStub_Execute(CFE_PSP_MemSet, Basic, UT_DefaultHandler_CFE_PSP_MemSet);

    return UT_GenStub_GetReturnValue(CFE_PSP_MemSet, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_MemWrite16()
 * ----------------------------------------------------
 */
int32 CFE_PSP_MemWrite16(cpuaddr MemoryAddress, uint16 uint16Value)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_MemWrite16, int32);

    UT_GenStub_AddParam(CFE_PSP_MemWrite16, cpuaddr, MemoryAddress);
    UT_GenStub_AddParam(CFE_PSP_MemWrite16, uint16, uint16Value);

    UT_GenStub_Execute(CFE_PSP_MemWrite16, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_MemWrite16, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_MemWrite32()
 * ----------------------------------------------------
 */
int32 CFE_PSP_MemWrite32(cpuaddr MemoryAddress, uint32 uint32Value)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_MemWrite32, int32);

    UT_GenStub_AddParam(CFE_PSP_MemWrite32, cpuaddr, MemoryAddress);
    UT_GenStub_AddParam(CFE_PSP_MemWrite32, uint32, uint32Value);

    UT_GenStub_Execute(CFE_PSP_MemWrite32, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_MemWrite32, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_MemWrite8()
 * ----------------------------------------------------
 */
int32 CFE_PSP_MemWrite8(cpuaddr MemoryAddress, uint8 ByteValue)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_MemWrite8, int32);

    UT_GenStub_AddParam(CFE_PSP_MemWrite8, cpuaddr, MemoryAddress);
    UT_GenStub_AddParam(CFE_PSP_MemWrite8, uint8, ByteValue);

    UT_GenStub_Execute(CFE_PSP_MemWrite8, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_MemWrite8, int32);
}
