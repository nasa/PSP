/*
** cfe_psp_config.h
**
**      Copyright (c) 2004-2011, United States Government as represented by
**      Administrator for The National Aeronautics and Space Administration.
**      All Rights Reserved.
**
**      This is governed by the NASA Open Source Agreement and may be used,
**      distributed and modified only pursuant to the terms of that agreement.
**
*/

#ifndef _cfe_psp_config_
#define _cfe_psp_config_

#include "common_types.h"

#include <stdio.h>
#include <string.h>
#include <vxWorks.h>
#include <sysLib.h>
#include "speLib.h"
#include "excLib.h"
#include "taskLib.h"
#include "arch/ppc/esfPpc.h"
#include "fppLib.h"

/*
** This define sets the number of memory ranges that are defined in the memory range defintion
** table.
*/
#define CFE_PSP_MEM_TABLE_SIZE 10

/**
 * This define sets the maximum number of exceptions
 * that can be stored.
 *
 * It must always be a power of two.
 */
#define CFE_PSP_MAX_EXCEPTION_ENTRIES       4

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
    UINT32      timebase_upper; /* Upper 32 bits of timebase as sampled by hook */
    UINT32      timebase_lower; /* Lower 32 bits of timebase as sampled by hook */
    int         vector;         /* vector number */
    ESFPPC      esf;            /* Exception stack frame */
    FP_CONTEXT  fp;             /* floating point registers */

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
 * Chosen as the cache line size of the SP0 processor (32 bytes)
 * such that the blocks will be cached more efficiently.
 */
#define CFE_PSP_MEMALIGN_MASK  ((cpuaddr)0x1F)

/* The task and task priority for existing VxWorks task.
 */
typedef struct
{
    const char * VxWorksTaskName;
    int32        VxWorksTaskPriority;
} CFE_PSP_OS_Task_and_priority_t;


#endif  /* _cfe_psp_config_ */


