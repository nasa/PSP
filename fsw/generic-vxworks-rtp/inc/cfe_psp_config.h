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

#ifndef CFE_PSP_CONFIG_H
#define CFE_PSP_CONFIG_H

#include "common_types.h"

#include <stdio.h>
#include <string.h>
#include <vxWorks.h>
#include <sysLib.h>
#include <signal.h>
#include <time.h>

/**
 * \brief Period of the VxWorks timebase, in nanoseconds
 *
 * This is expressed as a ratio in case it is not a whole number.
 *
 * Multiplying the timebase register by 60 should yield a result
 * in nanoseconds, and then further dividing by the OSAL OS_time_t tick
 * resolution will convert to an OS_time_t compatible value.
 *
 * This needs to be set to the correct timebase for the BSP 
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
#define CFE_PSP_MAX_EXCEPTION_ENTRIES        4
#define CFE_PSP_MAX_EXCEPTION_BACKTRACE_SIZE 16

/*
 * The tick period that will be configured in the RTOS for the simulated
 * time base, in microseconds.  This in turn is used to drive the 1hz clock
 * and other functions.
 *
 * On the <TBD> the sysClockRate runs at 60Hz so this is the same period
 * that the cFE software timebase will be configured at.
 */
#define CFE_PSP_SOFT_TIMEBASE_PERIOD 16666


/*
 * A random 32-bit value that is used as the "validity flag"
 * of the PC-Linux boot record structure.  This is simply
 * a value that is unlikely to occur unless specifically set.
 */
#define CFE_PSP_BOOTRECORD_VALID   ((uint32)0x2aebe984)
#define CFE_PSP_BOOTRECORD_INVALID (~CFE_PSP_BOOTRECORD_VALID)

/*
 * The amount of time to wait for an orderly shutdown
 * in the event of a call to CFE_PSP_Restart()
 *
 * If this expires, then an abnormal exit/abort() is triggered.
 */
#define CFE_PSP_RESTART_DELAY 10000

/* use the "USR1" signal to wake the idle thread when an exception occurs */
#define CFE_PSP_EXCEPTION_EVENT_SIGNAL SIGUSR1



#define CFE_PSP_SHM_NAME_LENGTH        32
#define CFE_PSP_CPU_NAME_LENGTH        32
#define CFE_PSP_RESET_NAME_LENGTH      10
#define CFE_PSP_CFS_ID_LENGTH          16

#define CFE_PSP_CFS_ID                 "cfs1"

/*
** Typedef for the layout of the vxWorks boot record structure
**
** This is statically placed at the beginning of system memory (sysMemTop)
** which should be reserved in the kernel.
*/
typedef struct
{
    uint32 bsp_reset_type;
    uint32 ValidityFlag;
    uint32 NextResetType;
} CFE_PSP_ReservedMemoryBootRecord_t;

/*
 * The state of the PSP "idle task"
 *
 * This is the main/initial thread that runs early init,
 * it is NOT an OSAL task.
 *
 * Once initialized, this thread goes idle and waits for
 * asynchronous events to occur, and resumes with an orderly
 * shutdown if requested.
 */
typedef struct
{
    pthread_t     ThreadID;
    volatile bool ShutdownReq;
} CFE_PSP_IdleTaskState_t;


/*
** Structure for the Command line parameters
*/
typedef struct
{
    char   ResetType[CFE_PSP_RESET_NAME_LENGTH]; /* Reset type can be "PO" for Power on or "PR" for Processor Reset */
    uint32 GotResetType;                         /* did we get the ResetType parameter ? */

    uint32 SubType;    /* Reset Sub Type ( 1 - 5 )  */
    uint32 GotSubType; /* did we get the ResetSubType parameter ? */

    char   CpuName[CFE_PSP_CPU_NAME_LENGTH]; /* CPU Name */
    uint32 GotCpuName;                       /* Did we get a CPU Name ? */

    char   CfsId[CFE_PSP_CFS_ID_LENGTH];      /* CFS ID */
    uint32 GotCfsId;                          /* Did we get a cFS Id? */

    uint32 CpuId;    /* CPU ID */
    uint32 GotCpuId; /* Did we get a CPU Id ?*/

    uint32 SpacecraftId;    /* Spacecraft ID */
    uint32 GotSpacecraftId; /* Did we get a Spacecraft ID */
} CFE_PSP_CommandData_t;


/**
 * \brief The data type used by the underlying OS to represent a thread ID.
 */
typedef TASK_ID CFE_PSP_Exception_SysTaskId_t;

/*
** Global variables
*/

typedef struct
{
    struct timespec event_time;
    siginfo_t       si;

    /*
     * Note this is a variably-filled array based on the number of addresses
     * reported by the library.  It should be last.
     */
    void *bt_addrs[CFE_PSP_MAX_EXCEPTION_BACKTRACE_SIZE];
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

/*
 * Information about the "idle task" --
 * this is used by exception handling to wake it when an event occurs
 */
extern CFE_PSP_IdleTaskState_t CFE_PSP_IdleTaskState;

#endif
