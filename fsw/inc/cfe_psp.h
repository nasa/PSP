/************************************************************************
 * NASA Docket No. GSC-18,719-1, and identified as “core Flight System: Bootes”
 *
 * Copyright (c) 2020 United States Government as represented by the
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

/*
**  Author:  A. Cudmore
**
**  Purpose:  This file contains the cFE Platform Support Package(PSP)
**            prototypes.
**            The PSP routines serve as the "glue" between the RTOS and
**            the cFE Flight Software. The routines fill gaps that are not
**            really considered part of the OS Abstraction, but are required
**            for the cFE flight software implementation. It is possible that
**            some of these routines could migrate into the OS AL.
**
*/

#ifndef CFE_PSP_H
#define CFE_PSP_H

/******************************************************************************
 INCLUDE FILES
 ******************************************************************************/

#include "common_types.h"
#include "osapi.h"

#include "cfe_psp_error.h"

/******************************************************************************
 MACRO DEFINITIONS
 ******************************************************************************/

/*
** Definitions for PSP PANIC types
*/
#define CFE_PSP_PANIC_STARTUP         1
#define CFE_PSP_PANIC_VOLATILE_DISK   2
#define CFE_PSP_PANIC_MEMORY_ALLOC    3
#define CFE_PSP_PANIC_NONVOL_DISK     4
#define CFE_PSP_PANIC_STARTUP_SEM     5
#define CFE_PSP_PANIC_CORE_APP        6
#define CFE_PSP_PANIC_GENERAL_FAILURE 7

/*
** Macros for the file loader
*/
#define BUFF_SIZE 256
#define SIZE_BYTE 1
#define SIZE_HALF 2
#define SIZE_WORD 3

/*
** Define memory types
*/
#define CFE_PSP_MEM_RAM     1
#define CFE_PSP_MEM_EEPROM  2
#define CFE_PSP_MEM_ANY     3
#define CFE_PSP_MEM_INVALID 4

/*
** Define Memory Read/Write Attributes
*/
#define CFE_PSP_MEM_ATTR_WRITE     0x01
#define CFE_PSP_MEM_ATTR_READ      0x02
#define CFE_PSP_MEM_ATTR_READWRITE 0x03

/*
** Define the Memory Word Sizes
*/
#define CFE_PSP_MEM_SIZE_BYTE  0x01
#define CFE_PSP_MEM_SIZE_WORD  0x02
#define CFE_PSP_MEM_SIZE_DWORD 0x04

/*
 * Common definition for reset types at the PSP layer
 */
/** @name Reset Types */
/** \{ */
#define CFE_PSP_RST_TYPE_PROCESSOR 1 /**< Volatile disk, CDS and User Reserved memory may be valid */
#define CFE_PSP_RST_TYPE_POWERON   2 /**< All memory has been cleared */
#define CFE_PSP_RST_TYPE_MAX       3 /**< Placeholder to indicate 1+ the maximum value that the PSP will ever use. */
/** \} */

/*
** Reset Sub-Types
*/
/** @name Reset Sub-Types */
/** \{ */

/** @brief Reset caused by power having been removed and restored */
#define CFE_PSP_RST_SUBTYPE_POWER_CYCLE 1
/** @brief Reset caused by reset button on the board */
#define CFE_PSP_RST_SUBTYPE_PUSH_BUTTON 2
/** @brief Reset was caused by a reset line having been stimulated by a hardware special command */
#define CFE_PSP_RST_SUBTYPE_HW_SPECIAL_COMMAND 3
/** @brief Reset was caused by a watchdog timer expiring */
#define CFE_PSP_RST_SUBTYPE_HW_WATCHDOG 4
/** @brief Reset was caused by cFE ES processing a @link #CFE_ES_RESTART_CC Reset Command @endlink */
#define CFE_PSP_RST_SUBTYPE_RESET_COMMAND 5
/** @brief Reset was caused by a Processor Exception */
#define CFE_PSP_RST_SUBTYPE_EXCEPTION 6
/** @brief Reset was caused in an unknown manner */
#define CFE_PSP_RST_SUBTYPE_UNDEFINED_RESET 7
/** @brief Reset was caused by a JTAG or BDM connection */
#define CFE_PSP_RST_SUBTYPE_HWDEBUG_RESET 8
/** @brief Reset reverted to a cFE POWERON due to a boot bank switch */
#define CFE_PSP_RST_SUBTYPE_BANKSWITCH_RESET 9
/** @brief Placeholder to indicate 1+ the maximum value that the PSP will ever use. */
#define CFE_PSP_RST_SUBTYPE_MAX 10
/** \} */

/**
 * @brief The name of the software/RTOS timebase for general system timers.
 *
 * This name may be referred to by CFE TIME and/or SCH when setting up its own timers.
 */
#define CFE_PSP_SOFT_TIMEBASE_NAME "cFS-Master"

/******************************************************************************
 FUNCTION PROTOTYPES
 ******************************************************************************/

/*
** PSP entry point and reset routines
*/
/*--------------------------------------------------------------------------------------*/
/**
 * @brief PSP Entry Point to initialize the OSAL and start up the cFE
 *
 * This is the entry point that the real-time OS calls to start our software.
 * This routine will do any BSP/OS-specific setup, then call the entry point of
 * the flight software (i.e. the cFE main entry point).
 *
 * @note The flight software (i.e. cFE) should not call this routine.
 */
extern void CFE_PSP_Main(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Sample/Read a monotonic platform clock with normalization
 *
 * Outputs an OS_time_t value indicating the time elapsed since an epoch. The
 * epoch is not defined, but typically represents the system boot time. The
 * value increases continuously over time and cannot be reset by software.
 *
 * This is similar to the CFE_PSP_Get_Timebase(), but additionally it normalizes
 * the output value to an OS_time_t, thereby providing consistent units to the
 * calling application. Any OSAL-provided routine that accepts OS_time_t inputs
 * may be used to convert this value into other standardized time units.
 *
 * @note This should refer to the same time domain as CFE_PSP_Get_Timebase(),
 * the primary difference being the format and units of the output value.
 *
 * @sa CFE_PSP_Get_Timebase()
 *
 * @param[out] LocalTime Value of PSP tick counter as OS_time_t
 */
extern void CFE_PSP_GetTime(OS_time_t *LocalTime);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Entry point back to the BSP to restart the processor.
 *
 * The flight software calls this routine to restart the processor.
 *
 * @param[in] resetType Type of reset
 */
extern void CFE_PSP_Restart(uint32 resetType);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Returns the last reset type
 *
 * @note If a pointer to a valid memory space is passed in, it returns the reset
 * sub-type in that memory. Right now the reset types are application-specific.
 * For the cFE they are defined in the cfe_es.h file.
 *
 * @param restartSubType
 */
extern uint32 CFE_PSP_GetRestartType(uint32 *restartSubType);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief This is a BSP-specific cache flush routine
 *
 * Provides a common interface to flush the processor caches. This routine is in
 * the BSP because it is sometimes implemented in hardware and sometimes taken
 * care of by the RTOS.
 *
 * @param[in] type
 * @param[in] address
 * @param[in] size
 */
extern void CFE_PSP_FlushCaches(uint32 type, void *address, uint32 size);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Returns the CPU ID as defined by the specific board and BSP.
 *
 * @return The processor ID
 */
extern uint32 CFE_PSP_GetProcessorId(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Returns the Spacecraft ID (if any)
 *
 * @return The Spacecraft ID
 */
extern uint32 CFE_PSP_GetSpacecraftId(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Returns the processor name
 *
 * @return The processor name
 */
extern const char *CFE_PSP_GetProcessorName(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Returns the underlying OS timer tick value
 *
 * It is used for the performance monitoring software
 */
extern uint32 CFE_PSP_Get_Timer_Tick(void);

/*--------------------------------------------------------------------------------------*/
/**
 * Provides the resolution of the least significant 32 bits of the 64-bit time
 * stamp returned by CFE_PSP_Get_Timebase in timer ticks per second. The timer
 * resolution for accuracy should not be any slower than 1000000 ticks per
 * second or 1 us (microsecond) per tick
 *
 * @return The number of timer ticks per second of the time stamp returned by
 * CFE_PSP_Get_Timebase
 */
extern uint32 CFE_PSP_GetTimerTicksPerSecond(void);

/*--------------------------------------------------------------------------------------*/
/**
 * Provides the number that the least significant 32 bits of the 64-bit time
 * stamp returned by CFE_PSP_Get_Timebase rolls over. If the lower 32 bits rolls
 * at 1 second, then the CFE_PSP_TIMER_LOW32_ROLLOVER will be 1000000. If the
 * lower 32 bits rolls at its maximum value (2^32) then
 * CFE_PSP_TIMER_LOW32_ROLLOVER will be 0.
 *
 * @return The number that the least significant 32 bits of the 64-bit time
 * stamp returned by CFE_PSP_Get_Timebase rolls over.
 */
extern uint32 CFE_PSP_GetTimerLow32Rollover(void);

/**
 * @brief Sample/Read a monotonic platform clock without normalization
 *
 * Provides a common interface to system timebase. This routine is in the BSP
 * because it is sometimes implemented in hardware and sometimes taken care of
 * by the RTOS.
 *
 * This is defined as a free-running, monotonically-increasing tick counter. The
 * epoch is not defined, but typically is the system boot time, and the value
 * increases indefinitely as the system runs. The tick period/rate is also not
 * defined.
 *
 * Rollover events - where the range of representable values is exceeded - are
 * theoretically possible, but would take many years of continuous uptime to
 * occur (typically hundreds of years, if not thousands). System designers
 * should ensure that the actual tick rate and resulting timebase range is
 * sufficiently large to ensure that rollover is not a concern.
 *
 * @note This is a "raw" value from the underlying platform with minimal/no
 * conversions or normalization applied. Neither the epoch nor the resolution of
 * this tick counter is specified, and it may vary from platform to platform.
 * Use the CFE_PSP_GetTime() function to sample the timebase and also convert
 * the units into a normalized/more consistent form.
 *
 * @sa CFE_PSP_GetTime()
 *
 * @param[out] Tbu Buffer to hold the upper 32 bits of a 64-bit tick counter
 * @param[out] Tbl Buffer to hold the lower 32 bits of a 64-bit tick counter
 */
extern void CFE_PSP_Get_Timebase(uint32 *Tbu, uint32 *Tbl);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief CFE_PSP_Get_Dec
 */
extern uint32 CFE_PSP_Get_Dec(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Fetches the size of the OS Critical Data Store area.
 *
 * @param[out] SizeOfCDS Pointer to the variable that will store the size of the CDS
 *
 * @return 0 (OS_SUCCESS or CFE_PSP_SUCCESS) on success, -1 (OS_ERROR or CFE_PSP_ERROR) on error
 */
extern int32 CFE_PSP_GetCDSSize(uint32 *SizeOfCDS);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Writes to the CDS Block.
 *
 * @param[in] PtrToDataToWrite Pointer to the data that will be written to the CDS
 * @param[in] CDSOffset        CDS offset
 * @param[in] NumBytes         Number of bytes to write
 *
 * @return 0 (OS_SUCCESS or CFE_PSP_SUCCESS) on success, -1 (OS_ERROR or CFE_PSP_ERROR) on error
 */
extern int32 CFE_PSP_WriteToCDS(const void *PtrToDataToWrite, uint32 CDSOffset, uint32 NumBytes);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Reads from the CDS Block
 *
 * @param[out] PtrToDataToRead Pointer to the location that will store the data to be read from the CDS
 * @param[in]  CDSOffset       CDS offset
 * @param[in]  NumBytes        Number of bytes to read
 *
 * @return 0 (OS_SUCCESS or CFE_PSP_SUCCESS) on success, -1 (OS_ERROR or CFE_PSP_ERROR) on error
 */
extern int32 CFE_PSP_ReadFromCDS(void *PtrToDataToRead, uint32 CDSOffset, uint32 NumBytes);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Returns the location and size of the ES Reset information area.
 *
 * This area is preserved during a processor reset and is used to store the ER
 * Log, System Log and reset-related variables
 *
 * @param[out] PtrToResetArea  Pointer to the variable that will store the location of the reset area
 * @param[out] SizeOfResetArea Pointer to the variable that will store the reset area size
 *
 * @return 0 (OS_SUCCESS or CFE_PSP_SUCCESS) on success, -1 (OS_ERROR or CFE_PSP_ERROR) on error
 */
extern int32 CFE_PSP_GetResetArea(cpuaddr *PtrToResetArea, uint32 *SizeOfResetArea);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Returns the location and size of the memory used for the cFE user-reserved area.
 *
 * @param[out] PtrToUserArea  Pointer to the variable that will store the location of the user-reserved area
 * @param[out] SizeOfUserArea Pointer to the variable that will store the size of the user-reserved area
 *
 * @return 0 (OS_SUCCESS or CFE_PSP_SUCCESS) on success, -1 (OS_ERROR or CFE_PSP_ERROR) on error
 */
extern int32 CFE_PSP_GetUserReservedArea(cpuaddr *PtrToUserArea, uint32 *SizeOfUserArea);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Returns the location and size of the memory used for the cFE volatile disk.
 *
 * @param[out] PtrToVolDisk  Pointer to the variable that will store the location of the cFE volatile disk
 * @param[out] SizeOfVolDisk Pointer to the variable that will store the size of the cFE volatile disk
 *
 * @return 0 (OS_SUCCESS or CFE_PSP_SUCCESS) on success, -1 (OS_ERROR or CFE_PSP_ERROR) on error
 */
extern int32 CFE_PSP_GetVolatileDiskMem(cpuaddr *PtrToVolDisk, uint32 *SizeOfVolDisk);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Returns the location and size of the kernel memory.
 *
 * This function returns the start and end address of the kernel text segment.
 * It may not be implemented on all architectures.
 *
 * @param[out] PtrToKernelSegment  Pointer to the variable that will store the location of the kernel text segment
 * @param[out] SizeOfKernelSegment Pointer to the variable that will store the size of the kernel text segment
 *
 * @return 0 (OS_SUCCESS or CFE_PSP_SUCCESS) on success, -1 (OS_ERROR or CFE_PSP_ERROR) on error
 * or CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
extern int32 CFE_PSP_GetKernelTextSegmentInfo(cpuaddr *PtrToKernelSegment, uint32 *SizeOfKernelSegment);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Returns the location and size of the kernel memory.
 *
 * This function returns the start and end address of the CFE text segment. It
 * may not be implemented on all architectures.
 *
 * @param[out] PtrToCFESegment  Pointer to the variable that will store the location of the cFE text segment
 * @param[out] SizeOfCFESegment Pointer to the variable that will store the size of the cFE text segment
 *
 * @return 0 (OS_SUCCESS or CFE_PSP_SUCCESS) on success, -1 (OS_ERROR or CFE_PSP_ERROR) on error
 */
extern int32 CFE_PSP_GetCFETextSegmentInfo(cpuaddr *PtrToCFESegment, uint32 *SizeOfCFESegment);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Configures the watchdog timer.
 *
 * To set up the timer resolution and/or other settings custom to this platform.
 */
extern void CFE_PSP_WatchdogInit(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Enables the watchdog timer.
 */
extern void CFE_PSP_WatchdogEnable(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Disables the watchdog timer.
 */
extern void CFE_PSP_WatchdogDisable(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Services the watchdog timer according to the value set in WatchDogSet.
 *
 * Load the watchdog timer with a count that corresponds to the millisecond
 * time given in the parameter.
 *
 * @note Currently an ExpireTime value of zero will result in the minimum reset
 * time of 4.5 seconds. All other ExpireTime values will result in a reset time
 * of 5.5 seconds.
 */
extern void CFE_PSP_WatchdogService(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Gets the watchdog time in milliseconds
 *
 * @return The current watchdog value
 */
extern uint32 CFE_PSP_WatchdogGet(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Sets the watchdog time in milliseconds
 *
 * @param[in] WatchdogValue New watchdog value to set
 */
extern void CFE_PSP_WatchdogSet(uint32 WatchdogValue);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Aborts the cFE startup
 *
 * Provides a common interface to abort the cFE startup process and return back
 * to the OS.
 *
 * @note This is called by the cFE Core startup code when it needs to abort the
 *       cFE startup. This should not be called by applications.
 *
 * @param[in] ErrorCode Reason for exiting
 */
extern void CFE_PSP_Panic(int32 ErrorCode);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Initializes the Solid State recorder memory for a particular platform
 *
 * @note For the MCP750, this simply initializes the Hard Disk device.
 *
 * @param[in] bus
 * @param[in] device
 * @param[in] DeviceName
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR on error
 */
extern int32 CFE_PSP_InitSSR(uint32 bus, uint32 device, char *DeviceName);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Uncompresses the source file to the file specified in the destination file name.
 *
 * @note The Decompress uses the "gzip" algorithm. Files can be compressed
 * using the "gzip" program available on almost all host platforms.
 *
 * @param srcFileName Source file to decompress
 * @param dstFileName Destination file name
 */
extern int32 CFE_PSP_Decompress(char *srcFileName, char *dstFileName);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Sets up the exception environment for the chosen platform
 *
 * On a board, this can be configured to look at a debug flag or switch in order
 * to keep the standard OS exception handlers, rather than restarting the system.
 */
extern void CFE_PSP_AttachExceptions(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Defines the CPU and FPU exceptions that are enabled for each cFE Task/App
 *
 * This function sets a default exception environment that can be used
 *
 * @note The exception environment is local to each task. Therefore, this must
 * be Called for each task that wants to do floating point and catch exceptions.
 */
extern void CFE_PSP_SetDefaultExceptionEnvironment(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Returns the unread exception count
 *
 * @return The unread exception count
 */
extern uint32 CFE_PSP_Exception_GetCount(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Retrieves a summary of an exception log entry
 *
 * @note This function returns CFE_PSP_SUCCESS to indicate that an entry was
 * popped from the queue. This doesn't necessarily mean that the output fields
 * have valid data, but it does mean they are initialized to something.
 *
 * @param[in]      ContextLogId ID of the exception log entry to get a summary for
 * @param[in, out] TaskId       Pointer to the TaskID buffer
 * @param[out]     ReasonBuf    Pointer to the buffer that will store the exception summary string
 * @param[in]      ReasonSize   Maximum size of the summary string to retrieve
 *
 * @retval CFE_PSP_SUCCESS on success (see note above)
 * @retval CFE_PSP_NO_EXCEPTION_DATA if no context available for reading
 */
extern int32 CFE_PSP_Exception_GetSummary(uint32 *ContextLogId, osal_id_t *TaskId, char *ReasonBuf, uint32 ReasonSize);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Retrieves exception log entry context information
 *
 * @param[in]  ContextLogId ID of the exception log entry to copy
 * @param[out] ContextBuf   Pointer to the buffer where the context information is to be copied to
 * @param[in]  ContextSize  Maximum size of context information data to copy
 *
 * @return Size of the copied data
 * @retval CFE_PSP_NO_EXCEPTION_DATA if data has expired from the memory log
 */
extern int32 CFE_PSP_Exception_CopyContext(uint32 ContextLogId, void *ContextBuf, uint32 ContextSize);

/*
** I/O Port API
*/
/*--------------------------------------------------------------------------------------*/
/**
 * @brief Read one byte of memory.
 *
 * @param[in]  PortAddress Address to be read
 * @param[out] ByteValue   The address content will be copied to the location pointed to by this argument
 *
 * @return Always returns CFE_PSP_SUCCESS (if implemented)
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_PortRead8(cpuaddr PortAddress, uint8 *ByteValue);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Write one byte of memory.
 *
 * @param[out] PortAddress Address to be written to
 * @param[in]  ByteValue   The content pointed to by this argument will be copied to the address
 *
 * @return Always returns CFE_PSP_SUCCESS (if implemented)
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_PortWrite8(cpuaddr PortAddress, uint8 ByteValue);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Read 2 bytes of memory.
 *
 * @param[in]  PortAddress Address to be read
 * @param[out] uint16Value The address content will be copied to the location pointed to by this argument
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_ADDRESS_MISALIGNED if the address is not aligned to a 16-bit addressing scheme.
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_PortRead16(cpuaddr PortAddress, uint16 *uint16Value);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Write 2 bytes of memory.
 *
 * @param[out] PortAddress Address to be written to
 * @param[in]  uint16Value the content pointed to by this argument will be copied to the address
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_ADDRESS_MISALIGNED if the address is not aligned to a 16-bit addressing scheme.
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_PortWrite16(cpuaddr PortAddress, uint16 uint16Value);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Read 4 bytes of memory.
 *
 * @param[in]  PortAddress Address to be read
 * @param[out] uint32Value The address content will be copied to the location pointed to by this argument
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_ADDRESS_MISALIGNED if the address is not aligned to a 16-bit addressing scheme.
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_PortRead32(cpuaddr PortAddress, uint32 *uint32Value);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Write 4 bytes of memory.
 *
 * @param[out] PortAddress Address to be written to
 * @param[in]  uint32Value The content pointed to by this argument will be copied to the address
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_ADDRESS_MISALIGNED if the address is not aligned to a 16-bit addressing scheme.
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_PortWrite32(cpuaddr PortAddress, uint32 uint32Value);

/*
** Memory API
*/
/*--------------------------------------------------------------------------------------*/
/**
 * @brief Read one byte of memory.
 *
 * @param[in]  MemoryAddress Address to be read
 * @param[out] ByteValue     The address content will be copied to the location pointed to by this argument
 *
 * @return Always returns CFE_PSP_SUCCESS (if implemented)
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_MemRead8(cpuaddr MemoryAddress, uint8 *ByteValue);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Write one byte of memory.
 *
 * @param[out] MemoryAddress Address to be written to
 * @param[in]  ByteValue     The content pointed to by this argument will be copied to the address
 *
 * @return Always returns CFE_PSP_SUCCESS (if implemented)
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_MemWrite8(cpuaddr MemoryAddress, uint8 ByteValue);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Read 2 bytes of memory.
 *
 * @param[in]  MemoryAddress Address to be read
 * @param[out] uint16Value   The address content will be copied to the location pointed to by this argument
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_ADDRESS_MISALIGNED if the address is not aligned to a 16-bit addressing scheme.
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_MemRead16(cpuaddr MemoryAddress, uint16 *uint16Value);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Write 2 bytes of memory.
 *
 * @param[out] MemoryAddress Address to be written to
 * @param[in]  uint16Value   The content pointed to by this argument will be copied to the address
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_ADDRESS_MISALIGNED if the address is not aligned to a 16-bit addressing scheme.
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_MemWrite16(cpuaddr MemoryAddress, uint16 uint16Value);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Read 4 bytes of memory.
 *
 * @param[in]  MemoryAddress Address to be read
 * @param[out] uint32Value   The address content will be copied to the location pointed to by this argument
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_ADDRESS_MISALIGNED if the address is not aligned to a 16-bit addressing scheme.
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_MemRead32(cpuaddr MemoryAddress, uint32 *uint32Value);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Write 4 bytes of memory.
 *
 * @param[out] MemoryAddress Address to be written to
 * @param[in]  uint32Value   The content pointed to by this argument will be copied to the address
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_ADDRESS_MISALIGNED if the address is not aligned to a 16-bit addressing scheme.
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_MemWrite32(cpuaddr MemoryAddress, uint32 uint32Value);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Copy 'n' bytes from 'src' to 'dest'
 *
 * Copies 'n' bytes from memory address pointed to by 'src' to memory
 * address pointed to by 'dest'.
 *
 * @note For now we are using the standard C library call 'memcpy' but if we
 * find we need to make it more efficient then we'll implement it in assembly.
 *
 * @param[out] dest Pointer to the destination address to copy to
 * @param[in]  src  Pointer to the address to copy from
 * @param[in]  n    Number of bytes to copy
 *
 * @return Always returns CFE_PSP_SUCCESS
 */
int32 CFE_PSP_MemCpy(void *dest, const void *src, uint32 n);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Copy 'n' bytes of value 'value' to 'dest'
 *
 * Copies 'n' number of bytes of value 'value' to memory address pointed
 * to by 'dest'.
 *
 * @note For now we are using the standard C library call 'memset' but if we
 * find we need to make it more efficient then we'll implement it in assembly.
 *
 * @param[out] dest  Pointer to the destination address to copy to
 * @param[in]  value Value to set
 * @param[in]  n     Number of bytes to copy
 *
 * @return Always returns CFE_PSP_SUCCESS
 */
int32 CFE_PSP_MemSet(void *dest, uint8 value, uint32 n);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Validates the memory range and type using the global CFE_PSP_MemoryTable
 *
 * @param[in] Address    A 32-bit starting address of the memory range
 * @param[in] Size       A 32-bit size of the memory range (Address + Size = End Address)
 * @param[in] MemoryType The memory type to validate, including but not limited to:
 *                       CFE_PSP_MEM_RAM, CFE_PSP_MEM_EEPROM, or CFE_PSP_MEM_ANY
 *                       Any defined CFE_PSP_MEM_* enumeration can be specified
 *
 * @retval CFE_PSP_SUCCESS           Memory range and type information is valid and can be used.
 * @retval CFE_PSP_INVALID_MEM_ADDR  Starting address is not valid
 * @retval CFE_PSP_INVALID_MEM_TYPE  Memory type associated with the range does not match the passed-in type.
 * @retval CFE_PSP_INVALID_MEM_RANGE The Memory range associated with the address is not large enough to contain
 *                                   Address + Size.
 */
int32 CFE_PSP_MemValidateRange(cpuaddr Address, size_t Size, uint32 MemoryType);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Returns the number of memory ranges in the CFE_PSP_MemoryTable
 *
 * @return Positive integer number of entries in the memory range table
 */
uint32 CFE_PSP_MemRanges(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Populates one of the records in the CFE_PSP_MemoryTable.
 *
 * @note Because the table is fixed size, the entries are set by using the
 * integer index. No validation is done with the address or size.
 *
 * @param[in] RangeNum   A 32-bit integer (starting with 0) specifying the MemoryTable entry.
 * @param[in] MemoryType The memory type to validate, including but not limited to:
 *                       CFE_PSP_MEM_RAM, CFE_PSP_MEM_EEPROM, or CFE_PSP_MEM_ANY
 *                       Any defined CFE_PSP_MEM_* enumeration can be specified
 * @param[in] StartAddr  A 32-bit starting address of the memory range
 * @param[in] Size       A 32-bit size of the memory range (Address + Size = End Address)
 * @param[in] WordSize   The minimum addressable size of the range:
 *                       (CFE_PSP_MEM_SIZE_BYTE, CFE_PSP_MEM_SIZE_WORD, CFE_PSP_MEM_SIZE_DWORD)
 * @param[in] Attributes The attributes of the Memory Range:
 *                       (CFE_PSP_MEM_ATTR_WRITE, CFE_PSP_MEM_ATTR_READ, CFE_PSP_MEM_ATTR_READWRITE)
 *
 * @retval CFE_PSP_SUCCESS              Memory range set successfully.
 * @retval CFE_PSP_INVALID_MEM_RANGE    The index into the table is invalid
 * @retval FE_PSP_INVALID_MEM_ADDR      Starting address is not valid
 * @retval CFE_PSP_INVALID_MEM_TYPE     Memory type associated with the range does not match the passed-in type.
 * @retval CFE_PSP_INVALID_MEM_WORDSIZE The WordSize parameter is not one of the predefined types.
 * @retval CFE_PSP_INVALID_MEM_ATTR     The Attributes parameter is not one of the predefined types.
 * @retval OP_INVALID_MEM_SIZE          The Memory range associated with the address is not large enough to contain
 *                                      Address + Size.
 */
int32 CFE_PSP_MemRangeSet(uint32 RangeNum, uint32 MemoryType, cpuaddr StartAddr, size_t Size, size_t WordSize,
                          uint32 Attributes);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Retrieves one of the records in the CFE_PSP_MemoryTable.
 *
 * @note Because the table is fixed size, the entries are accessed by using the integer index.
 *
 * @param[in]  RangeNum   A 32-bit integer (starting with 0) specifying the MemoryTable entry.
 * @param[out] MemoryType A pointer to the 32-bit integer where the Memory Type is stored.
 *                        Any defined CFE_PSP_MEM_* enumeration can be specified
 * @param[out] StartAddr  Pointer to the 32-bit integer where the 32-bit starting address of the memory range is stored.
 * @param[out] Size       A pointer to the 32-bit integer where the 32-bit size of the memory range is stored.
 * @param[out] WordSize   A pointer to the 32-bit integer where the minimum addressable size of the range:
 *                        (CFE_PSP_MEM_SIZE_BYTE, CFE_PSP_MEM_SIZE_WORD, CFE_PSP_MEM_SIZE_DWORD)
 * @param[out] Attributes The attributes of the Memory Range:
 *                        (CFE_PSP_MEM_ATTR_WRITE, CFE_PSP_MEM_ATTR_READ, CFE_PSP_MEM_ATTR_READWRITE)
 *
 * @retval CFE_PSP_SUCCESS           Memory range returned successfully.
 * @retval CFE_PSP_INVALID_POINTER   Parameter error
 * @retval CFE_PSP_INVALID_MEM_RANGE The index into the table is invalid
 */
int32 CFE_PSP_MemRangeGet(uint32 RangeNum, uint32 *MemoryType, cpuaddr *StartAddr, size_t *Size, size_t *WordSize,
                          uint32 *Attributes);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Write one byte (ByteValue) to EEPROM address MemoryAddress
 *
 * @param[out] MemoryAddress Memory address to write to
 * @param[in]  ByteValue     Value to write to memory
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_TIMEOUT write operation did not go through after a specific timeout.
 * @retval CFE_PSP_ERROR_ADDRESS_MISALIGNED if the address is not aligned to a 16-bit addressing scheme.
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_EepromWrite8(cpuaddr MemoryAddress, uint8 ByteValue);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Write two bytes (uint16Value) to EEPROM address MemoryAddress
 *
 * @param[out] MemoryAddress Memory address to write to
 * @param[in]  uint16Value   Value to write to memory
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_TIMEOUT write operation did not go through after a specific timeout.
 * @retval CFE_PSP_ERROR_ADDRESS_MISALIGNED if the address is not aligned to a 16-bit addressing scheme.
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_EepromWrite16(cpuaddr MemoryAddress, uint16 uint16Value);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Write four bytes (uint32Value) to EEPROM address MemoryAddress
 *
 * @param[out] MemoryAddress Memory address to write to
 * @param[in]  uint32Value   Value to write to memory
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_TIMEOUT write operation did not go through after a specific timeout.
 * @retval CFE_PSP_ERROR_ADDRESS_MISALIGNED if the address is not aligned to a 16-bit addressing scheme.
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_EepromWrite32(cpuaddr MemoryAddress, uint32 uint32Value);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Enable the EEPROM for write operation
 *
 * @param[in] Bank The bank of EEPROM to enable
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_EepromWriteEnable(uint32 Bank);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Disable the EEPROM from write operation
 *
 * @param[in] Bank The bank of EEPROM to disable
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_EepromWriteDisable(uint32 Bank);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Power up the EEPROM
 *
 * @param[in] Bank The bank of EEPROM to power up
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_EepromPowerUp(uint32 Bank);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Power down the EEPROM
 *
 * @param[in] Bank The bank of EEPROM to power down
 *
 * @retval CFE_PSP_SUCCESS on success
 * @retval CFE_PSP_ERROR_NOT_IMPLEMENTED if not implemented
 */
int32 CFE_PSP_EepromPowerDown(uint32 Bank);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Obtain the PSP version/baseline identifier string
 *
 * This retrieves the PSP version identifier string without extra info
 *
 * @return Version string. This is a fixed string and cannot be NULL.
 */
const char *CFE_PSP_GetVersionString(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Obtain the version code name
 *
 * This retrieves the PSP code name. This is a compatibility indicator for the
 * overall NASA cFS ecosystem. All modular components which are intended to
 * interoperate should report the same code name.
 *
 * @return Code name. This is a fixed string and cannot be NULL.
 */
const char *CFE_PSP_GetVersionCodeName(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Retrieves the numeric PSP version identifier as an array of uint8 values
 *
 * The array of numeric values is in order of precedence:
 *  [0] = Major Number
 *  [1] = Minor Number
 *  [2] = Revision Number
 *  [3] = Mission Revision
 *
 * The "Mission Revision" (last output) also indicates whether this is an
 * official release, a patched release, or a development version.
 *  0 indicates an official release
 *  1-254 local patch level (reserved for mission use)
 *  255 indicates a development build
 *
 * @param[out] VersionNumbers A fixed-size array to be filled with the version numbers
 */
void CFE_PSP_GetVersionNumber(uint8 VersionNumbers[4]);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Obtain the PSP library numeric build number
 *
 * The build number is a monotonically increasing number that (coarsely)
 * reflects the number of commits/changes that have been merged since the epoch
 * release. During development cycles this number should increase after each
 * subsequent merge/modification.
 *
 * Like other version information, this is a fixed number assigned at compile
 * time.
 *
 * @return The OSAL library build number
 */
uint32 CFE_PSP_GetBuildNumber(void);

#endif
