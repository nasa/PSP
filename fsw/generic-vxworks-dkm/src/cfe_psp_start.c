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
** File:  cfe_psp_start.c
**
** Purpose:
**   cFE PSP main entry point.
**
** History:
**   2004/09/23  J.P. Swinski    | Initial version,
**   2004/10/01  P.Kutt          | Replaced OS API task delay with VxWorks functions
**                                 since OS API is initialized later.
**   2016/04/07  M.Grubb         | Updated for PSP version 1.3
**
******************************************************************************/

/*
**  Include Files
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "vxWorks.h"
#include "sysLib.h"
#include "taskLib.h"
#include "ramDrv.h"
#include "dosFsLib.h"
#include "xbdBlkDev.h"
#include "errnoLib.h"
#include "usrLib.h"
#include "cacheLib.h"

/*
** cFE includes
*/
#include "common_types.h"
#include "osapi.h"

#include "cfe_psp.h"
#include "cfe_psp_memory.h"
#include "cfe_psp_module.h"

/*
**  External Declarations
*/

/*
 * The preferred way to obtain the CFE tunable values at runtime is via
 * the dynamically generated configuration object.  This allows a single build
 * of the PSP to be completely CFE-independent.
 */
#include "target_config.h"

#define CFE_PSP_MAIN_FUNCTION       (*GLOBAL_CONFIGDATA.CfeConfig->SystemMain)
#define CFE_PSP_NONVOL_STARTUP_FILE (GLOBAL_CONFIGDATA.CfeConfig->NonvolStartupFile)

/******************************************************************************
**
**  Purpose:
**    Application startup entry point from OSAL BSP.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
void OS_Application_Startup(void)
{
    int       TicksPerSecond;
    uint32    reset_type;
    uint32    reset_subtype;
    osal_id_t fs_id;
    int32     Status;

    /*
    ** Initialize the OS API
    */
    Status = OS_API_Init();
    if (Status != OS_SUCCESS)
    {
        /* irrecoverable error if OS_API_Init() fails. */
        /* note: use printf here, as OS_printf may not work */
        printf("CFE_PSP: OS_API_Init() failure\n");
        CFE_PSP_Panic(Status);

        /*
         * normally CFE_PSP_Panic() does not return, except
         * during unit testing.  This return avoids executing
         * the rest of this function in that case.
         */
        return;
    }

    /*
    ** Set up the virtual FS mapping for the "/cf" directory
    ** Currently, the generic VxWorks 7 DKM works with a ROMFS statically
    ** built into the VIP since that is easily supportable across
    ** most platforms. However, this may need to change based on
    ** specfic needs. 
    */
    Status = OS_FileSysAddFixedMap(&fs_id, CFE_PSP_CF_ROMFS_VIRTUAL_MAPPING, "/cf");
    if (Status != OS_SUCCESS)
    {
        /* Print for informational purposes --
         * startup can continue, but loads may fail later, depending on config. */
        OS_printf("CFE_PSP: OS_FileSysAddFixedMap() failure: %d\n", (int)Status);
    }

    /*
    ** Delay for one second.
    */
    TicksPerSecond = sysClkRateGet();
    (void)taskDelay(TicksPerSecond);

    /*
    ** Setup the pointer to the reserved area in vxWorks.
    ** This must be done before any of the reset variables are used.
    */
    CFE_PSP_SetupReservedMemoryMap();

    /*
    ** Initialize the statically linked modules (if any)
    */
    CFE_PSP_ModuleInit();

    /*
    ** Determine Reset type by reading the hardware reset register.
    ** (If any?)
    */
    reset_type    = CFE_PSP_RST_TYPE_POWERON;
    reset_subtype = CFE_PSP_RST_SUBTYPE_POWER_CYCLE;

    /*
     * If CFE fails to boot with a processor reset,
     * then make sure next time it uses a power on reset.
     */
    if (reset_type == CFE_PSP_RST_TYPE_PROCESSOR)
    {
        CFE_PSP_ReservedMemoryMap.BootPtr->bsp_reset_type = CFE_PSP_RST_TYPE_POWERON;
    }

    /*
    ** Initialize the reserved memory
    */
    CFE_PSP_InitProcessorReservedMemory(reset_type);

    /*
    ** Call cFE entry point. This will return when cFE startup
    ** is complete.
    */
    CFE_PSP_MAIN_FUNCTION(reset_type, reset_subtype, 1, CFE_PSP_NONVOL_STARTUP_FILE);
}
