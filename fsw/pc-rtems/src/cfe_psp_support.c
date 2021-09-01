/*
**  GSC-18128-1, "Core Flight Executive Version 6.7"
**
**  Copyright (c) 2006-2019 United States Government as represented by
**  the Administrator of the National Aeronautics and Space Administration.
**  All Rights Reserved.
**
**  Licensed under the Apache License, Version 2.0 (the "License");
**  you may not use this file except in compliance with the License.
**  You may obtain a copy of the License at
**
**    http://www.apache.org/licenses/LICENSE-2.0
**
**  Unless required by applicable law or agreed to in writing, software
**  distributed under the License is distributed on an "AS IS" BASIS,
**  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**  See the License for the specific language governing permissions and
**  limitations under the License.
*/

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

/******************************************************************************
**  Function:  CFE_PSP_Restart()
**
**  Purpose:
**    Provides a common interface to the processor reset.
**
**  Arguments:
**    reset_type  : Type of reset.
**
**  Return:
**    (none)
*/

void CFE_PSP_Restart(uint32 reset_type)
{

    CFE_PSP_FlushCaches(1, PcRtems_ReservedMemBlock.BlockPtr, PcRtems_ReservedMemBlock.BlockSize);
    OS_printf("CFE_PSP_Restart is not implemented on this platform ( yet ! )\n");
    exit(-1);
}

/******************************************************************************
**  Function:  CFE_PSP_Panic()
**
**  Purpose:
**    Provides a common interface to abort the cFE startup process and return
**    back to the OS.
**
**  Arguments:
**    ErrorCode  : Reason for Exiting.
**
**  Return:
**    (none)
*/

void CFE_PSP_Panic(int32 ErrorCode)
{
    printf("CFE_PSP_Panic Called with error code = 0x%08X. Exiting.\n", (unsigned int)ErrorCode);
    OS_ApplicationExit(ErrorCode);
}

/******************************************************************************
**  Function:  CFE_PSP_FlushCaches()
**
**  Purpose:
**    Provides a common interface to flush the processor caches. This routine
**    is in the BSP because it is sometimes implemented in hardware and
**    sometimes taken care of by the RTOS.
**
**  Arguments:
**
**  Return:
**    (none)
*/

void CFE_PSP_FlushCaches(uint32 type, void *address, uint32 size)
{
    if (type == 1)
    {
        /* cacheTextUpdate((void *)address, size); */
    }
}

/*
** Name: CFE_PSP_GetProcessorId
**
** Purpose:
**         return the processor ID.
**
**
** Parameters:
**
** Global Inputs: None
**
** Global Outputs: None
**
**
**
** Return Values: Processor ID
*/
uint32 CFE_PSP_GetProcessorId(void)
{
    return (CFE_PSP_CPU_ID);
}

/*
** Name: CFE_PSP_GetSpacecraftId
**
** Purpose:
**         return the spacecraft ID.
**
** Parameters:
**
** Global Inputs: None
**
** Global Outputs: None
**
**
** Return Values: Spacecraft ID
*/
uint32 CFE_PSP_GetSpacecraftId(void)
{
    return (CFE_PSP_SPACECRAFT_ID);
}

/*
** Name: CFE_PSP_GetProcessorName
**
** Purpose:
**         return the processor name.
**
** Parameters:
**
** Global Inputs: None
**
** Global Outputs: None
**
**
** Return Values: Processor name
*/
const char *CFE_PSP_GetProcessorName(void)
{
    return (CFE_PSP_CPU_NAME);
}
