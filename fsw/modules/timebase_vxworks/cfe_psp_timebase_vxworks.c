/************************************************************************
 * NASA Docket No. GSC-18,719-1, and identified as “core Flight System: Bootes”
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
 * \file
 *
 * A PSP module to implement the PSP time API via the VxWorks
 * vxTimeBaseGet() routine.  The VxWorks timebase is a 64 bit
 * monotonically increasing counter implemented as a hardware
 * register in PowerPC chips, and is described in the Power ISA
 * specification v2.06b section 7.2.
 *
 * The vxTimeBaseGet() function is provided by the VxWorks BSP and
 * returns the value of this register as a pair of UINT32 values,
 * containing the upper and lower 32 bit words.
 *
 * Note that the tick rate of the clock is not specified by Power
 * architecture and is system-dependent.  This needs to have some
 * platform-specific tuning to normalize the tick units.
 */

/*
**  System Include Files
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <vxWorks.h>
#include <sysLib.h>
#include <vxLib.h>
#include <arch/ppc/vxPpcLib.h>

#include "osapi-clock.h"

#include "cfe_psp.h"
#include "cfe_psp_config.h"
#include "cfe_psp_module.h"

/**
 * \brief The number that the least significant 32 bits of the 64 bit
 *        time stamp returned by CFE_PSP_Get_Timebase rolls over.  If the lower 32
 *        bits rolls at 1 second, then the CFE_PSP_TIMER_LOW32_ROLLOVER will be 1000000.
 *        if the lower 32 bits rolls at its maximum value (2^32) then
 *        CFE_PSP_TIMER_LOW32_ROLLOVER will be 0.
 */
#define CFE_PSP_TIMER_LOW32_ROLLOVER 0

typedef struct
{
    uint32 TicksPerSecond;
    uint32 OSTimeConvNumerator;
    uint32 OSTimeConvDenominator;
} PSP_VxWorks_Timebase_Global_t;

PSP_VxWorks_Timebase_Global_t PSP_VxWorks_Timebase_Global;

CFE_PSP_MODULE_DECLARE_SIMPLE(timebase_vxworks);

void timebase_vxworks_Init(uint32 PspModuleId)
{
    uint64 TicksPerSec;
    uint32 CheckFactor;
    uint32 RatioN;
    uint32 RatioD;
    uint32 QuotientN;
    uint32 QuotientD;

    /*
     * The ticks per second is the reciprocal of the period -
     * precomputed here so the value can be returned via API.
     * Note this may not be an exact value.  The API is limited
     * in this regard.
     */
    TicksPerSec = 1000000000;
    TicksPerSec *= CFE_PSP_VX_TIMEBASE_PERIOD_DENOMINATOR;
    TicksPerSec /= CFE_PSP_VX_TIMEBASE_PERIOD_NUMERATOR;

    /*
     * Precompute the ratio for conversion to OS_time_t.
     *
     * This is the timebase period divided by OS_TIME_TICK_RESOLUTION_NS,
     * which may not be a whole number.
     */
    RatioN = CFE_PSP_VX_TIMEBASE_PERIOD_NUMERATOR;
    RatioD = CFE_PSP_VX_TIMEBASE_PERIOD_DENOMINATOR;
    RatioD *= OS_TIME_TICK_RESOLUTION_NS;

    /*
     * This just does a brute-force sequential search for a common factors.
     * The numbers are generally not very large, so this should be quick,
     * and it is only done once during init.
     *
     * Reducing the fraction at runtime avoids issues with possibly choosing
     * hardcoded values that do not divide evenly.
     */
    CheckFactor = 2;
    while (RatioN >= CheckFactor && RatioD >= CheckFactor)
    {
        QuotientN = RatioN / CheckFactor;
        QuotientD = RatioD / CheckFactor;

        if ((QuotientN * CheckFactor) == RatioN && (QuotientD * CheckFactor) == RatioD)
        {
            /* It is a common factor, save quotient try again. */
            RatioN = QuotientN;
            RatioD = QuotientD;

            continue;
        }

        /*
         * Not a common factor, move on.
         *
         * Technically this only needs to advance to the next prime,
         * but for simplicity, just go sequential.
         */
        ++CheckFactor;
    }

    /* Inform the user that this module is in use */
    printf("CFE_PSP: Set up VxWorks timebase, %lu ticks/sec, OS_time_t ratio=%lu/%lu\n", (unsigned long)TicksPerSec,
           (unsigned long)RatioN, (unsigned long)RatioD);

    /* Save the final reduced fraction for use in CFE_PSP_GetTime() */
    PSP_VxWorks_Timebase_Global.OSTimeConvNumerator   = RatioN;
    PSP_VxWorks_Timebase_Global.OSTimeConvDenominator = RatioD;
    PSP_VxWorks_Timebase_Global.TicksPerSecond        = TicksPerSec & 0xFFFFFFFF;
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
    return PSP_VxWorks_Timebase_Global.TicksPerSecond;
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
    return 0;
}

/******************************************************************************
**  Function:  CFE_PSP_Get_Timebase()
**
**  Purpose:
**    Provides a common interface to system timebase. This routine
**    is in the BSP because it is sometimes implemented in hardware and
**    sometimes taken care of by the RTOS.
**
**  Arguments:
**
**  Return:
**  Timebase register value
*/
void CFE_PSP_Get_Timebase(uint32 *Tbu, uint32 *Tbl)
{
    vxTimeBaseGet((UINT32 *)Tbu, (UINT32 *)Tbl);
}

/******************************************************************************
**  Function:  CFE_PSP_GetTime()
**
**  Purpose: Gets the value of the timebase from the hardware normalized as OS_time_t
**
**  Arguments: LocalTime - where the time is returned through
**
**  Note this requires a platform-specific conversion factor to translate timebase
**  ticks into real time ticks.
**
******************************************************************************/

void CFE_PSP_GetTime(OS_time_t *LocalTime)
{
    uint64 NormalizedTicks;
    uint32 RegUpper;
    uint32 RegLower;

    vxTimeBaseGet(&RegUpper, &RegLower);

    /*
     * Convert to a uint64 value.  Per the Power ISA definition, this
     * register wraps at (2^60)-1.  However at the tick rate implemented
     * here this would require running continuously (without a power
     * cycle or reset) for over 2000 years to reach that point, so
     * for all practical purposes it does not roll over.
     */
    NormalizedTicks = RegUpper;
    NormalizedTicks <<= 32;
    NormalizedTicks |= RegLower;

    /*
     * Apply the pre-computed conversion to OS_time_t.
     *
     * This ratio has been reduced during init such that it should minimize
     * the impact on overall range of the 64-bit value.
     */
    NormalizedTicks *= PSP_VxWorks_Timebase_Global.OSTimeConvNumerator;
    NormalizedTicks /= PSP_VxWorks_Timebase_Global.OSTimeConvDenominator;

    /* Output the value as an OS_time_t */
    *LocalTime = (OS_time_t) {NormalizedTicks};

} /* end CFE_PSP_GetLocalTime */
