/******************************************************************************
** File:  cfe_psp_memory.c
**
**      Copyright (c) 2004-2011, United States Government as represented by
**      Administrator for The National Aeronautics and Space Administration.
**      All Rights Reserved.
**
**      This is governed by the NASA Open Source Agreement and may be used,
**      distributed and modified only pursuant to the terms of that agreement.
**
** Purpose:
**   cFE PSP Memory related functions
**
**   This is the implementation of the cFE memory areas that have to be
**   preserved, and the API that is designed to allow access to them.
**   It also contains memory related routines to return the address of the
**   kernel code used in the cFE checksum.
**
******************************************************************************/

/*
**  Include Files
*/
#include <stdio.h>
#include <string.h>
#include <vxWorks.h>
#include <sysLib.h>
#include <moduleLib.h>
#include <userReservedMem.h>
/*
** cFE includes
*/
#include "common_types.h"
#include "osapi.h"

#include "cfe_psp.h"
#include "cfe_psp_memory.h"

#include <target_config.h>
/*
** Macro Definitions
*/

/* Define cFE core loadable module name*/
#define CFE_MODULE_NAME "cfe-core.o"

/*
**  External Declarations
*/
extern unsigned long long GetWrsKernelTextStart(void);
extern unsigned long long GetWrsKernelTextEnd(void);


/*
** Global variables
*/

/*
** Pointer to the vxWorks USER_RESERVED_MEMORY area
** The sizes of each memory area is defined in os_processor.h for this architecture.
*/
CFE_PSP_ReservedMemoryMap_t CFE_PSP_ReservedMemoryMap;

CFE_PSP_MemoryBlock_t PSP_ReservedMemBlock;
/*
*********************************************************************************
** CDS related functions
*********************************************************************************
*/

/******************************************************************************
**  Function: CFE_PSP_GetCDSSize
**
**  Purpose:
**    This function fetches the size of the OS Critical Data Store area.
**
**  Arguments:
**    Output - pSizeOfCds - Pointer to variable that stores size of CDS
**
**  Return:
**    CFE_PSP_SUCCESS
**    CFE_PSP_ERROR
******************************************************************************/

int32 CFE_PSP_GetCDSSize(uint32 *SizeOfCDS)
{
   int32 return_code;

   if ( SizeOfCDS == NULL )
   {
       return_code = CFE_PSP_ERROR;
   }
   else
   {
       *SizeOfCDS =  (uint32)CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize;
       return_code = CFE_PSP_SUCCESS;
   }
   return(return_code);
}

/******************************************************************************
**  Function: CFE_PSP_WriteToCDS
**
**  Purpose:
**    This function writes to the CDS Block.
**
**  Arguments:
**    Input - PtrToDataToWrite - Pointer to the input data buffer
**    Input - CDSOffset - Memory offset of CDS
**    Input - NumBytes - Number of bytes to write to CDS
**
**  Return:
**    CFE_PSP_SUCCESS
**    CFE_PSP_ERROR
******************************************************************************/
int32 CFE_PSP_WriteToCDS(const void *PtrToDataToWrite, uint32 CDSOffset, uint32 NumBytes)
{
   uint8 *CopyPtr;
   int32  return_code;

   if ( PtrToDataToWrite == NULL )
   {
       return_code = CFE_PSP_ERROR;
   }
   else
   {
       if ( (CDSOffset < CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize ) &&
               ( (CDSOffset + NumBytes) <= CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize ))
       {
           CopyPtr = CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr;
           CopyPtr += CDSOffset;
           memcpy(CopyPtr, (char *)PtrToDataToWrite,NumBytes);

           return_code = CFE_PSP_SUCCESS;
       }
       else
       {
          return_code = CFE_PSP_ERROR;
       }

   } /* end if PtrToDataToWrite == NULL */

   return(return_code);
}


/******************************************************************************
**  Function: CFE_PSP_ReadFromCDS
**
**  Purpose:
**    This function reads from the CDS Block.
**
**  Arguments:
**    Output - PtrToDataToRead - Pointer to output data buffer
**    Input  - CDSOffset - Memory offset of CDS
**    Input  - NumBytes - Number of bytes to read from CDS
**
**  Return:
**    CFE_PSP_SUCCESS
**    CFE_PSP_ERROR
******************************************************************************/

int32 CFE_PSP_ReadFromCDS(void *PtrToDataToRead, uint32 CDSOffset, uint32 NumBytes)
{
   uint8 *CopyPtr;
   int32  return_code;

   if ( PtrToDataToRead == NULL )
   {
       return_code = CFE_PSP_ERROR;
   }
   else
   {
       if ( (CDSOffset < CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize ) &&
               ( (CDSOffset + NumBytes) <= CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize ))
       {
           CopyPtr = CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr;
           CopyPtr += CDSOffset;
           memcpy((char *)PtrToDataToRead,CopyPtr, NumBytes);

           return_code = CFE_PSP_SUCCESS;
       }
       else
       {
          return_code = CFE_PSP_ERROR;
       }

   } /* end if PtrToDataToWrite == NULL */

   return(return_code);

}

/*
*********************************************************************************
** ES Reset Area related functions
*********************************************************************************
*/

/******************************************************************************
**  Function: CFE_PSP_GetResetArea
**
**  Purpose:
**     This function returns the location and size of the ES Reset information area.
**     This area is preserved during a processor reset and is used to store the
**     ER Log, System Log and reset related variables
**
**  Arguments:
**    Output - PtrToResetArea - Pointer to the reset memory address
**    Output - SizeOfResetArea - Pointer to variable that stores size of memory
**
**  Return:
**    CFE_PSP_SUCCESS
**    CFE_PSP_ERROR
******************************************************************************/
int32 CFE_PSP_GetResetArea (cpuaddr *PtrToResetArea, uint32 *SizeOfResetArea)
{
   int32   return_code;

   if ((PtrToResetArea == NULL) || (SizeOfResetArea == NULL))
   {
      return_code = CFE_PSP_ERROR;
   }
   else
   {
      *PtrToResetArea = (cpuaddr)(CFE_PSP_ReservedMemoryMap.ResetMemory.BlockPtr);
      *SizeOfResetArea = (uint32)CFE_PSP_ReservedMemoryMap.ResetMemory.BlockSize;
      return_code = CFE_PSP_SUCCESS;
   }

   return(return_code);
}

/*
*********************************************************************************
** ES User Reserved Area related functions
*********************************************************************************
*/

/******************************************************************************
**  Function: CFE_PSP_GetUserReservedArea
**
**  Purpose:
**    This function returns the location and size of the memory used for the cFE
**    user-reserved area.
**
**  Arguments:
**    Output - PtrToUserArea - Pointer to user-reserved memory address
**    Output - SizeOfUserArea - Pointer to variable that stores size of memory
**
**  Return:
**    CFE_PSP_SUCCESS
**    CFE_PSP_ERROR
******************************************************************************/
int32 CFE_PSP_GetUserReservedArea(cpuaddr *PtrToUserArea, uint32 *SizeOfUserArea )
{
   int32   return_code;

   if ((PtrToUserArea == NULL) || (SizeOfUserArea == NULL))
   {
      return_code = CFE_PSP_ERROR;
   }
   else
   {
      *PtrToUserArea = (cpuaddr)(CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockPtr);
      *SizeOfUserArea = (uint32)CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockSize;
      return_code = CFE_PSP_SUCCESS;
   }

   return(return_code);
}

/*
*********************************************************************************
** ES Volatile disk memory related functions
*********************************************************************************
*/

/******************************************************************************
**  Function: CFE_PSP_GetVolatileDiskMem
**
**  Purpose:
**    This function returns the location and size of the memory used for the cFE
**     volatile disk.
**
**  Arguments:
**    Output - PtrToVolDisk - Pointer to the volatile disk memory address
**    Output - SizeOfVolDisk - Pointer to variable that stores size of memory
**
**  Return:
**    CFE_PSP_SUCCESS
**    CFE_PSP_ERROR
******************************************************************************/
int32 CFE_PSP_GetVolatileDiskMem(cpuaddr *PtrToVolDisk, uint32 *SizeOfVolDisk )
{
   int32   return_code;

   if ((PtrToVolDisk == NULL) || (SizeOfVolDisk == NULL))
   {
      return_code = CFE_PSP_ERROR;
   }
   else
   {
      *PtrToVolDisk = (cpuaddr)(CFE_PSP_ReservedMemoryMap.VolatileDiskMemory.BlockPtr);
      *SizeOfVolDisk = (uint32)CFE_PSP_ReservedMemoryMap.VolatileDiskMemory.BlockSize;
      return_code = CFE_PSP_SUCCESS;

   }

   return(return_code);

}


/*
*********************************************************************************
** ES BSP Top Level Reserved memory initialization
*********************************************************************************
*/

/******************************************************************************
**  Function: CFE_PSP_InitProcessorReservedMemory
**
**  Purpose:
**    This function performs the top level reserved memory initialization.
**
**  Arguments:
**    Input - RestartType - type of re-start
**
**  Return:
**    CFE_PSP_SUCCESS
******************************************************************************/
int32 CFE_PSP_InitProcessorReservedMemory( uint32 RestartType )
{
   cpuaddr start_addr;
   size_t reserve_memory_size = 0;
   int32 return_code = CFE_PSP_SUCCESS;

   userReservedGet((char**)&start_addr, &reserve_memory_size);

   if(PSP_ReservedMemBlock.BlockSize > reserve_memory_size)
   {
       OS_printf("CFE_PSP: VxWorks Reserved Memory Block Size not large enough, Total Size = 0x%lx, VxWorks Reserved Size=0x%lx\n",
               (unsigned long)PSP_ReservedMemBlock.BlockSize,
               (unsigned long)reserve_memory_size);
       return_code = OS_ERROR;

   }
   else if ( RestartType != CFE_PSP_RST_TYPE_PROCESSOR )
   {
      OS_printf("CFE_PSP: Clearing Processor Reserved Memory.\n");
      memset(PSP_ReservedMemBlock.BlockPtr, 0, PSP_ReservedMemBlock.BlockSize);

      /*
      ** Set the default reset type in case a watchdog reset occurs
      */
      CFE_PSP_ReservedMemoryMap.BootPtr->bsp_reset_type = CFE_PSP_RST_TYPE_PROCESSOR;

   }

   return(return_code);

}

/******************************************************************************
**  Function: CFE_PSP_SetupReservedMemoryMap
**
**  Purpose:
**    Set up the CFE_PSP_ReservedMemoryMap global data structure
**    This only sets the pointers, it does not initialize the data.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
void CFE_PSP_SetupReservedMemoryMap(void)
{
    cpuaddr start_addr;
    cpuaddr end_addr;
    size_t reserve_memory_size = 0;

    /*
    ** Setup the pointer to the reserved area in vxWorks.
    ** This must be done before any of the reset variables are used.
    */
    /*
    ** Note: this uses a "cpuaddr" (integer address) as an intermediate
    ** to avoid warnings about alignment.  The output of userReservedGet()
    ** should be aligned to hold any data type, being the very start
    ** of the memory space.
    */
    userReservedGet((char**)&start_addr, &reserve_memory_size);

    end_addr = start_addr;

    memset(&CFE_PSP_ReservedMemoryMap, 0, sizeof(CFE_PSP_ReservedMemoryMap));

    CFE_PSP_ReservedMemoryMap.BootPtr = (CFE_PSP_ReservedMemoryBootRecord_t *)end_addr;
    end_addr += sizeof(CFE_PSP_ReservedMemoryBootRecord_t);
    end_addr = (end_addr + CFE_PSP_MEMALIGN_MASK) & ~CFE_PSP_MEMALIGN_MASK;

    CFE_PSP_ReservedMemoryMap.ExceptionStoragePtr = (CFE_PSP_ExceptionStorage_t *)end_addr;
    end_addr += sizeof(CFE_PSP_ExceptionStorage_t);
    end_addr = (end_addr + CFE_PSP_MEMALIGN_MASK) & ~CFE_PSP_MEMALIGN_MASK;

    CFE_PSP_ReservedMemoryMap.ResetMemory.BlockPtr = (void*)end_addr;
    CFE_PSP_ReservedMemoryMap.ResetMemory.BlockSize = GLOBAL_CONFIGDATA.CfeConfig->ResetAreaSize;
    end_addr += CFE_PSP_ReservedMemoryMap.ResetMemory.BlockSize;
    end_addr = (end_addr + CFE_PSP_MEMALIGN_MASK) & ~CFE_PSP_MEMALIGN_MASK;

    CFE_PSP_ReservedMemoryMap.VolatileDiskMemory.BlockPtr = (void*)end_addr;
    CFE_PSP_ReservedMemoryMap.VolatileDiskMemory.BlockSize =
        GLOBAL_CONFIGDATA.CfeConfig->RamDiskSectorSize * GLOBAL_CONFIGDATA.CfeConfig->RamDiskTotalSectors;
    end_addr += CFE_PSP_ReservedMemoryMap.VolatileDiskMemory.BlockSize;
    end_addr = (end_addr + CFE_PSP_MEMALIGN_MASK) & ~CFE_PSP_MEMALIGN_MASK;

    CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr = (void*)end_addr;
    CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize = GLOBAL_CONFIGDATA.CfeConfig->CdsSize;
    end_addr += CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize;
    end_addr = (end_addr + CFE_PSP_MEMALIGN_MASK) & ~CFE_PSP_MEMALIGN_MASK;

    CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockPtr = (void*)end_addr;
    CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockSize = GLOBAL_CONFIGDATA.CfeConfig->UserReservedSize;
    end_addr += CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockSize;
    end_addr = (end_addr + CFE_PSP_MEMALIGN_MASK) & ~CFE_PSP_MEMALIGN_MASK;

    /* The total size of the entire block is the difference in address */
    PSP_ReservedMemBlock.BlockPtr = (void*)start_addr;
    PSP_ReservedMemBlock.BlockSize =  end_addr - start_addr;

    OS_printf("CFE_PSP: Reserved Memory Block at 0x%p, Total Size = 0x%lx, VxWorks Reserved Size=0x%lx\n",
            PSP_ReservedMemBlock.BlockPtr,
            PSP_ReservedMemBlock.BlockSize,
            reserve_memory_size);
}

/******************************************************************************
 * Function: CFE_PSP_DeleteProcessorReservedMemory
 *
 * No action on SP0 - reserved block is statically allocated as user reserved
 * memory.
 * Implemented for API consistency with other PSPs.
 */
void CFE_PSP_DeleteProcessorReservedMemory(void)
{
}

/*
*********************************************************************************
** ES BSP kernel memory segment functions
*********************************************************************************
*/

/******************************************************************************
**  Function: CFE_PSP_GetKernelTextSegmentInfo
**
**  Purpose:
**    This function returns the start and end address of the kernel text segment.
**     It may not be implemented on all architectures.
**
**  Arguments:
**    Output - PtrToKernelSegment - Pointer to kernel segment memory address
**    Output - SizeOfKernelSegment - Pointer to variable that stores memory size
**
**  Return:
**    CFE_PSP_SUCCESS
**    CFE_PSP_ERROR
******************************************************************************/
int32 CFE_PSP_GetKernelTextSegmentInfo(cpuaddr *PtrToKernelSegment, uint32 *SizeOfKernelSegment)
{
   int32 return_code;
   cpuaddr StartAddress;
   cpuaddr EndAddress;

   if ( SizeOfKernelSegment == NULL )
   {
      return_code = CFE_PSP_ERROR;
   }
   else
   {
      /*
      ** Get the kernel start and end
      ** addresses from the BSP, because the
      ** symbol table does not contain the symbls we need for this
      */
      StartAddress = (cpuaddr) GetWrsKernelTextStart();
      EndAddress = (cpuaddr) GetWrsKernelTextEnd();

      *PtrToKernelSegment = StartAddress;
      *SizeOfKernelSegment = (uint32) (EndAddress - StartAddress);

      return_code = CFE_PSP_SUCCESS;
   }

   return(return_code);
}

/******************************************************************************
**  Function: CFE_PSP_GetCFETextSegmentInfo
**
**  Purpose:
**    This function returns the start and end address of the CFE text segment.
**     It may not be implemented on all architectures.
**
**  Arguments:
**    Output - PtrToCFESegment - Pointer to CFE segment memory address
**    Output - SizeOfCFESegment - Pointer to variable that stores memory size
**
**  Return:
**    CFE_PSP_SUCCESS
**    CFE_PSP_ERROR
******************************************************************************/
int32 CFE_PSP_GetCFETextSegmentInfo(cpuaddr *PtrToCFESegment, uint32 *SizeOfCFESegment)
{
   int32       return_code;
   STATUS      status;
   MODULE_ID   cFEModuleId;
   MODULE_INFO cFEModuleInfo;

   if ( SizeOfCFESegment == NULL )
   {
      return_code = CFE_PSP_ERROR;
   }
   else
   {
       char name[] = CFE_MODULE_NAME;
      cFEModuleId = moduleFindByName(name);

      if ( cFEModuleId == NULL )
      {
         return_code = CFE_PSP_ERROR;
      }
      else
      {
         status = moduleInfoGet(cFEModuleId, &cFEModuleInfo);
         if ( status != ERROR )
         {
            *PtrToCFESegment = (cpuaddr) (cFEModuleInfo.segInfo.textAddr);
            *SizeOfCFESegment = (uint32) (cFEModuleInfo.segInfo.textSize);
            return_code = CFE_PSP_SUCCESS;
         }
         else
         {
            return_code = CFE_PSP_SUCCESS;
         }
      }
   }

   return(return_code);
}



