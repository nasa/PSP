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

/******************************************************************************
** File:  cfe_psp_memory.c
**
**
** Purpose:
**   cFE PSP Memory related functions. This is the implementation of the cFE
**   memory areas that have to be preserved, and the API that is designed to allow
**   access to them. It also contains memory related routines to return the
**   address of the kernel code used in the cFE checksum.
**
** History:
**
******************************************************************************/

/*
**  Include Files
*/
#include <stdio.h>
#include <string.h>

/*
** cFE includes
*/
#include "common_types.h"
#include "osapi.h"

/*
** VxWorks includes
*/
#include "vxWorks.h"
#include "userReservedMem.h"
#include <sysLib.h>
#include <moduleLib.h>

/* Note that usage of this reserved memory implementation requires the INCLUDE_USER_RESERVED_MEMORY 
 * component with CLEAR_USER_RESERVED_MEMORY_ON_COLD_BOOT set to FALSE */

/*
** Types and prototypes for this module
*/
#include "cfe_psp.h"
#include "cfe_psp_memory.h"
#include "cfe_psp_config.h"

/*
** Macro Definitions
*/
#include "target_config.h"

/*
 * Define the PSP-supported capacities to be the maximum allowed,
 * (since the PC-linux PSP has the advantage of abundant disk space to hold this)
 */
#define CFE_PSP_CDS_SIZE             (GLOBAL_CONFIGDATA.CfeConfig->CdsSize)
#define CFE_PSP_RESET_AREA_SIZE      (GLOBAL_CONFIGDATA.CfeConfig->ResetAreaSize)
#define CFE_PSP_USER_RESERVED_SIZE   (GLOBAL_CONFIGDATA.CfeConfig->UserReservedSize)
#define CFE_PSP_RAM_DISK_SECTOR_SIZE (GLOBAL_CONFIGDATA.CfeConfig->RamDiskSectorSize)
#define CFE_PSP_RAM_DISK_NUM_SECTORS (GLOBAL_CONFIGDATA.CfeConfig->RamDiskTotalSectors)

/* simple handy macro */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef struct
{
    CFE_PSP_ReservedMemoryBootRecord_t BootRecord;
    CFE_PSP_ExceptionStorage_t         ExceptionStorage;
} CFE_PSP_VxWorksReservedAreaFixedLayout_t;

/*
**  External Declarations
*/
extern void *GetWrsKernelTextStart(void);
extern void *GetWrsKernelTextEnd(void);

/*
** Global variables
*/

/*
** Dynamic map of the reserved memory area
*/
CFE_PSP_ReservedMemoryMap_t CFE_PSP_ReservedMemoryMap = {0};

CFE_PSP_MemoryBlock_t VxWorks_ReservedMemBlock;

/*
*********************************************************************************
** CDS related functions
*********************************************************************************
*/

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_GetCDSSize(uint32 *SizeOfCDS)
{
    int32 return_code;

    if (SizeOfCDS == NULL)
    {
        return_code = OS_ERROR;
    }
    else
    {
        *SizeOfCDS  = CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize;
        return_code = OS_SUCCESS;
    }
    return return_code;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_WriteToCDS(const void *PtrToDataToWrite, uint32 CDSOffset, uint32 NumBytes)
{
    uint8 *CopyPtr;
    int32  return_code;

    if (PtrToDataToWrite == NULL)
    {
        return_code = OS_ERROR;
    }
    else
    {
        if ((CDSOffset < CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize) &&
            ((CDSOffset + NumBytes) <= CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize))
        {
            CopyPtr = CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr;
            CopyPtr += CDSOffset;
            memcpy((char *)CopyPtr, (char *)PtrToDataToWrite, NumBytes);

            return_code = OS_SUCCESS;
        }
        else
        {
            return_code = OS_ERROR;
        }

    } /* end if PtrToDataToWrite == NULL */

    return return_code;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_ReadFromCDS(void *PtrToDataToRead, uint32 CDSOffset, uint32 NumBytes)
{
    uint8 *CopyPtr;
    int32  return_code;

    if (PtrToDataToRead == NULL)
    {
        return_code = OS_ERROR;
    }
    else
    {
        if ((CDSOffset < CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize) &&
            ((CDSOffset + NumBytes) <= CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize))
        {
            CopyPtr = CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr;
            CopyPtr += CDSOffset;
            memcpy((char *)PtrToDataToRead, (char *)CopyPtr, NumBytes);

            return_code = OS_SUCCESS;
        }
        else
        {
            return_code = OS_ERROR;
        }

    } /* end if PtrToDataToWrite == NULL */

    return return_code;
}

/*
*********************************************************************************
** ES Reset Area related functions
*********************************************************************************
*/

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_GetResetArea(cpuaddr *PtrToResetArea, uint32 *SizeOfResetArea)
{
    int32 return_code;

    if (SizeOfResetArea == NULL || PtrToResetArea == NULL)
    {
        return_code = OS_ERROR;
    }
    else
    {
        *PtrToResetArea  = (cpuaddr)(CFE_PSP_ReservedMemoryMap.ResetMemory.BlockPtr);
        *SizeOfResetArea = CFE_PSP_ReservedMemoryMap.ResetMemory.BlockSize;
        return_code      = OS_SUCCESS;
    }

    return return_code;
}

/*
*********************************************************************************
** ES User Reserved Area related functions
*********************************************************************************
*/

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_GetUserReservedArea(cpuaddr *PtrToUserArea, uint32 *SizeOfUserArea)
{
    int32 return_code;

    if (SizeOfUserArea == NULL || PtrToUserArea == NULL)
    {
        return_code = OS_ERROR;
    }
    else
    {
        *PtrToUserArea  = (cpuaddr)(CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockPtr);
        *SizeOfUserArea = CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockSize;
        return_code     = OS_SUCCESS;
    }

    return return_code;
}

/*
*********************************************************************************
** ES Volatile disk memory related functions
*********************************************************************************
*/

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_GetVolatileDiskMem(cpuaddr *PtrToVolDisk, uint32 *SizeOfVolDisk)
{
    int32 return_code;

    if (SizeOfVolDisk == NULL || PtrToVolDisk == NULL)
    {
        return_code = OS_ERROR;
    }
    else
    {
        *PtrToVolDisk  = (cpuaddr)(CFE_PSP_ReservedMemoryMap.VolatileDiskMemory.BlockPtr);
        *SizeOfVolDisk = CFE_PSP_ReservedMemoryMap.VolatileDiskMemory.BlockSize;
        return_code    = OS_SUCCESS;
    }

    return return_code;
}

/*
*********************************************************************************
** ES BSP Top Level Reserved memory initialization
*********************************************************************************
*/


/******************************************************************************
**
**  Purpose:
**    This function performs the top level reserved memory initialization.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
int32 CFE_PSP_InitProcessorReservedMemory(uint32 RestartType)
{
    if (RestartType == CFE_PSP_RST_TYPE_POWERON)
    {
        OS_printf("CFE_PSP: Clearing Processor Reserved Memory.\n");
        memset(VxWorks_ReservedMemBlock.BlockPtr, 0, VxWorks_ReservedMemBlock.BlockSize);
        /*
        ** Set the default reset type in case a watchdog reset occurs
        */
        CFE_PSP_ReservedMemoryMap.BootPtr->bsp_reset_type = CFE_PSP_RST_TYPE_PROCESSOR;
    }

    return OS_SUCCESS;
}

/******************************************************************************
**
**  Purpose:
**    This function performs the top level reserved memory initialization.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
void CFE_PSP_SetupReservedMemoryMap(void)
{
    CFE_PSP_VxWorksReservedAreaFixedLayout_t *FixedPtr;
    cpuaddr                                 ReservedMemoryAddr;
    size_t                                  FixedSize;
    size_t                                  ResetSize;
    size_t                                  CDSSize;
    size_t                                  UserReservedSize;
    size_t                                  VolatileDiskSize;
    size_t                                  RequiredSize;
    char *ReservedMemoryStart;
    size_t ReservedMemorySize;
    /* TODO: do we need both ReservedMemoryStart and ReservedMemoryAddr */

    /*
    ** Allocate memory for the cFE memory. Note that this is malloced on
    ** the COTS board, but will be a static location in the ETU.
    */
    FixedSize        = sizeof(CFE_PSP_VxWorksReservedAreaFixedLayout_t);
    ResetSize        = CFE_PSP_RESET_AREA_SIZE;
    VolatileDiskSize = (CFE_PSP_RAM_DISK_SECTOR_SIZE * CFE_PSP_RAM_DISK_NUM_SECTORS);
    CDSSize          = CFE_PSP_CDS_SIZE;
    UserReservedSize = CFE_PSP_USER_RESERVED_SIZE;

    FixedSize        = (FixedSize + CFE_PSP_MEMALIGN_MASK) & ~CFE_PSP_MEMALIGN_MASK;
    ResetSize        = (ResetSize + CFE_PSP_MEMALIGN_MASK) & ~CFE_PSP_MEMALIGN_MASK;
    CDSSize          = (CDSSize + CFE_PSP_MEMALIGN_MASK) & ~CFE_PSP_MEMALIGN_MASK;
    VolatileDiskSize = (VolatileDiskSize + CFE_PSP_MEMALIGN_MASK) & ~CFE_PSP_MEMALIGN_MASK;
    UserReservedSize = (UserReservedSize + CFE_PSP_MEMALIGN_MASK) & ~CFE_PSP_MEMALIGN_MASK;

    /*  Calculate the required size, adding padding so that each element is aligned */
    RequiredSize = FixedSize;
    RequiredSize += ResetSize;
    RequiredSize += VolatileDiskSize;
    RequiredSize += CDSSize;
    RequiredSize += UserReservedSize;

    /* Get address and size of user reserved memory */

    /* Since we need to have at least RequiredSize amount of reserved memory,
     * we have to check if there is enough given by the userReservedGet() call.
     * Since the size of user reserved memory is a static constant built into 
     * the kernel at build time, there is no recourse here. Either RequiredSize 
     * must be reduced or the kernel build must change to support more memory
     * by changing the USER_RESERVED_MEM component. */
    userReservedGet(&ReservedMemoryStart, &ReservedMemorySize);
    if (ReservedMemorySize < RequiredSize || ReservedMemoryStart == NULL) {
        OS_printf("CFE_PSP: Error: Cannot get BSP reserved memory\n");
        abort();
    }

    OS_printf("Size of BSP reserved memory = %u bytes\n", (unsigned int)RequiredSize);

    /* with the INCLUDE_USER_RESERVED_MEMORY configuration, we don't need to allocate
     * any memory here. We can just set this variable to the address given by 
     * userReservedGet(). */
    VxWorks_ReservedMemBlock.BlockPtr = ReservedMemoryStart;

    VxWorks_ReservedMemBlock.BlockSize = RequiredSize;
    ReservedMemoryAddr                 = (cpuaddr)VxWorks_ReservedMemBlock.BlockPtr;

    OS_printf("CFE_PSP: Allocated %u bytes for PSP reserved memory at: 0x%08lX\n", (unsigned int)RequiredSize,
              (unsigned long)ReservedMemoryAddr);

    FixedPtr = (CFE_PSP_VxWorksReservedAreaFixedLayout_t *)ReservedMemoryAddr;

    CFE_PSP_ReservedMemoryMap.BootPtr             = &FixedPtr->BootRecord;
    CFE_PSP_ReservedMemoryMap.ExceptionStoragePtr = &FixedPtr->ExceptionStorage;
    ReservedMemoryAddr += FixedSize;

    CFE_PSP_ReservedMemoryMap.ResetMemory.BlockPtr  = (void *)ReservedMemoryAddr;
    CFE_PSP_ReservedMemoryMap.ResetMemory.BlockSize = CFE_PSP_RESET_AREA_SIZE;
    ReservedMemoryAddr += ResetSize;

    CFE_PSP_ReservedMemoryMap.VolatileDiskMemory.BlockPtr = (void *)ReservedMemoryAddr;
    CFE_PSP_ReservedMemoryMap.VolatileDiskMemory.BlockSize =
        (CFE_PSP_RAM_DISK_SECTOR_SIZE * CFE_PSP_RAM_DISK_NUM_SECTORS);
    ReservedMemoryAddr += VolatileDiskSize;

    CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr  = (void *)ReservedMemoryAddr;
    CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize = CFE_PSP_CDS_SIZE;
    ReservedMemoryAddr += CDSSize;

    CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockPtr  = (void *)ReservedMemoryAddr;
    CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockSize = CFE_PSP_USER_RESERVED_SIZE;
    ReservedMemoryAddr += UserReservedSize;

    /*
     * displaying the final address shows how much was actually used,
     * and additionally avoids a warning about the result of the final increment not being used.
     * (prefer this over removing the increment, as it is safer if another block is added)
     */
    OS_printf("CFE_PSP: PSP reserved memory ends at: 0x%08lX\n", (unsigned long)ReservedMemoryAddr);

    /*
     * Set up the "RAM" entry in the memory table.
     * On RTEMS this just encompasses the entire memory space, but an entry needs
     * to exist so that CFE_PSP_ValidateMemRange() works as intended.
     */
    CFE_PSP_MemRangeSet(0, CFE_PSP_MEM_RAM, 0, SIZE_MAX, CFE_PSP_MEM_SIZE_DWORD, CFE_PSP_MEM_ATTR_READWRITE);
}

/*
*********************************************************************************
** ES BSP kernel memory segment functions
*********************************************************************************
*/

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_GetKernelTextSegmentInfo(cpuaddr *PtrToKernelSegment, uint32 *SizeOfKernelSegment)
{
    int32   return_code;
    cpuaddr StartAddress;
    cpuaddr EndAddress;

    if (SizeOfKernelSegment == NULL || PtrToKernelSegment == NULL)
    {
        return_code = OS_ERROR;
    }
    else
    {
        /*
        ** Get the kernel start and end
        ** addresses from the BSP, because the
        ** symbol table does not contain the symbols we need for this
        */
        StartAddress = (cpuaddr)GetWrsKernelTextStart();
        EndAddress   = (cpuaddr)GetWrsKernelTextEnd();

        *PtrToKernelSegment  = StartAddress;
        *SizeOfKernelSegment = (uint32)(EndAddress - StartAddress);

        return_code = OS_SUCCESS;
    }

    return return_code;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_GetCFETextSegmentInfo(cpuaddr *PtrToCFESegment, uint32 *SizeOfCFESegment)
{
    int32       return_code;
    STATUS      status;
    MODULE_ID   cFEModuleId;
    MODULE_INFO cFEModuleInfo;
    cpuaddr     GetModuleIdAddr;
    MODULE_ID (*GetModuleIdFunc)(void);

    if (PtrToCFESegment == NULL || SizeOfCFESegment == NULL)
    {
        return_code = OS_ERROR;
    }
    else
    {
        /*
         * First attempt to call a function called GetCfeCoreModuleID().
         *
         * If CFE core was started via the "startCfeCore" routine, this
         * provides the actual module ID that was loaded by that routine,
         * no matter what it is actually named.  This is provided by the
         * support/integration code compiled directly into the VxWorks kernel
         * image.
         *
         * The prototype should be:
         *     MODULE_ID GetCfeCoreModuleID(void);
         */
        cFEModuleId     = NULL;
        GetModuleIdAddr = 0;
        return_code     = OS_SymbolLookup(&GetModuleIdAddr, "GetCfeCoreModuleID");
        if (return_code == OS_SUCCESS && GetModuleIdAddr != 0)
        {
            GetModuleIdFunc = (MODULE_ID(*)(void))GetModuleIdAddr;
            cFEModuleId     = GetModuleIdFunc();
        }

        /*
         * If the above did not yield a valid module ID,
         * then attempt to find the module ID by name.
         * This assumes the core executable name as built by CMake
         */
        if (cFEModuleId == NULL)
        {
            cFEModuleId = moduleFindByName((char *)GLOBAL_CONFIGDATA.Default_CoreFilename);
        }

        if (cFEModuleId == NULL)
        {
            return_code = OS_ERROR;
        }
        else
        {
            status = moduleInfoGet(cFEModuleId, &cFEModuleInfo);
            if (status != ERROR)
            {
                *PtrToCFESegment  = (cpuaddr)(cFEModuleInfo.segInfo.textAddr);
                *SizeOfCFESegment = (uint32)(cFEModuleInfo.segInfo.textSize);
                return_code       = OS_SUCCESS;
            }
            else
            {
                return_code = OS_SUCCESS;
            }
        }
    }

    return return_code;
}
