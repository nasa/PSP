/*
**  Author:  A. Cudmore
**
**  Purpose:  This file contains PSP support routine internal prototypes
**            and typedefs. The routines and typedefs are intended for
**            the local PSP routines only.
**
**  Modification History:
**
*/

#ifndef CFE_PSP_MEMORY_H
#define CFE_PSP_MEMORY_H

/*
** Include Files
*/

#include "common_types.h"
#include "cfe_psp_config.h"
#include "cfe_psp_exceptionstorage_types.h"

/*
** Memory table type
*/
typedef struct
{
    uint32  MemoryType;
    size_t  WordSize;
    cpuaddr StartAddr;
    size_t  Size;
    uint32  Attributes;
} CFE_PSP_MemTable_t;

typedef struct
{
    void * BlockPtr;
    size_t BlockSize;

} CFE_PSP_MemoryBlock_t;

typedef struct
{
    CFE_PSP_ReservedMemoryBootRecord_t *BootPtr;
    CFE_PSP_ExceptionStorage_t *        ExceptionStoragePtr;

    CFE_PSP_MemoryBlock_t ResetMemory;
    CFE_PSP_MemoryBlock_t VolatileDiskMemory;
    CFE_PSP_MemoryBlock_t CDSMemory;
    CFE_PSP_MemoryBlock_t UserReservedMemory;

    /**
     * \brief The system memory table
     *
     * This is the table used for CFE_PSP_MemRangeGet/Set and related ops
     * that allow CFE applications to query the general system memory map.
     */

    CFE_PSP_MemTable_t SysMemoryTable[CFE_PSP_MEM_TABLE_SIZE];

} CFE_PSP_ReservedMemoryMap_t;

/**
 * \brief Initialize the CFE_PSP_ReservedMemoryMap global object
 *
 * This must be called by the startup code before the map is accessed.
 */
extern void CFE_PSP_SetupReservedMemoryMap(void);

/*
 * CFE_PSP_InitProcessorReservedMemory initializes all of the memory in the
 * BSP that is preserved on a processor reset. The memory includes the
 * Critical Data Store, the ES Reset Area, the Volatile Disk Memory, and
 * the User Reserved Memory.
 *
 * This initializes based on the reset type.  Typically, the information
 * is preserved on a processor reset, and cleared/reinitialized on a power-on
 * reset.
 */
extern int32 CFE_PSP_InitProcessorReservedMemory(uint32 RestartType);

/**
 * \brief Unlink the memory segments within the CFE_PSP_ReservedMemoryMap global object
 *
 * This function is only relevant on systems where the objects are implemented
 * as kernel shared memory segments.  The segments will be marked for deletion
 * but the local maps remain usable until the process ends.
 */
extern void CFE_PSP_DeleteProcessorReservedMemory(void);

/*
** External variables
*/

/*
** Map to the reserved memory area(s)
** Contains a pointer to each of the separate memory blocks
*/
extern CFE_PSP_ReservedMemoryMap_t CFE_PSP_ReservedMemoryMap;

#endif
