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

#include "target_config.h"

/*
** Functions
*/

/*****************************************************************************/
/**
** \brief CFE_PSP_WriteToCDS stub function
**
** \par Description
**        This function is used to mimic the response of the PSP function
**        CFE_PSP_WriteToCDS.
**
** \par Assumptions, External Events, and Notes:
**        None
**
** \returns
**        Returns either OS_SUCCESS, OS_ERROR, or a user-defined value.
**
******************************************************************************/
void UT_DefaultHandler_CFE_PSP_WriteToCDS(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* int32 CFE_PSP_WriteToCDS(const void *PtrToDataToWrite, uint32 CDSOffset, uint32 NumBytes) */
    const void *PtrToDataToWrite = UT_Hook_GetArgValueByName(Context, "PtrToDataToWrite", const void *);
    uint32      CDSOffset        = UT_Hook_GetArgValueByName(Context, "CDSOffset", uint32);
    uint32      NumBytes         = UT_Hook_GetArgValueByName(Context, "NumBytes", uint32);

    uint8 *BufPtr;
    size_t CdsSize;
    size_t Position;
    int32  status;

    UT_Stub_GetInt32StatusCode(Context, &status);

    if (status >= 0)
    {
        UT_GetDataBuffer(UT_KEY(CFE_PSP_WriteToCDS), (void **)&BufPtr, &CdsSize, &Position);
        if (BufPtr != NULL && (CDSOffset + NumBytes) <= CdsSize)
        {
            memcpy(BufPtr + CDSOffset, PtrToDataToWrite, NumBytes);
        }
    }
}

/*****************************************************************************/
/**
** \brief CFE_PSP_ReadFromCDS stub function
**
** \par Description
**        This function is used to mimic the response of the PSP function
**        CFE_PSP_ReadFromCDS.
**
** \par Assumptions, External Events, and Notes:
**        None
**
** \returns
**        Returns either OS_SUCCESS, OS_ERROR, or a user-defined value.
**
******************************************************************************/
void UT_DefaultHandler_CFE_PSP_ReadFromCDS(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* int32 CFE_PSP_ReadFromCDS(void *PtrToDataFromRead, uint32 CDSOffset, uint32 NumBytes) */
    void * PtrToDataFromRead = UT_Hook_GetArgValueByName(Context, "PtrToDataFromRead", void *);
    uint32 CDSOffset         = UT_Hook_GetArgValueByName(Context, "CDSOffset", uint32);
    uint32 NumBytes          = UT_Hook_GetArgValueByName(Context, "NumBytes", uint32);

    uint8 *BufPtr;
    size_t CdsSize;
    size_t Position;
    int32  status;

    UT_Stub_GetInt32StatusCode(Context, &status);

    if (status >= 0)
    {
        UT_GetDataBuffer(UT_KEY(CFE_PSP_ReadFromCDS), (void **)&BufPtr, &CdsSize, &Position);
        if (BufPtr != NULL && (CDSOffset + NumBytes) <= CdsSize)
        {
            memcpy(PtrToDataFromRead, BufPtr + CDSOffset, NumBytes);
        }
    }
}

/*****************************************************************************/
/**
** \brief CFE_PSP_GetCDSSize stub function
**
** \par Description
**        This function is used to mimic the response of the PSP function
**        CFE_PSP_GetCDSSize.
**
** \par Assumptions, External Events, and Notes:
**        None
**
** \returns
**        Returns either OS_SUCCESS or OS_ERROR.
**
******************************************************************************/
void UT_DefaultHandler_CFE_PSP_GetCDSSize(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* int32 CFE_PSP_GetCDSSize(uint32 *SizeOfCDS) */
    uint32 *SizeOfCDS = UT_Hook_GetArgValueByName(Context, "SizeOfCDS", uint32 *);

    int32  status;
    size_t TempSize;

    UT_Stub_GetInt32StatusCode(Context, &status);

    if (status >= 0)
    {
        UT_GetDataBuffer(UT_KEY(CFE_PSP_GetCDSSize), NULL, &TempSize, NULL);
        *SizeOfCDS = TempSize;
    }
}
