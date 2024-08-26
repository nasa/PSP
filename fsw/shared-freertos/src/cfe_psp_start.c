/************************************************************************
 * NASA Docket No. GSC-18,719-1, and identified as “core Flight System: Bootes”
 *
 *  Copyright (c) 2024 Universidade Federal do Rio Grande do Sul (UFRGS)
 *
 *
 *  Copyright (c) 2021 Patrick Paul
 *  SPDX-License-Identifier: MIT-0
 *
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
** File:  cfe_psp_start.c
**
** \file     cfe_psp_start.c
** \brief    Purpose: cFE PSP main entry point.
** \ingroup  freertos
** \author   Patrick Paul (https://github.com/pztrick)
** \author   Fabio Benevenuti (UFRGS)
**/


#include "cfe_psp.h"
#include "cfe_psp_config.h"
#include "cfe_psp_memory.h"
#include "cfe_psp_module.h"

// target_config.h provides GLOBAL_CONFIGDATA object for CFE runtime settings
#include <target_config.h>

// PSP needs to call the CFE entry point
#define CFE_PSP_MAIN_FUNCTION (*GLOBAL_CONFIGDATA.CfeConfig->SystemMain)

// CFE needs a startup script file
#define CFE_PSP_NONVOL_STARTUP_FILE (GLOBAL_CONFIGDATA.CfeConfig->NonvolStartupFile)


int CFE_PSP_Setup(void)
{
    OS_printf("CFE PSP Setup called. No action.\n");
    return CFE_PSP_SUCCESS;
}

void CFE_PSP_Panic(int32 ErrorCode)
{
    #if defined(__unix__)
    #elif defined(__arm__)
    //__asm("bkpt 1");
    #else
    #error
    #endif

    // #if (sizeof(long) == sizeof(int32))
    OS_printf("CFE PSP Panic. ErrorCode:%ld .\n", (long int)ErrorCode);
    // #elif (sizeof(int) == sizeof(int32))
    // OS_printf("CFE PSP Panic. ErrorCode:%d .\n", ErrorCode);
    // #else
    // #error
    // #endif

    // vTaskEndScheduler();
    OS_ApplicationExit(ErrorCode);
}

// OSAL:main() invokes PSP:OS_Application_Startup() inside a FreeRTOS task
void OS_Application_Startup(void)
{
    int32 Status;
    uint32 reset_type;
    uint32 reset_subtype;

    /*
    ** Initialize the OS API data structures
    */
    Status = OS_API_Init();
    if (Status != OS_SUCCESS)
    {
        /* irrecoverable error if OS_API_Init() fails. */
        /* note: use printf here, as OS_printf may not work */
        OS_printf("CFE_PSP: OS_API_Init() failure\n");
        CFE_PSP_Panic(Status);
    }

    /*
    ** Setup the pointer to the reserved area in vxWorks.
    ** This must be done before any of the reset variables are used.
    */
    CFE_PSP_SetupReservedMemoryMap();

    /*
    ** Initialize the statically linked modules (if any)
    */
    CFE_PSP_ModuleInit();


    if(CFE_PSP_Setup() != CFE_PSP_SUCCESS){
        CFE_PSP_Panic(CFE_PSP_ERROR);
    }

    // @FIXME should try to read reset_type from NVM BootPtr
    reset_type = CFE_PSP_RST_TYPE_POWERON;
    reset_subtype = CFE_PSP_RST_SUBTYPE_POWER_CYCLE;
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
