/******************************************************************************
**
** File:  cfe_psp_support.c
**
**      Copyright (c) 2004-2011, United States Government as represented by
**      Administrator for The National Aeronautics and Space Administration.
**      All Rights Reserved.
**
**      This is governed by the NASA Open Source Agreement and may be used,
**      distributed and modified only pursuant to the terms of that agreement.
**
** Purpose:
**   This file contains glue routines between the cFE and the OS Board Support
**   Package (BSP). The functions here allow the cFE to interface functions
**   that are board and OS specific and usually dont fit well in the OS
**   abstraction layer.
**
******************************************************************************/

/*
**  Include Files
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "vxWorks.h"
#include "cacheLib.h"
#include "rebootLib.h"

#include "common_types.h"
#include "osapi.h"
#include "cfe_es.h"           

#include "cfe_psp.h"
#include "cfe_psp_memory.h"
#include "target_config.h"

#define CFE_PSP_CPU_ID               (GLOBAL_CONFIGDATA.Default_CpuId)
#define CFE_PSP_SPACECRAFT_ID        (GLOBAL_CONFIGDATA.Default_SpacecraftId)

/*
 * Track the overall "reserved memory block" at the start of RAM.
 * This single large block is then subdivided into separate areas for CFE use.
 */
extern CFE_PSP_MemoryBlock_t PSP_ReservedMemBlock;

/******************************************************************************
**  Function:  CFE_PSP_Restart()
**
**  Purpose:
**    Provides a common interface to the processor reset
**
**  Arguments:
**    Input - reset_type - Type of reset
**
**  Return:
**    None
******************************************************************************/
void CFE_PSP_Restart(uint32 reset_type)
{
    if (reset_type == CFE_PSP_RST_TYPE_POWERON)
    {
        CFE_PSP_ReservedMemoryMap.BootPtr->bsp_reset_type = CFE_PSP_RST_TYPE_POWERON;
        /*Normally the cache would be flushed but the reserved memory is not cached
         * so the flush is not needed.
         */
        reboot(BOOT_CLEAR);
    }
    else
    {
        CFE_PSP_ReservedMemoryMap.BootPtr->bsp_reset_type = CFE_PSP_RST_TYPE_PROCESSOR;
        /*Normally the cache would be flushed but the reserved memory is not cached
         * so the flush is not needed.
         */
        reboot(BOOT_NORMAL);
    }
}


/******************************************************************************
**  Function:  CFE_PSP_Panic()
**
**  Purpose:
**    Provides a common interface to abort the cFE startup process and return
**    back to the OS.
**
**  Arguments:
**    Input - errorCode - Error code that causes the exit
**
**  Return:
**    None
******************************************************************************/
void CFE_PSP_Panic(int32 errorCode)
{
    char msg[] = "CFE_PSP_Panic Called with error code = 0x%08X. Exiting.\n";
    logMsg(msg,
           (unsigned int)errorCode, 0,0,0,0,0);

    exit(-1);   /* TODO: Need to improve this */
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
**    Input - type - Cache memory type
**    Input - address - Cache memory address
**    Input - size - Cache memory size
**
**  Return:
**    None
******************************************************************************/
void CFE_PSP_FlushCaches(uint32 type, void* address, uint32 size)
{
    /*The cache is managed by the SP0 BSP/VxWorks OS.
     */
}


/******************************************************************************
**  Function:  CFE_PSP_GetProcessorId
**
** Purpose:
**         return the processor ID.
**
**  Arguments:
**    None
**
**  Return:
**    cFE CPU ID
******************************************************************************/
uint32 CFE_PSP_GetProcessorId(void)
{
    return CFE_PSP_CPU_ID;
}


/******************************************************************************
**  Function:  CFE_PSP_GetSpacecraftId
**
**  Purpose:
**    Provides the pre-assigned cFE Spacecraft ID
**
**  Arguments:
**    None
**
**  Return:
**    cFE Spacecraft ID
******************************************************************************/
uint32 CFE_PSP_GetSpacecraftId(void)
{
   return CFE_PSP_SPACECRAFT_ID;
}




