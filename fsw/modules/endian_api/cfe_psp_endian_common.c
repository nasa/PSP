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
 * Map the PSP endian conversion routines to the system-provided endian.h file
 * This is done using static inline functions, such that the result should be
 * optimized as much as possible.
 */

/*
** Include Files
*/
#include "cfe_psp_module.h"
#include "cfe_psp_endian.h"

CFE_PSP_MODULE_DECLARE_SIMPLE(endian_api);

/* Note these are not supposed to be exposed publicly but UT needs to access them */
uint8_t CFE_PSP_ENDIAN_INDICATOR;

/* these just need to be different.  Making them substantially different */
#define CFE_PSP_BIG_INDICATOR    0x25
#define CFE_PSP_LITTLE_INDICATOR 0x9a

bool CFE_PSP_IsBigEndian(void)
{
    return (CFE_PSP_ENDIAN_INDICATOR == CFE_PSP_BIG_INDICATOR);
}

bool CFE_PSP_IsLittleEndian(void)
{
    return (CFE_PSP_ENDIAN_INDICATOR == CFE_PSP_LITTLE_INDICATOR);
}

void CFE_PSP_ReportEndian(uint8 CheckValue)
{
    const char *CpuType;

    /* Keep it in the global for future reference */
    CFE_PSP_ENDIAN_INDICATOR = CheckValue;

    if (CFE_PSP_IsBigEndian())
    {
        CpuType = "BIG";
    }
    else if (CFE_PSP_IsLittleEndian())
    {
        CpuType = "LITTLE";
    }
    else
    {
        CpuType = "UNDEFINED";
    }

    printf("CFE_PSP: Host CPU Endian=%s\n", CpuType);
}

void endian_api_Init(uint32 PspModuleId)
{
    const uint16 Check = (CFE_PSP_BIG_INDICATOR << 8) | CFE_PSP_LITTLE_INDICATOR;

    /* Inform the user that this module is in use and what endianness we think this CPU has */
    CFE_PSP_ReportEndian(*((const char *)&Check));
}
