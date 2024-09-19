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
 * Auto-Generated stub implementations for functions defined in cfe_psp_cds_api header
 */

#include "cfe_psp_cds_api.h"
#include "utgenstub.h"

void UT_DefaultHandler_CFE_PSP_GetCDSSize(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_ReadFromCDS(void *, UT_EntryKey_t, const UT_StubContext_t *);
void UT_DefaultHandler_CFE_PSP_WriteToCDS(void *, UT_EntryKey_t, const UT_StubContext_t *);

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_GetCDSSize()
 * ----------------------------------------------------
 */
int32 CFE_PSP_GetCDSSize(uint32 *SizeOfCDS)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_GetCDSSize, int32);

    UT_GenStub_AddParam(CFE_PSP_GetCDSSize, uint32 *, SizeOfCDS);

    UT_GenStub_Execute(CFE_PSP_GetCDSSize, Basic, UT_DefaultHandler_CFE_PSP_GetCDSSize);

    return UT_GenStub_GetReturnValue(CFE_PSP_GetCDSSize, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_ReadFromCDS()
 * ----------------------------------------------------
 */
int32 CFE_PSP_ReadFromCDS(void *PtrToDataFromRead, uint32 CDSOffset, uint32 NumBytes)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_ReadFromCDS, int32);

    UT_GenStub_AddParam(CFE_PSP_ReadFromCDS, void *, PtrToDataFromRead);
    UT_GenStub_AddParam(CFE_PSP_ReadFromCDS, uint32, CDSOffset);
    UT_GenStub_AddParam(CFE_PSP_ReadFromCDS, uint32, NumBytes);

    UT_GenStub_Execute(CFE_PSP_ReadFromCDS, Basic, UT_DefaultHandler_CFE_PSP_ReadFromCDS);

    return UT_GenStub_GetReturnValue(CFE_PSP_ReadFromCDS, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_WriteToCDS()
 * ----------------------------------------------------
 */
int32 CFE_PSP_WriteToCDS(const void *PtrToDataToWrite, uint32 CDSOffset, uint32 NumBytes)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_WriteToCDS, int32);

    UT_GenStub_AddParam(CFE_PSP_WriteToCDS, const void *, PtrToDataToWrite);
    UT_GenStub_AddParam(CFE_PSP_WriteToCDS, uint32, CDSOffset);
    UT_GenStub_AddParam(CFE_PSP_WriteToCDS, uint32, NumBytes);

    UT_GenStub_Execute(CFE_PSP_WriteToCDS, Basic, UT_DefaultHandler_CFE_PSP_WriteToCDS);

    return UT_GenStub_GetReturnValue(CFE_PSP_WriteToCDS, int32);
}
