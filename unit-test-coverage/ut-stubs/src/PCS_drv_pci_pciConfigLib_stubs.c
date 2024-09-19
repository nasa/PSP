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
 * Auto-Generated stub implementations for functions defined in PCS_drv_pci_pciConfigLib header
 */

#include "PCS_drv_pci_pciConfigLib.h"
#include "utgenstub.h"

void UT_DefaultHandler_PCS_pciConfigInWord(void *, UT_EntryKey_t, const UT_StubContext_t *);

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_pciConfigInWord()
 * ----------------------------------------------------
 */
PCS_STATUS PCS_pciConfigInWord(int busNo, int deviceNo, int funcNo, int offset, uint16_t *pData)
{
    UT_GenStub_SetupReturnBuffer(PCS_pciConfigInWord, PCS_STATUS);

    UT_GenStub_AddParam(PCS_pciConfigInWord, int, busNo);
    UT_GenStub_AddParam(PCS_pciConfigInWord, int, deviceNo);
    UT_GenStub_AddParam(PCS_pciConfigInWord, int, funcNo);
    UT_GenStub_AddParam(PCS_pciConfigInWord, int, offset);
    UT_GenStub_AddParam(PCS_pciConfigInWord, uint16_t *, pData);

    UT_GenStub_Execute(PCS_pciConfigInWord, Basic, UT_DefaultHandler_PCS_pciConfigInWord);

    return UT_GenStub_GetReturnValue(PCS_pciConfigInWord, PCS_STATUS);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_pciFindDevice()
 * ----------------------------------------------------
 */
PCS_STATUS PCS_pciFindDevice(int vendorId, int deviceId, int index, int *pBusNo, int *pDeviceNo, int *pFuncNo)
{
    UT_GenStub_SetupReturnBuffer(PCS_pciFindDevice, PCS_STATUS);

    UT_GenStub_AddParam(PCS_pciFindDevice, int, vendorId);
    UT_GenStub_AddParam(PCS_pciFindDevice, int, deviceId);
    UT_GenStub_AddParam(PCS_pciFindDevice, int, index);
    UT_GenStub_AddParam(PCS_pciFindDevice, int *, pBusNo);
    UT_GenStub_AddParam(PCS_pciFindDevice, int *, pDeviceNo);
    UT_GenStub_AddParam(PCS_pciFindDevice, int *, pFuncNo);

    UT_GenStub_Execute(PCS_pciFindDevice, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_pciFindDevice, PCS_STATUS);
}
