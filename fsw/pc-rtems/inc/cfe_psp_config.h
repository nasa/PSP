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
#include <rtems.h>

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
#define CFE_PSP_MAX_EXCEPTION_ENTRIES 1

/*
 * The tick period that will be configured in the RTOS for the simulated
 * time base, in microseconds.  This in turn is used to drive the 1hz clock
 * and other functions.
 *
 * To minimize jitter in the resulting callbacks, it should be an even
 * divisor of 1000000 usec.
 *
 * Note - 10ms/100Hz is chosen to also allow this same timebase to be
 * used to drive the CFS SCH minor frame callbacks in its default config.
 */
#define CFE_PSP_SOFT_TIMEBASE_PERIOD 10000

/*
** Typedef for the layout of the header in the reserved memory block
*/
typedef struct
{
    /* not currently used in PC-RTEMS */
    uint32 reserved;

} CFE_PSP_ReservedMemoryBootRecord_t;

/**
 * \brief The data type used by the underlying OS to represent a thread ID.
 */
typedef rtems_id CFE_PSP_Exception_SysTaskId_t;

/**
 * \brief Exception context data which is relevant for offline/post-mortem diagnosis.
 *
 * This may be stored in a persistent exception log file for later analysis.
 *
 * On PC-RTEMS, this is reserved for future use.  Exception handling is not
 * currently implemented.
 */
typedef struct
{
    uint32 reserved; /* prevent empty structure */
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
 * Using 128 bytes as this is the cache line size of many
 * modern processors.
 */
#define CFE_PSP_MEMALIGN_MASK ((cpuaddr)0x7F)

#endif
