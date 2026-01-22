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
**      VxWorks 7 RTP / POSIX implementation 
**
** Purpose:
**   cFE PSP Memory related functions. This is the implementation of the cFE
**   memory areas that have to be preserved, and the API that is designed to allow
**   access to them. It also contains memory related routines to return the
**   address of the kernel code used in the cFE checksum.
**
**
******************************************************************************/

/*
**  Include Files
*/
#include <stdio.h>
#include <string.h>

#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

/*
** cFE includes
*/
#include "common_types.h"
#include "osapi.h"

/*
** Types and prototypes for this module
*/
#include "cfe_psp.h"

/*
** PSP Specific defines
*/
#include "cfe_psp_config.h"
#include "cfe_psp_memory.h"

#include "target_config.h"

/*
** On VxWorks, POSIX shared memory segments are being used for the
** reserved memory. This memory is preserved when the process quits
** but not when the OS is restarted.
** In VxWorks, the shared memory segments must be created through
** files in the "shmFs" which is mounted at /shm.
** shmFS is a flat file system, so shared memory segments for different
** cFS instances must be uniquely named.
**
** The shared memory segments are named by using a new command line
** parameter: cfsid
** This parameter specifies a prefix for the following shared memory segment file names.
** The default value for cfsid is "cfs1", so the default shared memory segment names are:
** /shm/cfs1.cdsfile
** /shm/cfs1.resetfile
** /shm/cfs1.reservedfile
**
** This allows more than one copy of the cFS to run on VxWorks (in RTPs) by using
** a different cfs id such as "cfs2"
*/
#define CFE_PSP_SHM_DIR        "/shm/"
#define CFE_PSP_CDS_SHM_FILE   ".cdsfile"
#define CFE_PSP_RST_SHM_FILE   ".resetfile"
#define CFE_PSP_USR_SHM_FILE   ".reservedfile"

/*
 * Define the PSP-supported capacities to be the maximum allowed,
 * (since the PC-linux PSP has the advantage of abundant disk space to hold this)
 */
#define CFE_PSP_CDS_SIZE           (GLOBAL_CONFIGDATA.CfeConfig->CdsSize)
#define CFE_PSP_RESET_AREA_SIZE    (GLOBAL_CONFIGDATA.CfeConfig->ResetAreaSize)
#define CFE_PSP_USER_RESERVED_SIZE (GLOBAL_CONFIGDATA.CfeConfig->UserReservedSize)

#define CFE_PSP_RAM_DISK_SECTOR_SIZE (GLOBAL_CONFIGDATA.CfeConfig->RamDiskSectorSize)
#define CFE_PSP_RAM_DISK_NUM_SECTORS (GLOBAL_CONFIGDATA.CfeConfig->RamDiskTotalSectors)

typedef struct
{
    CFE_PSP_ReservedMemoryBootRecord_t BootRecord;
    CFE_PSP_ExceptionStorage_t         ExceptionStorage;
} CFE_PSP_VxWorksReservedAreaFixedLayout_t;

/*
** Internal prototypes for this module
*/
void CFE_PSP_InitCDS(void);
void CFE_PSP_InitResetArea(void);
void CFE_PSP_InitVolatileDiskMem(void);
void CFE_PSP_InitUserReservedArea(void);

/*
**  External Declarations
**  These symbols mark the start and end of the RTPs code segment.
**  Note that this is not the kernel text segment that runs the RTP.
*/
extern unsigned int _init;
extern unsigned int _fini;

/* 
** Need to access the command line paramter data for cfsid
*/
extern CFE_PSP_CommandData_t CommandData;

/*
** Global variables
*/

/*
** Pointer to the vxWorks USER_RESERVED_MEMORY area
** The sizes of each memory area is defined in os_processor.h for this architecture.
*/
CFE_PSP_ReservedMemoryMap_t CFE_PSP_ReservedMemoryMap = {0};

/*
*********************************************************************************
** CDS related functions
*********************************************************************************
*/

/******************************************************************************
**
**  Purpose: This function is used by the ES startup code to initialize the
**            Critical Data store area
**
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/

void CFE_PSP_InitCDS(void)
{
    int  shm_fd;
    char shm_name[CFE_PSP_SHM_NAME_LENGTH];

    memset(shm_name, 0, CFE_PSP_SHM_NAME_LENGTH);
    strncpy(shm_name, CFE_PSP_SHM_DIR, CFE_PSP_SHM_NAME_LENGTH -1); 
    strncat(shm_name, CommandData.CfsId, strlen(CommandData.CfsId));
    strncat(shm_name, CFE_PSP_CDS_SHM_FILE, strlen(CFE_PSP_CDS_SHM_FILE));

    /* 
    ** Try to open an existing shared memory segment.
    ** If it fails, create a new one
    */  
    shm_fd = shm_open(shm_name, O_RDWR, 0666);
    if (shm_fd != -1)
    {
        OS_printf("CFE_PSP: Opened existing CDS shared memory segment\n");
    }
    else
    {
        OS_printf("CFE_PSP: Creating new CDS shared memory segment\n");

        shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
        if (shm_fd == -1)
        {
           perror("CFE_PSP - cannot create new shared memory segment");
           CFE_PSP_Panic(CFE_PSP_ERROR);
        }
    
        ftruncate(shm_fd, CFE_PSP_CDS_SIZE);
    }

    /* 
    ** Map the shared memory object
    */
    CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr = mmap(0, CFE_PSP_CDS_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if ( CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr == MAP_FAILED)
    {
        perror("CFE_PSP - Cannot map CDS Shared memory Segment");
        CFE_PSP_Panic(CFE_PSP_ERROR);
    }
    else
    {
       OS_printf("CFE_PSP: mmap CDS shared memory segment, size = %d\n", CFE_PSP_CDS_SIZE);
    }

    CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize = CFE_PSP_CDS_SIZE;
    close(shm_fd);
}

/******************************************************************************
**
**  Purpose:
**   This is an internal function to delete the CDS Shared memory segment.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
void CFE_PSP_DeleteCDS(void)
{
    char shm_name[CFE_PSP_SHM_NAME_LENGTH];

    memset(shm_name, 0, CFE_PSP_SHM_NAME_LENGTH);
    strncpy(shm_name, CFE_PSP_SHM_DIR, CFE_PSP_SHM_NAME_LENGTH -1);
    strncat(shm_name, CommandData.CfsId, strlen(CommandData.CfsId));
    strncat(shm_name, CFE_PSP_CDS_SHM_FILE, strlen(CFE_PSP_CDS_SHM_FILE));

    shm_unlink(shm_name);
    OS_printf("CFE_PSP: CDS Shared memory segment removed\n");
}

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
        return_code = CFE_PSP_ERROR;
    }
    else
    {
        *SizeOfCDS  = CFE_PSP_CDS_SIZE;
        return_code = CFE_PSP_SUCCESS;
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
        return_code = CFE_PSP_ERROR;
    }
    else
    {
        if ((CDSOffset < CFE_PSP_CDS_SIZE) && ((CDSOffset + NumBytes) <= CFE_PSP_CDS_SIZE))
        {
            CopyPtr = CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr;
            CopyPtr += CDSOffset;
            memcpy(CopyPtr, (char *)PtrToDataToWrite, NumBytes);

            return_code = CFE_PSP_SUCCESS;
        }
        else
        {
            return_code = CFE_PSP_ERROR;
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
        return_code = CFE_PSP_ERROR;
    }
    else
    {
        if ((CDSOffset < CFE_PSP_CDS_SIZE) && ((CDSOffset + NumBytes) <= CFE_PSP_CDS_SIZE))
        {
            CopyPtr = CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr;
            CopyPtr += CDSOffset;
            memcpy((char *)PtrToDataToRead, CopyPtr, NumBytes);

            return_code = CFE_PSP_SUCCESS;
        }
        else
        {
            return_code = CFE_PSP_ERROR;
        }

    } /* end if PtrToDataToWrite == NULL */

    return return_code;
}

/*
*********************************************************************************
** ES Reset Area related functions
*********************************************************************************
*/

/******************************************************************************
**
**  Purpose:
**    This function is used by the ES startup code to initialize the
**     ES Reset Area.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
void CFE_PSP_InitResetArea(void)
{
    
    size_t                                    total_size;
    size_t                                    reset_offset;
    size_t                                    align_mask;
    cpuaddr                                   block_addr;
    CFE_PSP_VxWorksReservedAreaFixedLayout_t *FixedBlocksPtr;
    char                                      shm_name[CFE_PSP_SHM_NAME_LENGTH];
    int                                       shm_fd;

    memset(shm_name, 0, CFE_PSP_SHM_NAME_LENGTH);
    strncpy(shm_name, CFE_PSP_SHM_DIR, CFE_PSP_SHM_NAME_LENGTH -1); 
    strncat(shm_name, CommandData.CfsId, strlen(CommandData.CfsId));
    strncat(shm_name, CFE_PSP_RST_SHM_FILE, strlen(CFE_PSP_RST_SHM_FILE));

    /*
     * NOTE: Historically the CFE ES reset area also contains the Exception log.
     * This is now allocated as a separate structure in the PSP, but it can
     * reside in this shared memory segment so it will be preserved on a processor
     * reset.
     */
    align_mask   = 4096 - 1; /* align blocks to whole memory pages */
    total_size   = sizeof(CFE_PSP_VxWorksReservedAreaFixedLayout_t);
    total_size   = (total_size + align_mask) & ~align_mask;
    reset_offset = total_size;
    total_size += CFE_PSP_RESET_AREA_SIZE;
    total_size = (total_size + align_mask) & ~align_mask;

    /* 
    ** Try to open an existing shared memory segment.
    ** If it fails, create a new one
    */  
    shm_fd = shm_open(shm_name, O_RDWR, 0666);
    if (shm_fd != -1)
    {
        OS_printf("CFE_PSP: Opened existing RST shared memory segment\n");
    }
    else
    {
        OS_printf("CFE_PSP: Creating new CDS shared memory segment\n");

        shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
        if (shm_fd == -1)
        {
           perror("CFE_PSP - cannot create new shared memory segment");
           CFE_PSP_Panic(CFE_PSP_ERROR);
        }

        ftruncate(shm_fd, total_size);
    } 

    /* 
    ** Map the shared memory object
    */
    block_addr = (cpuaddr)mmap(0, total_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if ( block_addr == (cpuaddr)MAP_FAILED)
    {
        perror("CFE_PSP - Cannot map RST Shared memory Segment");
        CFE_PSP_Panic(CFE_PSP_ERROR);
    }
    else
    {
       OS_printf("CFE_PSP: mmap RST shared memory segment, size = %zu\n", total_size);
    }
    
    FixedBlocksPtr = (CFE_PSP_VxWorksReservedAreaFixedLayout_t *)block_addr;
    block_addr += reset_offset;

    CFE_PSP_ReservedMemoryMap.BootPtr             = &FixedBlocksPtr->BootRecord;
    CFE_PSP_ReservedMemoryMap.ExceptionStoragePtr = &FixedBlocksPtr->ExceptionStorage;

    CFE_PSP_ReservedMemoryMap.ResetMemory.BlockPtr  = (void *)block_addr;
    CFE_PSP_ReservedMemoryMap.ResetMemory.BlockSize = CFE_PSP_RESET_AREA_SIZE;
    close(shm_fd);
}

/******************************************************************************
**
**  Purpose:
**   This is an internal function to delete the Reset Area Shared memory segment.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
void CFE_PSP_DeleteResetArea(void)
{
    char shm_name[CFE_PSP_SHM_NAME_LENGTH];

    memset(shm_name, 0, CFE_PSP_SHM_NAME_LENGTH);
    strncpy(shm_name, CFE_PSP_SHM_DIR, CFE_PSP_SHM_NAME_LENGTH -1);
    strncat(shm_name, CommandData.CfsId, strlen(CommandData.CfsId));
    strncat(shm_name, CFE_PSP_RST_SHM_FILE, strlen(CFE_PSP_RST_SHM_FILE));

    shm_unlink(shm_name);
    OS_printf("CFE_PSP: RST Shared memory segment removed\n");
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_GetResetArea(cpuaddr *PtrToResetArea, uint32 *SizeOfResetArea)
{
    int32 return_code;

    if (SizeOfResetArea == NULL)
    {
        return_code = CFE_PSP_ERROR;
    }
    else
    {
        *PtrToResetArea  = (cpuaddr)CFE_PSP_ReservedMemoryMap.ResetMemory.BlockPtr;
        *SizeOfResetArea = CFE_PSP_ReservedMemoryMap.ResetMemory.BlockSize;
        return_code      = CFE_PSP_SUCCESS;
    }

    return return_code;
}

/*
*********************************************************************************
** ES User Reserved Area related functions
*********************************************************************************
*/

/******************************************************************************
**
**  Purpose:
**    This function is used by the ES startup code to initialize the
**      ES user reserved area.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
void CFE_PSP_InitUserReservedArea(void)
{
    int  shm_fd;
    char shm_name[CFE_PSP_SHM_NAME_LENGTH];

    memset(shm_name, 0, CFE_PSP_SHM_NAME_LENGTH);
    strncpy(shm_name, CFE_PSP_SHM_DIR, CFE_PSP_SHM_NAME_LENGTH -1); 
    strncat(shm_name, CommandData.CfsId, strlen(CommandData.CfsId));
    strncat(shm_name, CFE_PSP_USR_SHM_FILE, strlen(CFE_PSP_USR_SHM_FILE));

    /* 
    ** Try to open an existing shared memory segment.
    ** If it fails, create a new one
    */  
    shm_fd = shm_open(shm_name, O_RDWR, 0666);
    if (shm_fd != -1)
    {
        OS_printf("CFE_PSP: Opened existing USR shared memory segment\n");
    }
    else
    {
        OS_printf("CFE_PSP: Creating new USR shared memory segment\n");
        shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
        if (shm_fd == -1)
        {
           perror("CFE_PSP - cannot create new shared memory segment");
           CFE_PSP_Panic(CFE_PSP_ERROR);
        }

        ftruncate(shm_fd, CFE_PSP_USER_RESERVED_SIZE);
    }

    /* 
    ** Map the shared memory object
    */
    CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockPtr = mmap(0, CFE_PSP_USER_RESERVED_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if ( CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockPtr == MAP_FAILED)
    {
        perror("CFE_PSP - Cannot map USR Shared memory Segment");
        CFE_PSP_Panic(CFE_PSP_ERROR);
        printf("PSP: error calling mmap! (USR)\n");
    }
    else
    {
       OS_printf("CFE_PSP: mmap USR shared memory segment, size = %d\n", CFE_PSP_USER_RESERVED_SIZE);
    }
    CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockSize = CFE_PSP_USER_RESERVED_SIZE;
    close(shm_fd);

}

/******************************************************************************
**
**  Purpose:
**   This is an internal function to delete the User Reserved Shared memory segment.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
void CFE_PSP_DeleteUserReservedArea(void)
{
    char shm_name[CFE_PSP_SHM_NAME_LENGTH];

    memset(shm_name, 0, CFE_PSP_SHM_NAME_LENGTH);
    strncpy(shm_name, CFE_PSP_SHM_DIR, CFE_PSP_SHM_NAME_LENGTH -1); 
    strncat(shm_name, CommandData.CfsId, strlen(CommandData.CfsId));
    strncat(shm_name, CFE_PSP_USR_SHM_FILE, strlen(CFE_PSP_USR_SHM_FILE));

    shm_unlink(shm_name);
    OS_printf("CFE_PSP: USR Reserved Shared memory segment removed\n");
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_GetUserReservedArea(cpuaddr *PtrToUserArea, uint32 *SizeOfUserArea)
{
    int32 return_code;

    if (SizeOfUserArea == NULL)
    {
        return_code = CFE_PSP_ERROR;
    }
    else
    {
        *PtrToUserArea  = (cpuaddr)CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockPtr;
        *SizeOfUserArea = CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockSize;
        return_code     = CFE_PSP_SUCCESS;
    }

    return return_code;
}

/*
*********************************************************************************
** ES Volatile disk memory related functions
*********************************************************************************
*/

/******************************************************************************
**
**  Purpose:
**   This function is used by the ES startup code to initialize the memory
**   used by the volatile disk. On a desktop/posix platform this is currently
**   a no-op, because the volatile disk is being mapped to the desktop.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
void CFE_PSP_InitVolatileDiskMem(void)
{
    /*
    ** Here, we want to clear out the volatile ram disk contents
    ** on a power on reset
    */
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_GetVolatileDiskMem(cpuaddr *PtrToVolDisk, uint32 *SizeOfVolDisk)
{
    int32 return_code;

    if (SizeOfVolDisk == NULL)
    {
        return_code = CFE_PSP_ERROR;
    }
    else
    {
        *PtrToVolDisk  = (cpuaddr)CFE_PSP_ReservedMemoryMap.VolatileDiskMemory.BlockPtr;
        *SizeOfVolDisk = CFE_PSP_ReservedMemoryMap.VolatileDiskMemory.BlockSize;
        return_code    = CFE_PSP_SUCCESS;
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
void CFE_PSP_SetupReservedMemoryMap(void)
{
    /*
     * The setup of each section is done as a separate init.
     *
     * Any failures within these routines call exit(), so there
     * is no need to check status - failure means no return.
     */

    CFE_PSP_InitCDS();
    CFE_PSP_InitResetArea();
    CFE_PSP_InitVolatileDiskMem();
    CFE_PSP_InitUserReservedArea();

    /*
     * Set up the "RAM" entry in the memory table.
     * On Linux this is just encompasses the entire memory space, but an entry needs
     * to exist so that CFE_PSP_ValidateMemRange() works as intended.
     */
    CFE_PSP_MemRangeSet(0, CFE_PSP_MEM_RAM, 0, SIZE_MAX, CFE_PSP_MEM_SIZE_DWORD, CFE_PSP_MEM_ATTR_READWRITE);
}

int32 CFE_PSP_InitProcessorReservedMemory(uint32 RestartType)
{
    /*
     * Clear the segments only on a POWER ON reset
     *
     * Newly-created segments should already be zeroed out,
     * but this ensures it.
     */
    if (RestartType == CFE_PSP_RST_TYPE_POWERON)
    {
        OS_printf("CFE_PSP: Clearing out CFE CDS Shared memory segment.\n");
        memset(CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr, 0, CFE_PSP_CDS_SIZE);
        OS_printf("CFE_PSP: Clearing out CFE Reset Shared memory segment.\n");
        memset(CFE_PSP_ReservedMemoryMap.ResetMemory.BlockPtr, 0, CFE_PSP_RESET_AREA_SIZE);
        OS_printf("CFE_PSP: Clearing out CFE User Reserved Shared memory segment.\n");
        memset(CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockPtr, 0, CFE_PSP_USER_RESERVED_SIZE);

        memset(CFE_PSP_ReservedMemoryMap.BootPtr, 0, sizeof(*CFE_PSP_ReservedMemoryMap.BootPtr));
        memset(CFE_PSP_ReservedMemoryMap.ExceptionStoragePtr, 0,
               sizeof(*CFE_PSP_ReservedMemoryMap.ExceptionStoragePtr));

        /*
         * If an unclean shutdown occurs, try to do a PROCESSOR reset next.
         * This will attempt to preserve the exception and reset log content.
         */
        CFE_PSP_ReservedMemoryMap.BootPtr->NextResetType = CFE_PSP_RST_TYPE_PROCESSOR;
    }
    else
    {
        /*
         * If an unclean shutdown occurs after a PROCESSOR reset, then next time should
         * be a POWERON reset.
         */
        CFE_PSP_ReservedMemoryMap.BootPtr->NextResetType = CFE_PSP_RST_TYPE_POWERON;
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
    CFE_PSP_ReservedMemoryMap.BootPtr->ValidityFlag = CFE_PSP_BOOTRECORD_INVALID;

    return CFE_PSP_SUCCESS;
}

/******************************************************************************
**
**  Purpose:
**    This function cleans up all of the shared memory segments in the
**     Linux/OSX ports.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
void CFE_PSP_DeleteProcessorReservedMemory(void)
{
    CFE_PSP_DeleteCDS();
    CFE_PSP_DeleteResetArea();
    CFE_PSP_DeleteUserReservedArea();
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
    /* Check pointers */
    if (PtrToKernelSegment == NULL || SizeOfKernelSegment == NULL)
    {
        return CFE_PSP_ERROR;
    }

    /* Set to known values */
    *PtrToKernelSegment  = (cpuaddr)0x0;
    *SizeOfKernelSegment = 0;

    return CFE_PSP_ERROR_NOT_IMPLEMENTED;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
int32 CFE_PSP_GetCFETextSegmentInfo(cpuaddr *PtrToCFESegment, uint32 *SizeOfCFESegment)
{
    int32 return_code;

    if (SizeOfCFESegment == NULL)
    {
        return_code = CFE_PSP_ERROR;
    }
    else
    {
        *PtrToCFESegment  = (cpuaddr)(&_init);
        *SizeOfCFESegment = (uint32)(((cpuaddr)&_fini) - ((cpuaddr)&_init));

        return_code = CFE_PSP_SUCCESS;
    }

    return return_code;
}
