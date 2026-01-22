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
#include <ucontext.h> // For ucontext_t in signal handler
#include <stdlib.h>
#include <errno.h>

/* Global unwind variables */
unw_cursor_t Cursor;
unw_context_t Context;
unw_proc_info_t Info;


CFE_PSP_MODULE_DECLARE_SIMPLE(backtrace_libunwind);

/*
 * ------------------------------------------
 * Init Routine
 * ------------------------------------------
 */
void backtrace_libunwind_Init(uint32 PspModuleId)
{
    /* Inform the user that this module is in use */
    printf("CFE_PSP: LIBUNWIND Backtrace Module Initialized...\n");
}

/*
 * ------------------------------------------
 * Init Routine
 * ------------------------------------------
 */
void CFE_PSP_Backtrace_Init(void)
{
}

/*
 * ------------------------------------------
 * Backtrace Routine
 * ------------------------------------------
 */
int32 CFE_PSP_Backtrace(CFE_PSP_BacktraceEntry_t *Entry, void *ContextPtr, int32 MaxEntries)
{
   int32 NumAddrs = 0;

   if (Entry != NULL)
   {
       /* Init the unwind context */
       Context = *(unw_context_t *)ContextPtr;

       /* Init unwind cursor for local execution context */
       unw_init_local(&Cursor, &Context);

       /* loop through stack frame */
       while ((MaxEntries > 0) && (unw_step(&Cursor) > 0))
       {
           /* Get instruction pointer (IP) and stack pointer (SP) registers */
           Entry->RegIp = Entry->RegSp = 0xDEADBEEF;
           unw_get_reg(&Cursor, UNW_REG_IP, &Entry->RegIp);
           unw_get_reg(&Cursor, UNW_REG_SP, &Entry->RegSp);

           /* Get symbol name and offset */
           if (unw_get_proc_name(&Cursor, Entry->SymName, CFE_PSP_BACKTRACE_SYM_NAME_LEN, &Entry->SymOffset) != 0)
           {
               strncpy(Entry->SymName, "<unknown>", CFE_PSP_BACKTRACE_SYM_NAME_LEN);
               Entry->SymOffset = 0;
           }
           else
           {
               Entry->SymName[CFE_PSP_BACKTRACE_SYM_NAME_LEN - 1] = '\0';
           }

           /* Display bracktrace info */
           PSP_DEBUG("CFE_PSP_Backtrace: [%02u] SP: 0x%lx PC: 0x%lx (%s+0x%lx)\n", NumAddrs, Entry->RegSp, Entry->RegIp, Entry->SymName, Entry->SymOffset);

           /* update entry pointer and counters */
           NumAddrs++;
           Entry++;
           MaxEntries--;
       }
   }

   return NumAddrs;
}
