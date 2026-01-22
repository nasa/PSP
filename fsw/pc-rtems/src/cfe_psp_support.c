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

/******************************************************************************
** File:  cfe_psp_support.c
**
** Purpose:
**   This file contains glue routines between the cFE and the OS Board Support Package ( BSP ).
**   The functions here allow the cFE to interface functions that are board and OS specific
**   and usually don't fit well in the OS abstraction layer.
**
** History:
**   2005/06/05  Alan Cudmore    | Initial version,
**
******************************************************************************/

/*
**  Include Files
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
** cFE includes
*/
#include "common_types.h"
#include "osapi.h"

/*
** Types and prototypes for this module
*/
#include "cfe_psp.h"
#include "cfe_psp_memory.h"

/*
 * The preferred way to obtain the CFE tunable values at runtime is via
 * the dynamically generated configuration object.  This allows a single build
 * of the PSP to be completely CFE-independent.
 */
#include "target_config.h"

#define CFE_PSP_CPU_ID        (GLOBAL_CONFIGDATA.Default_CpuId)
#define CFE_PSP_CPU_NAME      (GLOBAL_CONFIGDATA.Default_CpuName)
#define CFE_PSP_SPACECRAFT_ID (GLOBAL_CONFIGDATA.Default_SpacecraftId)

/*
 * Track the overall "reserved memory block" at the start of RAM.
 * This single large block is then subdivided into separate areas for CFE use.
 */
extern CFE_PSP_MemoryBlock_t PcRtems_ReservedMemBlock;

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CFE_PSP_Restart(uint32 resetType)
{

    CFE_PSP_DeleteProcessorReservedMemory();

    /*
     * Record the reset type for the next boot.
     */
    CFE_PSP_ReservedMemoryMap.BootPtr->NextResetType = resetType;
    CFE_PSP_ReservedMemoryMap.BootPtr->ValidityFlag  = CFE_PSP_BOOTRECORD_VALID;

    CFE_PSP_FlushCaches(1, PcRtems_ReservedMemBlock.BlockPtr, PcRtems_ReservedMemBlock.BlockSize);
    exit(EXIT_FAILURE);
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CFE_PSP_Panic(int32 ErrorCode)
{
    printf("%s called with error code = 0x%08X. Exiting.\n", __func__, (unsigned int)ErrorCode);
    OS_ApplicationExit(ErrorCode);
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CFE_PSP_FlushCaches(uint32 type, void *address, uint32 size)
{
    if (type == 1)
    {
        /* cacheTextUpdate((void *)address, size); */
    }
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
uint32 CFE_PSP_GetProcessorId(void)
{
    return CFE_PSP_CPU_ID;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
uint32 CFE_PSP_GetSpacecraftId(void)
{
    return CFE_PSP_SPACECRAFT_ID;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
const char *CFE_PSP_GetProcessorName(void)
{
    return CFE_PSP_CPU_NAME;
}
