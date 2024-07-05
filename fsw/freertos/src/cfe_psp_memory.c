#include <sysLib.h>

#include "cfe_psp.h"
#include "cfe_psp_config.h"	// TODO: set up (for reservedbootrecord and memalign mask)
#include "cfe_psp_memory.h"
#include "common_types.h"	// defined in osal/src/os/inc

/* macros */
#define CFE_PSP_CDS_SIZE (GLOBAL_CONFIGDATA.CfeConfig->CdsSize)
#define CFE_PSP_RESET_AREA_SIZE (GLOBAL_CONFIGDATA.CfeConfig->ResetAreaSize)
#define CFE_PSP_USER_RESERVED_SIZE (GLOBAL_CONFIGDATA.CfeConfig->UserReservedSize)
#define CFE_PSP_RAM_DISK_SECTOR_SIZE (GLOBAL_CONFIGDATA.CfeConfig->RamDiskSectorSize)
#define CFE_PSP_RAM_DISK_NUM_SECTORS (GLOBAL_CONFIGDATA.CfeConfig->RamDiskTotalSectors)

#define CFE_PSP_RESERVED_MEMORY_SIZE 200 * 1024

#define CFE_PSP_BOOT_RECORD_SIZE (sizeof(CFE_PSP_ReservedMemoryBootRecord_t))
#define CFE_PSP_EXCEPTION_RECORD_SIZE (sizeof(CFE_PSP_ExceptionStorage_t))


#define memalign(x) (x + CFE_PSP_MEMALIGN_MASK) & ~CFE_PSP_MEMALIGN_MASK

/* ------ */





/* Global Variables */

CFE_PSP_ReservedMemoryMap_t CFE_PSP_ReservedMemoryMap = { 0 };

__attribute__ ((section(".psp_reserved")))
__attribute__ ((aligned (8)))
char pspReservedMemoryAlloc[CFE_PSP_RESERVED_MEMORY_SIZE];


/* ---------------- */



/* 
 * CDS related functions
 */

init32 CFE_PSP_GetCDSSize(uint32 *SizeOfCDS)
{

	if (SizeOfCDS == NULL)
	{
		return CFE_PSP_ERROR;
	}
	
	*SizeOfCDS = CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize;
	
	return CFE_PSP_SUCCESS;
}


int32 CFE_PSP_WriteToCDS(const void *PtrToDataToWrite, uint32 CDSOffset, uint32 NumBytes)
{
	uint8 *CopyPtr;

	if (PtrToDataToWrite == NULL ||
			(CDSOffset >= CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize) ||
			((CDSOffset + NumBytes) > CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize))
	{
		return CFE_PSP_ERROR;
	}

	CopyPtr = CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr;
	CopyPtr += CDSOffset;
	memcpy((char *)CopyPtr, (char *)PtrToDataToWrite, NumBytes);

	return CFE_PSP_SUCCESS;
}

int32 CFE_PSP_ReadFromCDS(void *PtrToDataToRead, uint32 CDSOffset, uint32 NumBytes)
{
	uint8 *CopyPtr;
	
	if (PtrToDataToRead == NULL ||
			(CDSOffset >= CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize) ||
			((CDSOffset + NumBytes) > CFE_PSP_ReservedMemoryMap.CDSMemory.BlockSize))
	{
		return CFE_PSP_ERROR;
	}

	CopyPtr = CFE_PSP_ReservedMemoryMap.CDSMemory.BlockPtr;
	CopyPtr += CDSOffset;
	memcpy((char *)PtrToDataToRead, (char *)CopyPtr, NumBytes);

	return CFE_PSP_SUCCESS;
}

/*
 * Reset Area related functions
 */

int32 CFE_PSP_GetResetArea(cpuaddr *PtrToResetArea, uint32 *SizeOfResetArea)
{
	if (PtrToResetArea == NULL || SizeOfResetArea == NULL)
	{
		return CFE_PSP_ERROR;
	}

	*PtrToResetArea = (cpuaddr)CFE_PSP_ReservedMemoryMap.ResetMemory.BlockPtr;
	*SizeOfResetArea = CFE_PSP_ReservedMemoryMap.ResetMemory.BlockSize;
	
	return CFE_PSP_SUCCESS;
}

/*
 * Reserved Area related functions
 */

int32 CFE_PSP_GetUserReservedArea(cpuaddr *PtrToUserArea, uint32 *SizeOfUserArea)
{
	if (PtrToUserArea == NULL || PtrToUserArea == NULL)
	{
		return CFE_PSP_ERROR;
	}

	*PtrToUserArea = (cpuaddr)CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockPtr;
	*SizeOfUserArea = CFE_PSP_ReservedMemoryMap.UserReservedMemory.BlockSize;

	return CFE_PSP_SUCCESS;
}

/*
 * Volatile Disk Memory related functions
 */

int32 CFE_PSP_GetVolatileDiskMem(cpuaddr *PtrToVolDisk, uint32 *SizeOfVolDisk)
{
	if (PtrToVolDisk == NULL || SizeOfVolDisk == NULL)
	{
		return CFE_PSP_ERROR;
	}

	*PtrToVolDisk = (cpuaddr)CFE_PSP_ReservedMemoryMap.VolatileDiskMemory.BlockPtr;
	*SizeOfVolDisk = CFE_PSP_ReservedMemoryMap.VolatileDiskMemory.BlockSize;

	return CFE_PSP_SUCCESS;
}

/*
 * Kernel Memory functions
 */

int32 CFE_PSP_GetKernelTextSegmentInfo(cpuaddr *PtrToKernelSegment, uint32 *SizeOfKernelSegment)
{
	cpuaddr StartAddress;
	cpuaddr EndAddress;

	if (SizeOfKernelSegment == NULL)
	{
		return CFE_PSP_ERROR;
	}

	StartAddress = 0; 	// TODO: get kernel start address
	EndAddress = 0;		// TODO: get kernel end address
	
	*PtrToKernelSegment = StartAddress;
	*SizeOfKernelSegment = (uint32)(EndAddress - StartAddress);

	return CFE_PSP_SUCCESS;
}

/*
 * Top Level Reserved Memory initialization
 */

int32 CFE_PSP_InitProcessorReservedMemory(uint32 RestartType)
{
	if (RestartType != CFE_PSP_RST_TYPE_PROCESSOR)
	{
		memset(ReservedMemBlock.BlockPtr, 0, ReservedMemBlock.BlockSize);

		CFE_PSP_ReservedMemoryMap.BootPtr->bsp_reset_type = CFE_PSP_RST_TYPE_PROCESSOR;
	}

	return CFE_PSP_SUCCESS;
}


void CFE_PSP_SetupReservedMemoryMap(void)
{
	cpuaddr ReservedMemoryAddr;

	size_t ResetSize = memalign(CFE_PSP_RESET_AREA_SIZE);
	size_t CDSSize = memalign(CFE_PSP_CDS_SIZE);
	size_t UserReservedSize = memalign(CFE_PSP_USER_RESERVED_SIZE);
	size_t VolatileDiskSize = memalign(CFE_PSP_RAM_DISK_SECTOR_SIZE * CFE_PSP_RAM_DISK_NUM_SECTORS);
	size_t RequiredSize = 0;

	RequiredSize += ResetSize;
	RequiredSize += CDSSize;
	RequiredSize += UserReservedSize;
	RequiredSize += VolatileDiskSize;

	if ((unsigned int) RequiredSize > CFE_PSP_RESERVED_MEMORY_SIZE)
	{
		return;
	}

	ReservedMemoryAddr = pspReservedMemoryAlloc;

	CFE_PSP_ReservedMemoryMap.BootPtr = (void *)ReservedMemoryAddr;	
	ReservedMemoryAddr += CFE_PSP_BOOT_RECORD_SIZE;

	CFE_PSP_ReservedMemoryMap.ExceptionStoragePtr = (void *)ReservedMemoryAddr;
	ReservedMemoryAddr += CFE_PSP_EXCEPTION_RECORD_SIZE;
	
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

// TODO: is an action needed?
void CFE_PSP_DeleteProcessorReservedMemory(void) {}
