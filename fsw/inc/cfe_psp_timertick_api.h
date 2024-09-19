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

/*
**  Author:  A. Cudmore
**
**  Purpose:  This file contains the cFE Platform Support Package(PSP)
**            prototypes.
**            The PSP routines serve as the "glue" between the RTOS and
**            the cFE Flight Software. The routines fill gaps that are not
**            really considered part of the OS Abstraction, but are required
**            for the cFE flight software implementation. It is possible that
**            some of these routines could migrate into the OS AL.
**
*/

#ifndef CFE_PSP_TIMERTICK_API_H
#define CFE_PSP_TIMERTICK_API_H

/******************************************************************************
 INCLUDE FILES
 ******************************************************************************/

#include "common_types.h"
#include "osapi.h"

#include "cfe_psp_error.h"

/******************************************************************************
 MACRO DEFINITIONS
 ******************************************************************************/

/**
 * @brief The name of the software/RTOS timebase for general system timers.
 *
 * This name may be referred to by CFE TIME and/or SCH when setting up its own timers.
 */
#define CFE_PSP_SOFT_TIMEBASE_NAME "cFS-Master"

/******************************************************************************
 FUNCTION PROTOTYPES
 ******************************************************************************/

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Sample/Read a monotonic platform clock with normalization
 *
 * Outputs an OS_time_t value indicating the time elapsed since an epoch. The
 * epoch is not defined, but typically represents the system boot time. The
 * value increases continuously over time and cannot be reset by software.
 *
 * This is similar to the CFE_PSP_Get_Timebase(), but additionally it normalizes
 * the output value to an OS_time_t, thereby providing consistent units to the
 * calling application. Any OSAL-provided routine that accepts OS_time_t inputs
 * may be used to convert this value into other standardized time units.
 *
 * @note This should refer to the same time domain as CFE_PSP_Get_Timebase(),
 * the primary difference being the format and units of the output value.
 *
 * @sa CFE_PSP_Get_Timebase()
 *
 * @param[out] LocalTime Value of PSP tick counter as OS_time_t
 */
void CFE_PSP_GetTime(OS_time_t *LocalTime);

/*--------------------------------------------------------------------------------------*/
/**
 * Provides the resolution of the least significant 32 bits of the 64-bit time
 * stamp returned by CFE_PSP_Get_Timebase in timer ticks per second. The timer
 * resolution for accuracy should not be any slower than 1000000 ticks per
 * second or 1 us (microsecond) per tick
 *
 * @return The number of timer ticks per second of the time stamp returned by
 * CFE_PSP_Get_Timebase
 */
uint32 CFE_PSP_GetTimerTicksPerSecond(void);

/*--------------------------------------------------------------------------------------*/
/**
 * Provides the number that the least significant 32 bits of the 64-bit time
 * stamp returned by CFE_PSP_Get_Timebase rolls over. If the lower 32 bits rolls
 * at 1 second, then the CFE_PSP_TIMER_LOW32_ROLLOVER will be 1000000. If the
 * lower 32 bits rolls at its maximum value (2^32) then
 * CFE_PSP_TIMER_LOW32_ROLLOVER will be 0.
 *
 * @return The number that the least significant 32 bits of the 64-bit time
 * stamp returned by CFE_PSP_Get_Timebase rolls over.
 */
uint32 CFE_PSP_GetTimerLow32Rollover(void);

/**
 * @brief Sample/Read a monotonic platform clock without normalization
 *
 * Provides a common interface to system timebase. This routine is in the BSP
 * because it is sometimes implemented in hardware and sometimes taken care of
 * by the RTOS.
 *
 * This is defined as a free-running, monotonically-increasing tick counter. The
 * epoch is not defined, but typically is the system boot time, and the value
 * increases indefinitely as the system runs. The tick period/rate is also not
 * defined.
 *
 * Rollover events - where the range of representable values is exceeded - are
 * theoretically possible, but would take many years of continuous uptime to
 * occur (typically hundreds of years, if not thousands). System designers
 * should ensure that the actual tick rate and resulting timebase range is
 * sufficiently large to ensure that rollover is not a concern.
 *
 * @note This is a "raw" value from the underlying platform with minimal/no
 * conversions or normalization applied. Neither the epoch nor the resolution of
 * this tick counter is specified, and it may vary from platform to platform.
 * Use the CFE_PSP_GetTime() function to sample the timebase and also convert
 * the units into a normalized/more consistent form.
 *
 * @sa CFE_PSP_GetTime()
 *
 * @param[out] Tbu Buffer to hold the upper 32 bits of a 64-bit tick counter
 * @param[out] Tbl Buffer to hold the lower 32 bits of a 64-bit tick counter
 */
void CFE_PSP_Get_Timebase(uint32 *Tbu, uint32 *Tbl);

#endif
