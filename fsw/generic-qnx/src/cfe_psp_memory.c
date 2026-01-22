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
**   QNX Version
**
** Purpose:
**   cFE PSP Memory related functions. This is the implementation of the cFE
**   memory areas that have to be preserved, and the API that is designed to allow
**   access to them. It also contains memory related routines to return the
**   address of the kernel code used in the cFE checksum.
**
******************************************************************************/

/*
**  Include Files
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>

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

#define CFE_PSP_KEY_FILE_NAME_LENGTH   40

char CdsKeyFileName[CFE_PSP_KEY_FILE_NAME_LENGTH];
char ResetKeyFileName[CFE_PSP_KEY_FILE_NAME_LENGTH];
char ReservedKeyFileName[CFE_PSP_KEY_FILE_NAME_LENGTH];

#define CFE_PSP_CDS_KEY_FILE_NAME_EXT      "cdskeyfile"
#define CFE_PSP_RESET_KEY_FILE_NAME_EXT    "resetkeyfile"
#define CFE_PSP_RESERVED_KEY_FILE_NAME_EXT "reservedkeyfile"

#define CFE_PSP_CDS_KEY_FILE      CdsKeyFileName
#define CFE_PSP_RESET_KEY_FILE    ResetKeyFileName
#define CFE_PSP_RESERVED_KEY_FILE ReservedKeyFileName

#include "target_config.h"

/*
 * Define the PSP-supported capacities to be the maximum allowed,
*/
#define CFE_PSP_CDS_SIZE           (GLOBAL_CONFIGDATA.CfeConfig->CdsSize)
#define CFE_PSP_RESET_AREA_SIZE    (GLOBAL_CONFIGDATA.CfeConfig->ResetAreaSize)
#define CFE_PSP_USER_RESERVED_SIZE (GLOBAL_CONFIGDATA.CfeConfig->UserReservedSize)

typedef struct
{
    CFE_PSP_ReservedMemoryBootRecord_t BootRecord;
    CFE_PSP_ExceptionStorage_t         ExceptionStorage;
} CFE_PSP_QnxReservedAreaFixedLayout_t;

/*
** Internal prototypes for this module
*/
void CFE_PSP_InitCDS(void);
void CFE_PSP_InitResetArea(void);
void CFE_PSP_InitVolatileDiskMem(void);
void CFE_PSP_InitUserReservedArea(void);
void CFE_PSP_InitKeyFileNames(char *CpuName, uint32 CpuId);


/*
**  External Declarations
*/
extern unsigned int _btext;
extern unsigned int _etext;

/*
** Global variables
*/
int ResetAreaShmId;
int CDSShmId;
int UserShmId;

/*
** Pointer to the vxWorks USER_RESERVED_MEMORY area
** The sizes of each memory area is defined in os_processor.h for this architecture.
*/
CFE_PSP_ReservedMemoryMap_t CFE_PSP_ReservedMemoryMap;

/*
*********************************************************************************
** CDS related functions
*********************************************************************************
*/
/*
**
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
    /*
    ** connect to (and possibly create) the segment:
    */
    if ((CDSShmId = shm_open(CFE_PSP_CDS_KEY_FILE, O_RDWR | O_CREAT, 0644)) == -1)
    {
        perror("CFE_PSP - Cannot shm_open CDS Shared memory Segment");
        CFE_PSP_Panic(CFE_PSP_ERROR);
    }

    ftruncate(CDSShmId, CFE_PSP_CDS_SIZE);

    /*
    ** attach to the segment to get a pointer to it:
    */
    CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr = mmap(NULL,CFE_PSP_CDS_SIZE, (PROT_READ | PROT_WRITE), MAP_SHARED, CDSShmId, 0);
    if (CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr == MAP_FAILED)
    {
        perror("CFE_PSP - Cannot mmap to CDS Shared memory Segment");
        CFE_PSP_Panic(CFE_PSP_ERROR);
    }

    CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize = CFE_PSP_CDS_SIZE;
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
    int             ReturnCode = 0;

    /* Unmapped and unlink shared memory segment */ 
    ReturnCode = munmap(CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr, CFE_PSP_CDS_SIZE);
    if (ReturnCode == 0)
    {
        ReturnCode = shm_unlink(CFE_PSP_CDS_KEY_FILE);
        if(ReturnCode == 0)
        {
           OS_printf("User CDS Area Shared memory segment removed\n");
        }
        else
        {
           OS_printf("Error Removing User CDS Area Shared memory Segment.\n");
        }
    }
    else
    {
        OS_printf("Error Removing User CDS Area Shared memory Segment.\n");
    }
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
    size_t                                  total_size;
    size_t                                  reset_offset;
    size_t                                  align_mask;
    cpuaddr                                 block_addr;
    CFE_PSP_QnxReservedAreaFixedLayout_t *FixedBlocksPtr;

    /*
     * NOTE: Historically the CFE ES reset area also contains the Exception log.
     * This is now allocated as a separate structure in the PSP, but it can
     * reside in this shared memory segment so it will be preserved on a processor
     * reset.
     */
    align_mask   = sysconf(_SC_PAGESIZE) - 1; /* align blocks to whole memory pages */
    total_size   = sizeof(CFE_PSP_QnxReservedAreaFixedLayout_t);
    total_size   = (total_size + align_mask) & ~align_mask;
    reset_offset = total_size;
    total_size += CFE_PSP_RESET_AREA_SIZE;
    total_size = (total_size + align_mask) & ~align_mask;

    /*
    ** connect to (and possibly create) the segment:
    */
    if ((ResetAreaShmId = shm_open(CFE_PSP_RESET_KEY_FILE, O_RDWR | O_CREAT, 0644)) == -1)
    {
        perror("CFE_PSP - Cannot shm_open Reset Area Shared memory Segment");
        CFE_PSP_Panic(CFE_PSP_ERROR);
    }

    /*
    ** attach to the segment to get a pointer to it:
    */
    ftruncate(ResetAreaShmId, total_size);
    block_addr = (cpuaddr)mmap(NULL,total_size, (PROT_READ | PROT_WRITE), MAP_SHARED, ResetAreaShmId, 0);
    if (block_addr == (cpuaddr)(-1))
    {
        perror("CFE_PSP - Cannot mmap to Reset Area Shared memory Segment");
        CFE_PSP_Panic(CFE_PSP_ERROR);
    }

    FixedBlocksPtr = (CFE_PSP_QnxReservedAreaFixedLayout_t *)block_addr;
    block_addr += reset_offset;

    CFE_PSP_ReservedMemoryMap.BootPtr             = &FixedBlocksPtr->BootRecord;
    CFE_PSP_ReservedMemoryMap.ExceptionStoragePtr = &FixedBlocksPtr->ExceptionStorage;

    CFE_PSP_ReservedMemoryMap.ResetMemory.BlockPtr  = (void *)block_addr;
    CFE_PSP_ReservedMemoryMap.ResetMemory.BlockSize = CFE_PSP_RESET_AREA_SIZE;
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
    int             ReturnCode = 0;

    /* Unmapped and unlink shared memory segment */
    ReturnCode = munmap(CFE_PSP_ReservedMemoryMap.ResetMemory.BlockPtr, CFE_PSP_RESET_AREA_SIZE);

    if (ReturnCode == 0)
    {
        ReturnCode = shm_unlink(CFE_PSP_RESET_KEY_FILE);
        if(ReturnCode == 0)
        {
           OS_printf("User Reset Area Shared memory segment removed\n");
        }
        else
        {
           OS_printf("Error Removing User Reset Area Shared memory Segment.\n");
        }
    }
    else
    {
        OS_printf("Error Removing User Reset Area Shared memory Segment.\n");
    }
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

/*
**  Purpose:
**    This function is used to create unique key file names for shared memory
**    segements.
*/
void CFE_PSP_InitKeyFileNames(char *CpuName, uint32 CpuId)
{
    /*
    ** Construct the key file name:
    ** The name will consist of "/<cpuName.CpuId>.key_file_name"
    */
    snprintf(CdsKeyFileName,      sizeof(CdsKeyFileName),      "/%s.%d.%s", CpuName, CpuId, CFE_PSP_CDS_KEY_FILE_NAME_EXT);
    snprintf(ResetKeyFileName,    sizeof(ResetKeyFileName),    "/%s.%d.%s", CpuName, CpuId, CFE_PSP_RESET_KEY_FILE_NAME_EXT);
    snprintf(ReservedKeyFileName, sizeof(ReservedKeyFileName), "/%s.%d.%s", CpuName, CpuId, CFE_PSP_RESERVED_KEY_FILE_NAME_EXT);
}

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
    /*
    ** connect to (and possibly create) the segment:
    */
    if ((UserShmId = shm_open(CFE_PSP_RESERVED_KEY_FILE, O_RDWR | O_CREAT, 0644)) == -1)
    {
        perror("CFE_PSP - Cannot shm_open User Reserved Area Shared memory Segment");
        CFE_PSP_Panic(CFE_PSP_ERROR);
    }

    /*
    ** attach to the segment to get a pointer to it:
    */
    ftruncate(UserShmId, CFE_PSP_USER_RESERVED_SIZE);
    CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockPtr = mmap(NULL, CFE_PSP_USER_RESERVED_SIZE,
      (PROT_READ | PROT_WRITE), MAP_SHARED, UserShmId, 0);
    if (CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockPtr == (void *)(-1))
    {
        perror("CFE_PSP - Cannot mmap to User Reserved Area Shared memory Segment");
        CFE_PSP_Panic(CFE_PSP_ERROR);
    }

    CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockSize = CFE_PSP_USER_RESERVED_SIZE;
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
    int             ReturnCode = 0;

    /* Unmapped and unlink shared memory segment */
    ReturnCode = munmap(CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockPtr, CFE_PSP_USER_RESERVED_SIZE);

    if (ReturnCode == 0)
    {
        ReturnCode = shm_unlink(CFE_PSP_RESERVED_KEY_FILE);
        if(ReturnCode == 0)
        {
           OS_printf("User Reserved Area Shared memory segment removed\n");
        }
        else
        {
           OS_printf("Error Removing User Reserved Area Shared memory Segment.\n");
        }
    }
    else
    {
        OS_printf("Error Removing User Reserved Area Shared memory Segment.\n");
    }
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
    int tempFd;

    /*
    ** Create the key files for the shared memory segments
    ** The files are not needed, so they are closed right away.
    */
    tempFd = open(CFE_PSP_CDS_KEY_FILE, O_RDONLY | O_CREAT, S_IRWXU);
    close(tempFd);
    tempFd = open(CFE_PSP_RESET_KEY_FILE, O_RDONLY | O_CREAT, S_IRWXU);
    close(tempFd);
    tempFd = open(CFE_PSP_RESERVED_KEY_FILE, O_RDONLY | O_CREAT, S_IRWXU);
    close(tempFd);

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
        *PtrToCFESegment  = (cpuaddr)(&_btext);
        *SizeOfCFESegment = (uint32)(((cpuaddr)&_etext) - ((cpuaddr)&_btext));

        return_code = CFE_PSP_SUCCESS;
    }

    return return_code;
}
