/*
 *  Copyright (c) 2015, United States government as represented by the
 *  administrator of the National Aeronautics Space Administration.
 *  All rights reserved. This software was created at NASA Glenn
 *  Research Center pursuant to government contracts.
 */

/**
 * \file
 *
 * Generic abstraction API for on-board devices
 *
 * The design of this interface is similar to the POSIX "ioctl()" in concept -
 * A single interface function, with 3 basic arguments:
 *  - A device/target identifier
 *  - A command "opcode"
 *  - A generic argument containing the I/O parameter for that opcode
 *
 * Note that the last argument may in fact be a structure for opcodes that
 * require multiple parameters.
 *
 * This type of interface makes it fairly simple to swap one hardware device
 * for another, as long as they both implement a common set of opcodes, while
 * also being extendable/customizable by adding additional opcodes to expose
 * device-specific functionality, as long as those extension opcodes do not
 * interfere or overlap with the common set.
 */

#ifndef IODRIVER_BASE_H
#define IODRIVER_BASE_H

#include <common_types.h>

/**
 * Physical channel location descriptor.
 *
 * See the CFE_PSP_IODriver_LOOKUP_SUBCHANNEL opcode to determine channel number to set in here,
 * as each board may have their own unique channel naming conventions.  The integer value that
 * goes in this structure may or may not correlate to the physical device labeling.
 */
typedef struct
{
    uint32 PspModuleId;  /**<  Device selection */
    uint16 SubsystemId;  /**<  Instance or subsystem number */
    uint16 SubchannelId; /**<  Subchannel number - optional, set to 0 for devices that do not have multiple channels */
} CFE_PSP_IODriver_Location_t;

/**
 * Wrapper for constant arguments, to avoid a compiler warning
 * about arguments differing in const-ness.  Use the inline functions to
 * pass in an immediate/constant value.
 */
typedef union
{
    void *      Vptr;
    const void *ConstVptr;
    const char *ConstStr;
    uint32      U32;
} CFE_PSP_IODriver_Arg_t;

static inline CFE_PSP_IODriver_Arg_t CFE_PSP_IODriver_VPARG(void *x)
{
    CFE_PSP_IODriver_Arg_t a;
    a.Vptr = x;
    return a;
}
static inline CFE_PSP_IODriver_Arg_t CFE_PSP_IODriver_CONST_VPARG(const void *x)
{
    CFE_PSP_IODriver_Arg_t a;
    a.ConstVptr = x;
    return a;
}
static inline CFE_PSP_IODriver_Arg_t CFE_PSP_IODriver_CONST_STR(const char *x)
{
    CFE_PSP_IODriver_Arg_t a;
    a.ConstStr = x;
    return a;
}
static inline CFE_PSP_IODriver_Arg_t CFE_PSP_IODriver_U32ARG(uint32 x)
{
    CFE_PSP_IODriver_Arg_t a;
    a.U32 = x;
    return a;
}

/**
 * Standardized concept of directionality for any device
 *
 * Some code may use these enumeration values as a bitmask -
 * use care when updating to ensure that the values may be used as bitmasks.
 * Specific hardware drivers may or may not implement all modes depending on capabilities.
 */
typedef enum
{
    CFE_PSP_IODriver_Direction_DISABLED     = 0,    /**<  Disabled (inactive, tri-state if possible) */
    CFE_PSP_IODriver_Direction_INPUT_ONLY   = 0x01, /**<  Device/channel is configured for input */
    CFE_PSP_IODriver_Direction_OUTPUT_ONLY  = 0x02, /**<  Device/channel is configured for output */
    CFE_PSP_IODriver_Direction_INPUT_OUTPUT = 0x03  /**<  Input/Output (some HW supports this) */
} CFE_PSP_IODriver_Direction_t;

/**
 * Some common values for the device command codes
 * These are some VERY basic ops that many devices may support in some way.
 * Any opcode that is not implemented should return CFE_PSP_ERROR_NOT_IMPLEMENTED
 *
 * Negative return values indicate an error of some type, while return values >= 0 indicate success
 */
enum
{
    CFE_PSP_IODriver_NOOP = 0, /**< Reserved, do nothing */

    /* Start/stop opcodes */
    CFE_PSP_IODriver_SET_RUNNING = 1, /**< uint32 argument, 0=stop 1=start device */
    CFE_PSP_IODriver_GET_RUNNING = 2, /**< no argument, returns positive nonzero (true) if running and zero (false) if
                                     stopped, negative on error */

    /* Configuration opcodes */
    CFE_PSP_IODriver_SET_CONFIGURATION = 3, /**< const string argument (device-dependent content) */
    CFE_PSP_IODriver_GET_CONFIGURATION = 4, /**< void * argument (device-dependent content) */

    /* Sub-channel configuration/mapping opcodes */
    CFE_PSP_IODriver_LOOKUP_SUBSYSTEM = 5,  /**< const char * argument, looks up ChannelName and returns positive value
                                           for  subsystem ID, negative value for error */
    CFE_PSP_IODriver_LOOKUP_SUBCHANNEL = 6, /**< const char * argument, looks up ChannelName and returns positive value
                                           for subchannel ID, negative value for error */
    CFE_PSP_IODriver_SET_DIRECTION   = 7,   /**< U32 (CFE_PSP_IODriver_Direction_t) argument as input */
    CFE_PSP_IODriver_QUERY_DIRECTION = 8,   /**< U32 (CFE_PSP_IODriver_Direction_t) argument as output */

    /*
     * Placeholders for opcodes that could be implemented across a class of devices.
     * For instance, all ADC/DAC devices should implement a common set of read/write opcodes
     * so that devices can be interchanged without affecting higher-level software
     */
    CFE_PSP_IODriver_ANALOG_IO_CLASS_BASE   = 0x00010000, /**< Opcodes for typical adc/dac devices */
    CFE_PSP_IODriver_DISCRETE_IO_CLASS_BASE = 0x00020000, /**< Opcodes for discrete IO (digital logic) devices */
    CFE_PSP_IODriver_PACKET_IO_CLASS_BASE   = 0x00030000, /**< Opcodes for packet/datagram-oriented devices */
    CFE_PSP_IODriver_MEMORY_IO_CLASS_BASE   = 0x00040000, /**< Opcodes for memory/register oriented devices */
    CFE_PSP_IODriver_STREAM_IO_CLASS_BASE   = 0x00050000, /**< Opcodes for data stream oriented devices */

    /**
     * Placeholder for extended opcodes that may be very specific to a single device/device type.
     * This allows the same API call (CFE_PSP_DeviceCommandFunc_t) but
     */
    CFE_PSP_IODriver_EXTENDED_BASE = 0x7FFF0000

};

/* ------------------------------------------------------------- */
/**
 * @brief Find an IO device module ID by name
 *
 * @param DriverName the device name to find
 * @param PspModuleId location to store the module ID, if found
 *
 * @retval #CFE_PSP_SUCCESS if found, or error code if not found
 */
int32 CFE_PSP_IODriver_FindByName(const char *DriverName, uint32 *PspModuleId);

/* ------------------------------------------------------------- */
/**
 * @brief Issue a request to an IO device module
 *
 * @param Location Aggregate location identifier
 * @param CommandCode Request identifier
 * @param Arg Request Argument
 *
 * @retval #CFE_PSP_SUCCESS if successful, or error code if not successful
 */
int32 CFE_PSP_IODriver_Command(const CFE_PSP_IODriver_Location_t *Location, uint32 CommandCode,
                               CFE_PSP_IODriver_Arg_t Arg);

#endif /* IODRIVER_BASE_H */
