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

#ifndef CFE_PSP_BACKTRACE_H
#define CFE_PSP_BACKTRACE_H

#include <libunwind.h>

#include "common_types.h"

/*
** Global variables
*/
#define CFE_PSP_BACKTRACE_SYM_NAME_LEN 64

typedef struct
{
    unw_word_t RegIp;
    unw_word_t RegSp;
    unw_word_t SymOffset;
    char       SymName[CFE_PSP_BACKTRACE_SYM_NAME_LEN];
} CFE_PSP_BacktraceEntry_t;

/* ------------------------------------------------------------- */
/**
 * @brief Initialize Backtrace interface
 */
void CFE_PSP_Backtrace_Init(void);

/* ------------------------------------------------------------- */
/**
 * @brief Collect backtrace information
 *
 * @param[out]   Entry Pointer to store backtrace entries
 * @param[inout] ContextPtr Abstract context data
 * @param[in]    MaxEntries Maximum number of backtrace entries to collect
 *
 * @retval int32 Number of backtrace entries collected
 */
int32 CFE_PSP_Backtrace(CFE_PSP_BacktraceEntry_t *Entry, void *ContextPtr, int32 MaxEntries);

#endif
