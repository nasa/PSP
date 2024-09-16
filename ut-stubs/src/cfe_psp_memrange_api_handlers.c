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
** File: ut_bsp_stubs.c
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

void UT_DefaultHandler_CFE_PSP_GetResetArea(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* int32 CFE_PSP_GetResetArea() */
    cpuaddr *PtrToResetArea  = UT_Hook_GetArgValueByName(Context, "PtrToResetArea", cpuaddr *);
    uint32 * SizeOfResetArea = UT_Hook_GetArgValueByName(Context, "SizeOfResetArea", uint32 *);

    int32  status;
    size_t TempSize;
    void * TempAddr;

    UT_Stub_GetInt32StatusCode(Context, &status);

    if (status >= 0)
    {
        UT_GetDataBuffer(UT_KEY(CFE_PSP_GetResetArea), &TempAddr, &TempSize, NULL);

        *PtrToResetArea  = (cpuaddr)TempAddr;
        *SizeOfResetArea = TempSize;
    }
}

void UT_DefaultHandler_CFE_PSP_GetVolatileDiskMem(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* int32 CFE_PSP_GetVolatileDiskMem() */
    cpuaddr *PtrToVolDisk  = UT_Hook_GetArgValueByName(Context, "PtrToVolDisk", cpuaddr *);
    uint32 * SizeOfVolDisk = UT_Hook_GetArgValueByName(Context, "SizeOfVolDisk", uint32 *);

    int32  status;
    size_t TempSize;
    void * TempAddr;

    UT_Stub_GetInt32StatusCode(Context, &status);

    if (status >= 0)
    {
        UT_GetDataBuffer(UT_KEY(CFE_PSP_GetVolatileDiskMem), &TempAddr, &TempSize, NULL);

        *PtrToVolDisk  = (cpuaddr)TempAddr;
        *SizeOfVolDisk = TempSize;
    }
}

void UT_DefaultHandler_CFE_PSP_GetCFETextSegmentInfo(void *UserObj, UT_EntryKey_t FuncKey,
                                                     const UT_StubContext_t *Context)
{
    /* int32 CFE_PSP_GetCFETextSegmentInfo() */
    cpuaddr *PtrToCFESegment  = UT_Hook_GetArgValueByName(Context, "PtrToCFESegment", cpuaddr *);
    uint32 * SizeOfCFESegment = UT_Hook_GetArgValueByName(Context, "SizeOfCFESegment", uint32 *);

    static uint32 LocalTextSegment;
    int32         status;
    void *        TempAddr;
    size_t        TempSize;

    UT_Stub_GetInt32StatusCode(Context, &status);

    if (status >= 0)
    {
        UT_GetDataBuffer(UT_KEY(CFE_PSP_GetCFETextSegmentInfo), &TempAddr, &TempSize, NULL);
        if (TempAddr == NULL)
        {
            /* Backup -- Set the pointer and size to anything */
            *PtrToCFESegment  = (cpuaddr)&LocalTextSegment;
            *SizeOfCFESegment = sizeof(LocalTextSegment);
        }
        else
        {
            *PtrToCFESegment  = (cpuaddr)TempAddr;
            *SizeOfCFESegment = TempSize;
        }
    }
}

void UT_DefaultHandler_CFE_PSP_GetKernelTextSegmentInfo(void *UserObj, UT_EntryKey_t FuncKey,
                                                        const UT_StubContext_t *Context)
{
    /* int32 CFE_PSP_GetKernelTextSegmentInfo(cpuaddr *PtrToKernelSegment, uint32 *SizeOfKernelSegment) */
    cpuaddr *PtrToKernelSegment  = UT_Hook_GetArgValueByName(Context, "PtrToKernelSegment", cpuaddr *);
    uint32 * SizeOfKernelSegment = UT_Hook_GetArgValueByName(Context, "SizeOfKernelSegment", uint32 *);

    static uint32 LocalTextSegment;
    int32         status;
    void *        TempAddr;
    size_t        TempSize;

    UT_Stub_GetInt32StatusCode(Context, &status);

    if (status >= 0)
    {
        UT_GetDataBuffer(UT_KEY(CFE_PSP_GetKernelTextSegmentInfo), &TempAddr, &TempSize, NULL);
        if (TempAddr == NULL)
        {
            /* Backup -- Set the pointer and size to anything */
            *PtrToKernelSegment  = (cpuaddr)&LocalTextSegment;
            *SizeOfKernelSegment = sizeof(LocalTextSegment);
        }
        else
        {
            *PtrToKernelSegment  = (cpuaddr)TempAddr;
            *SizeOfKernelSegment = TempSize;
        }
    }
}
