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

/* PSP coverage stub replacement for rtems_bsdnet.h */
#include <stdlib.h>
#include <string.h>
#include "utstubs.h"

#include "PCS_drv_pci_pciConfigLib.h"
#include "PCS_vxWorks.h"

void UT_DefaultHandler_PCS_pciConfigInWord(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* PCS_STATUS PCS_pciConfigInWord(int busNo, int deviceNo, int funcNo, int offset, uint16 *pData) */
    uint16 *pData = UT_Hook_GetArgValueByName(Context, "pData", uint16 *);
    int32   iRetCode;

    UT_Stub_GetInt32StatusCode(Context, &iRetCode);

    if (iRetCode == PCS_OK)
    {
        UT_Stub_CopyToLocal(FuncKey, (uint16 *)pData, sizeof(*pData));
    }
}