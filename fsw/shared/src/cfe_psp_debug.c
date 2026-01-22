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
 * \file
 * \ingroup  shared
 * \author   dwaine.s.molock@nasa.gov
 *
 *      Contains the implementation for PSP_DEBUG().
 *
 *      This is only compiled when PSP_CONFIG_DEBUG_PRINTF is enabled.
 */

/****************************************************************************************
                                    INCLUDE FILES
 ***************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

/*
 * User defined include files
 */
#include "cfe_psp.h"
#include "osapi.h"

#define PSP_DEBUG_MAX_LINE_LEN  132

uint8 CFE_PSP_DebugLevel = CFE_PSP_DEBUG_LEVEL;

/*----------------------------------------------------------------
 *
 *  Purpose: Outputs a single debug statement to the console
 *
 *-----------------------------------------------------------------*/
void PSP_DebugPrintf(uint32 Level, const char *Func, uint32 Line, const char *Format, ...)
{
    char    prefix[PSP_DEBUG_MAX_LINE_LEN];
    char    buffer[PSP_DEBUG_MAX_LINE_LEN];
    int     actualsz;
    va_list va;

    if (CFE_PSP_DebugLevel >= Level)
    {
        /* build prefix string */
        actualsz = snprintf(prefix, sizeof(prefix), "PSP_DEBUG: %s():%lu ", Func, (unsigned long)Line);
        if (actualsz < 0)
        {
            actualsz = 0;
        }
        else if (actualsz >= PSP_DEBUG_MAX_LINE_LEN)
        {
            actualsz = PSP_DEBUG_MAX_LINE_LEN - 1;
        }
        prefix[actualsz] = 0;

        /* build message str */
        va_start(va, Format);
        actualsz = vsnprintf(buffer, sizeof(buffer), Format, va);
        va_end(va);
        
        if (actualsz < 0)
        {
            actualsz = 0;
        }
        else if (actualsz >= PSP_DEBUG_MAX_LINE_LEN)
        {
            actualsz = PSP_DEBUG_MAX_LINE_LEN - 1;
        }
        buffer[actualsz] = 0;
        
        /* output message strings */
        OS_printf("%s%s", prefix, buffer);
    }
}

