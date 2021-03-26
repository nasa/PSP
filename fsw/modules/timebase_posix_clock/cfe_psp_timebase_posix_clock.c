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

/**
 * \file cfe_psp_timebase_posix_clock.c
 *
 * A PSP module to satisfy the PSP time API on systems which
 * do not have a hardware clock register, but do provide a POSIX
 * compliant implementation of clock_gettime() and CLOCK_MONOTONIC
 * that can fulfill this role.
 *
 * The POSIX CLOCK_MONOTONIC is defined as a monotonically increasing
 * clock that has no specific epoch.  It is not affected by local time
 * changes and is not settable.
 *
 * The POSIX interface uses a "struct timespec" which has units in
 * nanoseconds, but this is converted down to units of microseconds for
 * consistency with previous versions of PSP where CFE_PSP_Get_Timebase()
 * returned units of microseconds.
 */

/*
**  System Include Files
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cfe_psp.h"
#include "cfe_psp_module.h"

/*
 * The specific clock ID to use with clock_gettime
 *
 * Linux provides some special (non-posix) clock IDs that also
 * could be relevant/useful:
 *
 * CLOCK_MONOTONIC_COARSE - emphasis on read speed at the (possible?) expense of precision
 * CLOCK_MONOTONIC_RAW - possibly hardware based, not affected by NTP or other sync software
 * CLOCK_BOOTTIME - includes time the system is suspended.
 *
 * Defaulting to the POSIX-specified "MONOTONIC" but it should be possible to use
 * one of the Linux-specific variants if the target system provides it.
 */
#define CFE_PSP_TIMEBASE_REF_CLOCK CLOCK_MONOTONIC

CFE_PSP_MODULE_DECLARE_SIMPLE(timebase_posix_clock);

void timebase_posix_clock_Init(uint32 PspModuleId)
{
    /* Inform the user that this module is in use */
    printf("CFE_PSP: Using POSIX monotonic clock as CFE timebase\n");
}

/*
 * ----------------------------------------------------------------------
 * The CFE_PSP_Get_Timebase() is a wrapper around clock_gettime()
 *
 * Reads the value of the monotonic POSIX clock, and output the value with
 * the whole seconds in the upper 32 and nanoseconds in the lower 32.
 *
 * This variant does minimal conversions - just enough to meet the API.
 * For a normalized output use CFE_PSP_GetTime()
 * ----------------------------------------------------------------------
 */
void CFE_PSP_Get_Timebase(uint32 *Tbu, uint32 *Tbl)
{
    struct timespec now;

    if (clock_gettime(CFE_PSP_TIMEBASE_REF_CLOCK, &now) != 0)
    {
        /* unlikely - but avoids undefined behavior */
        now.tv_sec  = 0;
        now.tv_nsec = 0;
    }

    *Tbu = now.tv_sec & 0xFFFFFFFF;
    *Tbl = now.tv_nsec;
}

/*
 * ----------------------------------------------------------------------
 * The CFE_PSP_GetTime() is also a wrapper around the same clock_gettime()
 *
 * Reads the value of the monotonic POSIX clock, and output the value
 * normalized to an OS_time_t format.
 * ----------------------------------------------------------------------
 */
void CFE_PSP_GetTime(OS_time_t *LocalTime)
{
    struct timespec now;

    if (clock_gettime(CFE_PSP_TIMEBASE_REF_CLOCK, &now) != 0)
    {
        /* unlikely - but avoids undefined behavior */
        now.tv_sec  = 0;
        now.tv_nsec = 0;
    }

    *LocalTime = OS_TimeAssembleFromNanoseconds(now.tv_sec, now.tv_nsec);
}

/******************************************************************************
**  Function:  CFE_PSP_GetTimerTicksPerSecond()
**
**  Purpose:
**    Provides the resolution of the least significant 32 bits of the 64 bit
**    time stamp returned by CFE_PSP_Get_Timebase in timer ticks per second.
**    The timer resolution for accuracy should not be any slower than 1000000
**    ticks per second or 1 us per tick
**
**  Arguments:
**
**  Return:
**    The number of timer ticks per second of the time stamp returned
**    by CFE_PSP_Get_Timebase
*/
uint32 CFE_PSP_GetTimerTicksPerSecond(void)
{
    /* POSIX "struct timespec" resolution is defined as nanoseconds */
    return 1000000000;
}

/******************************************************************************
**  Function:  CFE_PSP_GetTimerLow32Rollover()
**
**  Purpose:
**    Provides the number that the least significant 32 bits of the 64 bit
**    time stamp returned by CFE_PSP_Get_Timebase rolls over.  If the lower 32
**    bits rolls at 1 second, then the CFE_PSP_TIMER_LOW32_ROLLOVER will be 1000000.
**    if the lower 32 bits rolls at its maximum value (2^32) then
**    CFE_PSP_TIMER_LOW32_ROLLOVER will be 0.
**
**  Arguments:
**
**  Return:
**    The number that the least significant 32 bits of the 64 bit time stamp
**    returned by CFE_PSP_Get_Timebase rolls over.
*/
uint32 CFE_PSP_GetTimerLow32Rollover(void)
{
    /* POSIX "struct timespec" resolution is defined as nanoseconds */
    return 1000000000;
}
