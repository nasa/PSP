/*
 *  Copyright (c) 2015, United States government as represented by the
 *  administrator of the National Aeronautics Space Administration.
 *  All rights reserved. This software was created at NASA Glenn
 *  Research Center pursuant to government contracts.
 */

/**
 * \file
 *
 * I/O adapter for streams
 */

#ifndef CFE_PSP_IODRIVER_STREAM_IO_H
#define CFE_PSP_IODRIVER_STREAM_IO_H

/* Include all base definitions */
#include "iodriver_base.h"

/**
 * API container for stream write commands.
 * -- Associates a buffer pointer and a buffer size.
 */
typedef struct
{
    uint32      BufferSize; /**<  Size of data buffer */
    const void *BufferMem;  /**<  Pointer to data buffer to write */
} CFE_PSP_IODriver_WriteStreamBuffer_t;

/**
 * API container for stream read commands.
 * -- Associates a buffer pointer and a buffer size.
 */
typedef struct
{
    uint32 BufferSize; /**<  Size of data buffer */
    void * BufferMem;  /**<  Pointer to data buffer to store read data */
} CFE_PSP_IODriver_ReadStreamBuffer_t;

/**
 * Opcodes specific to stream oriented interfaces
 * FIX: Right now these are the same as the packet interface and need to be changed.
 */
enum
{
    CFE_PSP_IODriver_STREAM_IO_NOOP = CFE_PSP_IODriver_STREAM_IO_CLASS_BASE,

    CFE_PSP_IODriver_STREAM_IO_READ,  /**< CFE_PSP_IODriver_ReadStreamBuffer_t argument */
    CFE_PSP_IODriver_STREAM_IO_WRITE, /**< CFE_PSP_IODriver_WriteStreamBuffer_t argument */

    CFE_PSP_IODriver_STREAM_IO_MAX
};

/**
 * Additional error codes specific to Stream I/O
 *
 * These are based from the CFE_PSP_IODriver_STREAM_IO_CLASS_BASE so as to not conflict with other classes of I/O
 */
enum
{
    CFE_PSP_IODriver_STREAM_ERROR_BASE = -(CFE_PSP_IODriver_STREAM_IO_CLASS_BASE + 0xFFFF),
    CFE_PSP_IODriver_STREAM_LENGTH_ERROR,
    CFE_PSP_IODriver_STREAM_CRC_ERROR
};

#endif /* CFE_PSP_IODRIVER_STREAM_IO_H */
