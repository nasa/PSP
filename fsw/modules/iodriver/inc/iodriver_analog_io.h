/*
 *  Copyright (c) 2015, United States government as represented by the
 *  administrator of the National Aeronautics Space Administration.
 *  All rights reserved. This software was created at NASA Glenn
 *  Research Center pursuant to government contracts.
 */

/**
 * \file
 *
 * I/O adapter for analog (ADC/DAC) devices
 */

#ifndef CFE_PSP_IODRIVER_ANALOG_IO_H
#define CFE_PSP_IODRIVER_ANALOG_IO_H

/* Include all base definitions */
#include "iodriver_base.h"

/**
 * Standardized width of ADC/DAC codes.
 *
 * This should reflect the highest-precision ADC that the system is expected to use.  ADC inputs
 * that are less precise than this will be bit-expanded in software such that all processing
 * in the upper layers receives consistent data no matter what the actual hardware implements.
 * This permits easier swapping between different phsyical hardware types, including those with
 * potentially less ADC/DAC precision, while presenting similar values to application code.
 */
#define CFE_PSP_IODRIVER_ADC_BITWIDTH 24

/**
 * Type abstraction for expressing analog ADC codes.
 *
 * This type is an integer type of at least CFE_PSP_IODRIVER_ADC_BITWIDTH in length.  It is used
 * as a parameter for the Read/Write opcodes on ADC/DAC channels.  Normalized (fixed-width) ADC
 * codes are used at this layer rather than floating point due to the fact that floats involve a
 * lot of extra overhead and some CPUs do not have FP units at all.
 *
 * If desired on CPUs that are capable of good-performance floating point operations, another
 * module/CFS application can convert the ADC codes to real-word floats.  This would be done
 * outside the I/O driver layer.
 */
typedef int32 CFE_PSP_IODriver_AdcCode_t;

/**
 * Complete API container for analog read/write commands.
 * This allows reading/writing multiple channels at once with a single entry into the API.
 * As each entry into the API needs to acquire a mutex for serialization, this can be much
 * more efficient to read channels through this means rather than single channel read/write.
 * Set NumChannels to 1 to perform single channel read/write
 */
typedef struct
{
    uint16 NumChannels;                  /**<  Number of channels in the i/o structure (length of "samples" array) */
    CFE_PSP_IODriver_AdcCode_t *Samples; /**<  Array for ADC/DAC samples */
} CFE_PSP_IODriver_AnalogRdWr_t;

/**
 * Opcodes specific to analog io (ADC/DAC) devices
 */
enum
{
    CFE_PSP_IODriver_ANALOG_IO_NOOP = CFE_PSP_IODriver_ANALOG_IO_CLASS_BASE,

    CFE_PSP_IODriver_ANALOG_IO_READ_CHANNELS,  /**< CFE_PSP_IODriver_AnalogRdWr_t argument */
    CFE_PSP_IODriver_ANALOG_IO_WRITE_CHANNELS, /**< CFE_PSP_IODriver_AnalogRdWr_t argument */

    CFE_PSP_IODriver_ANALOG_IO_MAX
};

#endif /* CFE_PSP_IODRIVER_ANALOG_IO_H */
