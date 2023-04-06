/*
 *  Copyright (c) 2015, United States government as represented by the
 *  administrator of the National Aeronautics Space Administration.
 *  All rights reserved. This software was created at NASA Glenn
 *  Research Center pursuant to government contracts.
 */

/**
 * \file
 *
 * I/O adapter for memory device access
 */

#ifndef CFE_PSP_IODRIVER_MEMORY_IO_H
#define CFE_PSP_IODRIVER_MEMORY_IO_H

/* Include all base definitions */
#include "iodriver_base.h"

/**
 * API container for memory write commands.
 *
 * Associates a device address, buffer pointer and a buffer size.
 */
typedef struct
{
    uint32      DeviceAddress;
    uint32      BufferSize;
    const void *BufferMem;
} CFE_PSP_IODriver_WriteMemoryBuffer_t;

/**
 * API container for memory write commands.
 *
 * Associates a device address, buffer pointer and a buffer size.
 */
typedef struct
{
    uint32 DeviceAddress;
    uint32 BufferSize;
    void * BufferMem;
} CFE_PSP_IODriver_ReadMemoryBuffer_t;

/**
 * Opcodes specific to memory devices or other direct register-oriented interfaces
 */
enum
{
    CFE_PSP_IODriver_MEMORY_IO_NOOP = CFE_PSP_IODriver_MEMORY_IO_CLASS_BASE,

    CFE_PSP_IODriver_MEMORY_IO_READ_32,    /**< CFE_PSP_IODriver_ReadMemoryBuffer_t argument, use 32 bit access */
    CFE_PSP_IODriver_MEMORY_IO_WRITE_32,   /**< CFE_PSP_IODriver_WriteMemoryBuffer_t argument, use 32 bit access */
    CFE_PSP_IODriver_MEMORY_IO_READ_16,    /**< CFE_PSP_IODriver_ReadMemoryBuffer_t argument, use 16 bit access */
    CFE_PSP_IODriver_MEMORY_IO_WRITE_16,   /**< CFE_PSP_IODriver_WriteMemoryBuffer_t argument, use 16 bit access */
    CFE_PSP_IODriver_MEMORY_IO_READ_8,     /**< CFE_PSP_IODriver_ReadMemoryBuffer_t argument, use 8 bit access */
    CFE_PSP_IODriver_MEMORY_IO_WRITE_8,    /**< CFE_PSP_IODriver_WriteMemoryBuffer_t argument, use 8 bit access */
    CFE_PSP_IODriver_MEMORY_IO_READ_BLOCK, /**< CFE_PSP_IODriver_ReadMemoryBuffer_t argument, use any appropriate access
                                              cycle (generic) */
    CFE_PSP_IODriver_MEMORY_IO_WRITE_BLOCK, /**< CFE_PSP_IODriver_WriteMemoryBuffer_t argument, use any appropriate
                                               access cycle (generic) */

    CFE_PSP_IODriver_MEMORY_IO_MAX
};

#endif /* CFE_PSP_IODRIVER_MEMORY_IO_H */
