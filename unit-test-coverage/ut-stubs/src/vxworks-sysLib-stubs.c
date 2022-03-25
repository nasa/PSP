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

/* PSP coverage stub replacement for sysLib.h */
#include <string.h>
#include <stdlib.h>
#include "utstubs.h"

#include "PCS_sysLib.h"

int PCS_sysClkRateGet(void)
{
    return (UT_DEFAULT_IMPL_RC(PCS_sysClkRateGet, 10000));
}
char *PCS_sysMemTop(void)
{
    int32 Status;
    char *BufPtr;

    BufPtr = NULL;
    Status = UT_DEFAULT_IMPL(PCS_sysMemTop);
    if (Status == 0)
    {
        UT_GetDataBuffer(UT_KEY(PCS_sysMemTop), (void **)&BufPtr, NULL, NULL);
    }

    return BufPtr;
}

void PCS_PciOutByte(uint32_t address, uint8_t data)
{
    UT_DEFAULT_IMPL(PCS_PciOutByte);
}
void PCS_PciOutLong(uint32_t address, uint32_t data)
{
    UT_DEFAULT_IMPL(PCS_PciOutLong);
}
void PCS_sysPciWrite32(uint32_t address, uint32_t data)
{
    UT_DEFAULT_IMPL(PCS_sysPciWrite32);
}
void PCS_sysPciRead32(uint32_t address, uint32_t *data)
{
    UT_DEFAULT_IMPL(PCS_sysPciRead32);
}

unsigned int PCS_GetWrsKernelTextStart(void)
{
    return (UT_DEFAULT_IMPL(PCS_GetWrsKernelTextStart));
}

unsigned int PCS_GetWrsKernelTextEnd(void)
{
    return (UT_DEFAULT_IMPL(PCS_GetWrsKernelTextEnd));
}
