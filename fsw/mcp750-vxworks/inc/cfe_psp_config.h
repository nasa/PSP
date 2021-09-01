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

/*
** cfe_psp_config.h
**
*/

#ifndef _cfe_psp_config_
#define _cfe_psp_config_

#include "common_types.h"

#include <stdio.h>
#include <string.h>
#include <vxWorks.h>
#include <sysLib.h>
#include "fppLib.h"
#include "excLib.h"
#include "taskLib.h"
#include "arch/ppc/esfPpc.h"

/**
 * \brief Period of the VxWorks timebase, in nanoseconds
 *
 * This is expressed as a ratio in case it is not a whole number.
 *
 * Multiplying the timebase register by 60 should yield a result
 * in nanoseconds, and then further dividing by the OSAL OS_time_t tick
 * resolution will convert to an OS_time_t compatible value.
 *
 * On the MCP750 - the PPC timebase runs at 60ns period or ~16.67 MHz.
 *
 * Note this is distinct from the VxWorks system timer tick which runs,
 * confusingly, at 60Hz or a ~16.67ms period.
 */
#define CFE_PSP_VX_TIMEBASE_PERIOD_NUMERATOR   60
#define CFE_PSP_VX_TIMEBASE_PERIOD_DENOMINATOR 1

/*
** This define sets the number of memory ranges that are defined in the memory range definition
** table.
*/
#define CFE_PSP_MEM_TABLE_SIZE 10

/**
 * This define sets the maximum number of exceptions
 * that can be stored.
 *
 * It must always be a power of two.
 */
#define CFE_PSP_MAX_EXCEPTION_ENTRIES 4

/*
 * The tick period that will be configured in the RTOS for the simulated
 * time base, in microseconds.  This in turn is used to drive the 1hz clock
 * and other functions.
 *
 * On the MCP750 the sysClockRate runs at 60Hz so this is the same period
 * that the cFE software timebase will be configured at.
 */
#define CFE_PSP_SOFT_TIMEBASE_PERIOD 16666

/*
** Typedef for the layout of the vxWorks boot record structure
**
** This is statically placed at the beginning of system memory (sysMemTop)
** which should be reserved in the kernel.
*/
typedef struct
{
    uint32 bsp_reset_type;
    uint32 spare1;
    uint32 spare2;
    uint32 spare3;

} CFE_PSP_ReservedMemoryBootRecord_t;

/**
 * \brief The data type used by the underlying OS to represent a thread ID.
 */
typedef TASK_ID CFE_PSP_Exception_SysTaskId_t;

/*
** Global variables
*/
typedef struct
{
    UINT32     timebase_upper; /* Upper 32 bits of timebase as sampled by hook */
    UINT32     timebase_lower; /* Lower 32 bits of timebase as sampled by hook */
    int        vector;         /* vector number */
    ESFPPC     esf;            /* Exception stack frame */
    FP_CONTEXT fp;             /* floating point registers */

} CFE_PSP_Exception_ContextDataEntry_t;

/*
** Watchdog minimum and maximum values ( in milliseconds )
*/
#define CFE_PSP_WATCHDOG_MIN (0)
#define CFE_PSP_WATCHDOG_MAX (0xFFFFFFFF)

/*
** Number of EEPROM banks on this platform
*/
#define CFE_PSP_NUM_EEPROM_BANKS 1

/*
 * The alignment to use for each reserved memory block.
 *
 * This is a mask to be applied to each block base address
 *
 * Chosen as the cache line size of the MPC750 processor (32 bytes)
 * such that the blocks will be cached more efficiently.
 */
#define CFE_PSP_MEMALIGN_MASK ((cpuaddr)0x1F)

#endif
