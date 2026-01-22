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

/*
**  Include Files
*/
#include <stdio.h>
#include <string.h>
#include <pthread.h>

/*
** cFE includes
*/
#include "cfe_psp.h"
#include "cfe_psp_config.h"
#include "cfe_psp_module.h"
#include "cfe_psp_backtrace.h"

#include <signal.h>
#include <stdlib.h>
#include <errno.h>

/* Declare backtrace accessor */
bt_accessor_t CFE_PSP_BacktraceAcc;

CFE_PSP_MODULE_DECLARE_SIMPLE(backtrace_qnx);

/*
 * ------------------------------------------
 * Init Routine
 * ------------------------------------------
 */
void backtrace_qnx_Init(uint32 PspModuleId)
{
    /* Inform the user that this module is in use */
    printf("CFE_PSP: QNX Backtrace Module Initialized...\n");
}

/*
 * ------------------------------------------
 * Init Routine
 * ------------------------------------------
 */
void CFE_PSP_Backtrace_Init(void)
{
    /* Initialize backtrace accessor */
    if (bt_init_accessor(&CFE_PSP_BacktraceAcc, BT_SELF) == -1)
    {
        OS_printf("CFE_PSP: %s:%i could not initialize backtrace: %s (%i)%s\n", __func__, __LINE__,
            "bt_init_accessor", errno, strerror(errno));
        abort(); /* abort() is preferable to exit(EXIT_FAILURE), as it may create a core file for debug */
    }
}

/*
 * ------------------------------------------
 * Backtrace Routine
 * ------------------------------------------
 */
int32 CFE_PSP_Backtrace(CFE_PSP_BacktraceEntry_t *Entry, void *ContextPtr, int32 MaxEntries)
{
   int32 NumAddrs;

   NumAddrs = bt_get_backtrace(&CFE_PSP_BacktraceAcc, Entry, MaxEntries);

   PSP_DEBUG("CFE_PSP: %s:%i collecting backtrace [ NumAddrs: %i Info: %s (%i) %s ]\n", __func__, __LINE__,
      NumAddrs, "bt_init_accessor/bt_get_backtrace", errno, strerror(errno));

   return NumAddrs;
}
