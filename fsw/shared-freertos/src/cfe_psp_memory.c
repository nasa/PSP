/*
 * Copyright 2021 Patrick Paul
 * SPDX-License-Identifier: Apache-2.0 AND (Apache-2.0 OR MIT-0)
 * See further attribution at end of this file.
 */

#include <string.h>

#include "cfe_psp.h"
#include "cfe_psp_config.h"
#include "cfe_psp_memory.h"

#include "os-shared-globaldefs.h" // for OS_DebugPrintf()

#include "target_config.h"
#include "cfe_mission_cfg.h"
#include "cfe_platform_cfg.h"
//#include "cfe_es.h"
//#include "cfe_time.h"
#include "cfe_es_resetdata_typedef.h"
//#include "cfe_es_global.h"

// target_config.h provides GLOBAL_CONFIGDATA object for CFE runtime settings
#include <target_config.h>


// memory regions
#define CFE_PSP_CDS_SIZE (GLOBAL_CONFIGDATA.CfeConfig->CdsSize)
#define CFE_PSP_RESET_AREA_SIZE (GLOBAL_CONFIGDATA.CfeConfig->ResetAreaSize)
#define CFE_PSP_USER_RESERVED_SIZE (GLOBAL_CONFIGDATA.CfeConfig->UserReservedSize)
#define CFE_PSP_RAM_DISK_SECTOR_SIZE (GLOBAL_CONFIGDATA.CfeConfig->RamDiskSectorSize)
#define CFE_PSP_RAM_DISK_NUM_SECTORS (GLOBAL_CONFIGDATA.CfeConfig->RamDiskTotalSectors)

// gross size of psp memory to be allocated
//#define CFE_PSP_RESERVED_MEMORY_SIZE (156 * 1024)

// memory record type sizes
#define CFE_PSP_BOOT_RECORD_SIZE (sizeof(CFE_PSP_ReservedMemoryBootRecord_t))
#define CFE_PSP_EXCEPTION_RECORD_SIZE (sizeof(CFE_PSP_ExceptionStorage_t))


// cfe_psp_memory.h defines this type
CFE_PSP_ReservedMemoryMap_t CFE_PSP_ReservedMemoryMap = { 0 }; 

// allocate memory in a special memory region named ".psp_reserved" in linker script
// @FIXME determine whether to place CDS, other regions in NVM or other memory
__attribute__ ((section(".psp_reserved")))
__attribute__ ((aligned (8)))
char pspReservedMemoryAlloc[CFE_PSP_RESERVED_MEMORY_SIZE];


// zero-initialize certain memory depending on the reset type
int32 CFE_PSP_InitProcessorReservedMemory(uint32 reset_type)
{
    // @FIXME not implemented yet
    // memory may persist or be zero-initialized depending on linker memory region .psp_reserved
    OS_printf("CFE_PSP: Reset type %s.\n", 
       ( reset_type==CFE_PSP_RST_TYPE_POWERON)?"POWERON (Clear all)":"not POWERON (preserve disk, CDS and user reserved memory" );

    /*
     * Clear the segments only on a POWER ON reset
     *
     * Newly-created segments should already be zeroed out,
     * but this ensures it.
     */
    if ( reset_type == CFE_PSP_RST_TYPE_POWERON )
    {  
        //clean all except ram disk
        OS_printf("CFE_PSP: Clearing out CFE CDS Shared memory segment.\n");
        memset(CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr, 0, CFE_PSP_CDS_SIZE);
        OS_printf("CFE_PSP: Clearing out CFE Reset Shared memory segment.\n");
        memset(CFE_PSP_ReservedMemoryMap.ResetMemory.BlockPtr, 0, CFE_PSP_RESET_AREA_SIZE);
        OS_printf("CFE_PSP: Clearing out CFE User Reserved Shared memory segment.\n");
        memset(CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockPtr, 0, CFE_PSP_USER_RESERVED_SIZE);
        OS_printf("CFE_PSP: Clearing out CFE Boot Record memory segment.\n");
        memset(CFE_PSP_ReservedMemoryMap.BootPtr, 0, sizeof(*CFE_PSP_ReservedMemoryMap.BootPtr));
        OS_printf("CFE_PSP: Clearing out CFE Exception Record memory segment.\n");
        memset(CFE_PSP_ReservedMemoryMap.ExceptionStoragePtr, 0, sizeof(*CFE_PSP_ReservedMemoryMap.ExceptionStoragePtr));

        /*
         * If an unclean shutdown occurs, try to do a PROCESSOR reset next.
         * This will attempt to preserve the exception and reset log content.
         */
        /*
        ** Set the default reset type in case a watchdog reset occurs 
        */
        CFE_PSP_ReservedMemoryMap.BootPtr->bsp_reset_type = CFE_PSP_RST_TYPE_PROCESSOR;

    }
    else
    {
        OS_printf("CFE_PSP: unclean reset.\n");
        /*
         * If an unclean shutdown occurs after a PROCESSOR reset, then next time should
         * be a POWERON reset.
         */
        CFE_PSP_ReservedMemoryMap.BootPtr->bsp_reset_type = CFE_PSP_RST_TYPE_PROCESSOR;
    }

    /*
     * Reset the boot record validity flag (always).
     *
     * If an unclean shutdown occurs, such as a software crash or abort, this
     * will remain in the shm structure and it can be detected at startup.
     *
     * This can be used to differentiate between an intentional and unintentional
     * processor reset.
     *
     * If a directed shutdown occurs (via CFE_PSP_Restart) then this
     * is overwritten with the valid value.
     */
    //CFE_PSP_ReservedMemoryMap.BootPtr->ValidityFlag = CFE_PSP_BOOTRECORD_INVALID;
    
 
    return CFE_PSP_SUCCESS;
}

// assign the pointers for these memory regions:
// Boot Record, Exception Logging, Reset Reason, CDS, Volatile Disk, User Reserved
void CFE_PSP_SetupReservedMemoryMap(void){
    cpuaddr ReservedMemoryAddr;

    size_t BootRecordSize;
    size_t ExcRecordSize;
    size_t ResetSize;
    size_t CDSSize;
    size_t UserReservedSize;
    size_t VolatileDiskSize;
    size_t RequiredSize;

    // FBV 2024-01-10 Paranoid
    // is cpuaddr a uintptr_t
    // can it handle pointer arithmetics with byte increment?
    ReservedMemoryAddr = 0;
    ReservedMemoryAddr += 1;
    if (ReservedMemoryAddr != 1) {
        OS_DebugPrintf(1, __func__, __LINE__, "cpuaddr pointer arithmetics is not byte sized, ReservedMemoryAddr = %u\n", (unsigned int) ReservedMemoryAddr);
        return;
    }


    BootRecordSize = CFE_PSP_BOOT_RECORD_SIZE;
    ExcRecordSize = CFE_PSP_EXCEPTION_RECORD_SIZE;
    ResetSize = CFE_PSP_RESET_AREA_SIZE;
    VolatileDiskSize = (CFE_PSP_RAM_DISK_SECTOR_SIZE * CFE_PSP_RAM_DISK_NUM_SECTORS);
    CDSSize = CFE_PSP_CDS_SIZE;
    UserReservedSize = CFE_PSP_USER_RESERVED_SIZE;

    BootRecordSize = (BootRecordSize + CFE_PSP_MEMALIGN_MASK) & ~CFE_PSP_MEMALIGN_MASK;
    ExcRecordSize = (ExcRecordSize + CFE_PSP_MEMALIGN_MASK) & ~CFE_PSP_MEMALIGN_MASK;
    ResetSize = (ResetSize + CFE_PSP_MEMALIGN_MASK) & ~CFE_PSP_MEMALIGN_MASK;
    CDSSize = (CDSSize + CFE_PSP_MEMALIGN_MASK) & ~CFE_PSP_MEMALIGN_MASK;
    VolatileDiskSize = (VolatileDiskSize + CFE_PSP_MEMALIGN_MASK) & ~CFE_PSP_MEMALIGN_MASK;
    UserReservedSize = (UserReservedSize + CFE_PSP_MEMALIGN_MASK) & ~CFE_PSP_MEMALIGN_MASK;

    // calculate the required size and warn if not able to malloc
    RequiredSize = 0;
    RequiredSize += BootRecordSize;
    RequiredSize += ExcRecordSize;
    RequiredSize += ResetSize;
    RequiredSize += VolatileDiskSize;
    RequiredSize += CDSSize;
    RequiredSize += UserReservedSize;


    if((unsigned int) RequiredSize > CFE_PSP_RESERVED_MEMORY_SIZE){
        OS_DebugPrintf(1, __func__, __LINE__, "PSP required reserved memory = %u bytes\n", (unsigned int) RequiredSize);
        OS_DebugPrintf(1, __func__, __LINE__, "Not enough memory available for PSP CFE reserved sections.\n");

        OS_DebugPrintf(1, __func__, __LINE__, "PSP required BootRecordSize memory = %u bytes\n", (unsigned int) BootRecordSize);
        OS_DebugPrintf(1, __func__, __LINE__, "PSP required ExcRecordSize memory = %u bytes\n", (unsigned int) ExcRecordSize);
        OS_DebugPrintf(1, __func__, __LINE__, "PSP required ResetSize/Reset area segment size memory = %u bytes\n", (unsigned int) ResetSize);
        #if 1
        {
            CFE_ES_ResetData_t x;
            OS_DebugPrintf(1, __func__, __LINE__, "    required CFE_ES_ResetData_t memory = %u bytes\n", (unsigned int) sizeof(x));
            OS_DebugPrintf(1, __func__, __LINE__, "    required CFE_ES_ERLog_MetaData_t memory = %u bytes\n", (unsigned int) sizeof(CFE_ES_ERLog_MetaData_t));
            OS_DebugPrintf(1, __func__, __LINE__, "    required CFE_ES_ResetData_t::ERLog memory = %u bytes\n", (unsigned int) sizeof(x.ERLog));
            OS_DebugPrintf(1, __func__, __LINE__, "    required CFE_ES_ResetData_t::SystemLog memory = %u bytes\n", (unsigned int) sizeof(x.SystemLog));
            OS_DebugPrintf(1, __func__, __LINE__, "    required CFE_ES_PerfData_t memory = %u bytes\n", (unsigned int) sizeof(CFE_ES_PerfData_t));
            OS_DebugPrintf(1, __func__, __LINE__, "    required CFE_ES_ResetVariables_t memory = %u bytes\n", (unsigned int) sizeof(CFE_ES_ResetVariables_t));
            OS_DebugPrintf(1, __func__, __LINE__, "    required CFE_TIME_ResetVars_t memory = %u bytes\n", (unsigned int) sizeof(CFE_TIME_ResetVars_t));
            OS_DebugPrintf(1, __func__, __LINE__, "    required CFE_EVS_Log_t memory = %u bytes\n", (unsigned int) sizeof(CFE_EVS_Log_t));
        }
        #endif
        OS_DebugPrintf(1, __func__, __LINE__, "PSP required VolatileDiskSize memory = %u bytes\n", (unsigned int) VolatileDiskSize);
        OS_DebugPrintf(1, __func__, __LINE__, "PSP required CDSSize/CDS segment size memory = %u bytes\n", (unsigned int) CDSSize);
        OS_DebugPrintf(1, __func__, __LINE__, "PSP required UserReservedSize/User reserved area segment size memory = %u bytes\n", (unsigned int) UserReservedSize);

        return;
    }

    ReservedMemoryAddr = (cpuaddr)pspReservedMemoryAlloc;

    CFE_PSP_ReservedMemoryMap.BootPtr = (void*) ReservedMemoryAddr;
    ReservedMemoryAddr += BootRecordSize;

    CFE_PSP_ReservedMemoryMap.ExceptionStoragePtr = (void*) ReservedMemoryAddr;
    ReservedMemoryAddr += ExcRecordSize;

    CFE_PSP_ReservedMemoryMap.ResetMemory.BlockPtr = (void*) ReservedMemoryAddr;
    CFE_PSP_ReservedMemoryMap.ResetMemory.BlockSize = CFE_PSP_RESET_AREA_SIZE;
    ReservedMemoryAddr += ResetSize;

    CFE_PSP_ReservedMemoryMap.VolatileDiskMemory.BlockPtr = (void*) ReservedMemoryAddr;
    CFE_PSP_ReservedMemoryMap.VolatileDiskMemory.BlockSize = CFE_PSP_RAM_DISK_SECTOR_SIZE * CFE_PSP_RAM_DISK_NUM_SECTORS;
    ReservedMemoryAddr += VolatileDiskSize;

    CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr = (void*) ReservedMemoryAddr;
    CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize = CFE_PSP_CDS_SIZE;
    ReservedMemoryAddr += CDSSize;

    CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockPtr = (void*) ReservedMemoryAddr;
    CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockSize = CFE_PSP_USER_RESERVED_SIZE;
    ReservedMemoryAddr += UserReservedSize;
}

/*
**
**  This file is derived from these files:
**
**      mcp750-vxworks/src/cfe_psp_memory.c
**      pc-linux/src/cfe_psp_memory.c
**      pc-rtems/src/cfe_psp_memory.c
**
**  These works are licensed under the following terms:
**
**      GSC-18128-1, "Core Flight Executive Version 6.7"
**      
**      Copyright (c) 2006-2019 United States Government as represented by
**      the Administrator of the National Aeronautics and Space Administration.
**      All Rights Reserved.
**      
**      Licensed under the Apache License, Version 2.0 (the "License");
**      you may not use this file except in compliance with the License.
**      You may obtain a copy of the License at
**      
**        http://www.apache.org/licenses/LICENSE-2.0
**      
**      Unless required by applicable law or agreed to in writing, software
**      distributed under the License is distributed on an "AS IS" BASIS,
**      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**      See the License for the specific language governing permissions and
**      limitations under the License.
**
**  Modifications in this file authored by Patrick Paul are available under either the Apache-2.0 or MIT-0 license.
**
*/
