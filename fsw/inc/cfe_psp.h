/*
**  GSC-18128-1, "Core Flight Executive Version 6.7"
**
**  Copyright (c) 2006-2019 United States Government as represented by
**  the Administrator of the National Aeronautics and Space Administration.
**  All Rights Reserved.
**
**  Licensed under the Apache License, Version 2.0 (the "License");
**  you may not use this file except in compliance with the License.
**  You may obtain a copy of the License at
**
**    http://www.apache.org/licenses/LICENSE-2.0
**
**  Unless required by applicable law or agreed to in writing, software
**  distributed under the License is distributed on an "AS IS" BASIS,
**  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**  See the License for the specific language governing permissions and
**  limitations under the License.
*/

/*
**  File Name:  cfe_psp.h
**
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

#ifndef _cfe_psp_
#define _cfe_psp_

/*
** Include Files
*/

#include "common_types.h"
#include "osapi.h"

/*
** Macro Definitions
*/

/*
** Error and return codes
*/
#define CFE_PSP_SUCCESS                  (0)
#define CFE_PSP_ERROR                    (-1)
#define CFE_PSP_INVALID_POINTER          (-2)
#define CFE_PSP_ERROR_ADDRESS_MISALIGNED (-3)
#define CFE_PSP_ERROR_TIMEOUT            (-4)
#define CFE_PSP_INVALID_INT_NUM          (-5)
#define CFE_PSP_INVALID_MEM_ADDR         (-21)
#define CFE_PSP_INVALID_MEM_TYPE         (-22)
#define CFE_PSP_INVALID_MEM_RANGE        (-23)
#define CFE_PSP_INVALID_MEM_WORDSIZE     (-24)
#define CFE_PSP_INVALID_MEM_SIZE         (-25)
#define CFE_PSP_INVALID_MEM_ATTR         (-26)
#define CFE_PSP_ERROR_NOT_IMPLEMENTED    (-27)
#define CFE_PSP_INVALID_MODULE_NAME      (-28)
#define CFE_PSP_INVALID_MODULE_ID        (-29)
#define CFE_PSP_NO_EXCEPTION_DATA        (-30)

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
/** \name Reset Types */
/** \{ */
#define CFE_PSP_RST_TYPE_PROCESSOR 1 /**< Volatile disk, CDS and User Reserved memory may be valid */
#define CFE_PSP_RST_TYPE_POWERON   2 /**< All memory has been cleared */
#define CFE_PSP_RST_TYPE_MAX       3 /**< Placeholder to indicate 1+ the maximum value that the PSP will ever use. */
/** \} */

/*
** Reset Sub-Types
*/
/** \name Reset Sub-Types */
/** \{ */

/** \brief Reset caused by power having been removed and restored */
#define CFE_PSP_RST_SUBTYPE_POWER_CYCLE 1
/** \brief Reset caused by reset button on the board */
#define CFE_PSP_RST_SUBTYPE_PUSH_BUTTON 2
/** \brief Reset was caused by a reset line having been stimulated by a hardware special command */
#define CFE_PSP_RST_SUBTYPE_HW_SPECIAL_COMMAND 3
/** \brief Reset was caused by a watchdog timer expiring */
#define CFE_PSP_RST_SUBTYPE_HW_WATCHDOG 4
/** \brief Reset was caused by cFE ES processing a \link #CFE_ES_RESTART_CC Reset Command \endlink */
#define CFE_PSP_RST_SUBTYPE_RESET_COMMAND 5
/** \brief Reset was caused by a Processor Exception */
#define CFE_PSP_RST_SUBTYPE_EXCEPTION 6
/** \brief Reset was caused in an unknown manner */
#define CFE_PSP_RST_SUBTYPE_UNDEFINED_RESET 7
/** \brief Reset was caused by a JTAG or BDM connection */
#define CFE_PSP_RST_SUBTYPE_HWDEBUG_RESET 8
/** \brief Reset reverted to a cFE POWERON due to a boot bank switch */
#define CFE_PSP_RST_SUBTYPE_BANKSWITCH_RESET 9
/** \brief Placeholder to indicate 1+ the maximum value that the PSP will ever use. */
#define CFE_PSP_RST_SUBTYPE_MAX 10
/** \} */

/**
 * \brief The name of the software/RTOS timebase for general system timers.
 *
 * This name may be referred to by CFE TIME and/or SCH when setting up its own timers.
 */
#define CFE_PSP_SOFT_TIMEBASE_NAME "cFS-Master"

/*
** Type Definitions
*/

/*
** Function prototypes
*/

/*
** PSP entry point and reset routines
*/
extern void CFE_PSP_Main(void);

/*
** CFE_PSP_Main is the entry point that the real time OS calls to start our
** software. This routine will do any BSP/OS specific setup, then call the
** entrypoint of the flight software ( i.e. the cFE main entry point ).
** The flight software (i.e. cFE ) should not call this routine.
*/

/**
 * \brief Sample/Read a monotonic platform clock with normalization
 *
 * Outputs an OS_time_t value indicating the time elapsed since an epoch.  The
 * epoch is not defined, but typically represents the system boot time.  The
 * value increases continuously over time and cannot be reset by software.
 *
 * This is similar to the CFE_PSP_Get_Timebase(), but additionally it normalizes
 * the output value to an OS_time_t, thereby providing consistent units to
 * the calling application.  Any OSAL-provided routine accepts OS_time_t inputs
 * may be used to convert this value into other standardized time units.
 *
 * \note This should refer to the same time domain as CFE_PSP_Get_Timebase(),
 * the primary difference being the format and units of the output value.
 *
 * \sa CFE_PSP_Get_Timebase()
 *
 * \param[out] LocalTime Value of PSP tick counter as OS_time_t
 */
extern void CFE_PSP_GetTime(OS_time_t *LocalTime);

extern void CFE_PSP_Restart(uint32 resetType);
/*
** CFE_PSP_Restart is the entry point back to the BSP to restart the processor.
** The flight software calls this routine to restart the processor.
*/

extern uint32 CFE_PSP_GetRestartType(uint32 *restartSubType);
/*
** CFE_PSP_GetRestartType returns the last reset type and if a pointer to a valid
** memory space is passed in, it returns the reset sub-type in that memory.
** Right now the reset types are application specific. For the cFE they
** are defined in the cfe_es.h file.
*/

extern void CFE_PSP_FlushCaches(uint32 type, void *address, uint32 size);
/*
** This is a BSP specific cache flush routine
*/

extern uint32 CFE_PSP_GetProcessorId(void);
/*
** CFE_PSP_GetProcessorId returns the CPU ID as defined by the specific board
** and BSP.
*/

extern uint32 CFE_PSP_GetSpacecraftId(void);
/*
** CFE_PSP_GetSpacecraftId returns the Spacecraft ID (if any )
*/

extern const char *CFE_PSP_GetProcessorName(void);
/*
** CFE_PSP_GetProcessorName returns the processor name
*/

extern uint32 CFE_PSP_Get_Timer_Tick(void);
/*
** CFE_PSP_Get_Timer_Tick returns the underlying OS timer tick value
** It is used for the performance monitoring software
*/

extern uint32 CFE_PSP_GetTimerTicksPerSecond(void);
/*
** CFE_PSP_GetTimerTicksPerSecond provides the resolution of the least significant
** 32 bits of the 64 bit time stamp returned by CFE_PSP_Get_Timebase in timer
** ticks per second.  The timer resolution for accuracy should not be any slower
** than 1000000 ticks per second or 1 us per tick
*/

extern uint32 CFE_PSP_GetTimerLow32Rollover(void);
/*
** CFE_PSP_GetTimerLow32Rollover provides the number that the least significant
** 32 bits of the 64 bit time stamp returned by CFE_PSP_Get_Timebase rolls over.
** If the lower 32 bits rolls at 1 second, then the CFE_PSP_TIMER_LOW32_ROLLOVER
** will be 1000000.  if the lower 32 bits rolls at its maximum value (2^32) then
** CFE_PSP_TIMER_LOW32_ROLLOVER will be 0.
*/

/**
 * \brief Sample/Read a monotonic platform clock without normalization
 *
 * This is defined as a free-running, monotonically-increasing tick counter.  The
 * epoch is not defined, but typically is the system boot time, and the value increases
 * indefinitely as the system runs.  The tick period/rate is also not defined.
 *
 * Rollover events - where the range of representable values is exceeded - are
 * theoretically possible, but would take many years of continuous uptime to occur
 * (typically hundreds of years, if not thousands). System designers should ensure
 * that the actual tick rate and resulting timebase range is sufficiently large to
 * ensure that rollover is not a concern.
 *
 * \note This is a "raw" value from the underlying platform with minimal/no conversions
 * or normalization applied.  Neither the epoch nor the resolution of this tick
 * counter is specified, and it may vary from platform to platform.  Use the
 * CFE_PSP_GetTime() function to sample the timebase and also convert the units
 * into a normalized/more consistent form.
 *
 * \sa CFE_PSP_GetTime()
 *
 * \param[out] Tbu Buffer to hold the upper 32 bits of a 64-bit tick counter
 * \param[out] Tbl Buffer to hold the lower 32 bits of a 64-bit tick counter
 */
extern void CFE_PSP_Get_Timebase(uint32 *Tbu, uint32 *Tbl);

extern uint32 CFE_PSP_Get_Dec(void);
/*
** CFE_PSP_Get_Dec
*/

extern int32 CFE_PSP_GetCDSSize(uint32 *SizeOfCDS);
/*
** CFE_PSP_GetCDSSize fetches the size of the OS Critical Data Store area.
*/

extern int32 CFE_PSP_WriteToCDS(const void *PtrToDataToWrite, uint32 CDSOffset, uint32 NumBytes);
/*
** CFE_PSP_WriteToCDS writes to the CDS Block.
*/

extern int32 CFE_PSP_ReadFromCDS(void *PtrToDataToRead, uint32 CDSOffset, uint32 NumBytes);
/*
** CFE_PSP_ReadFromCDS reads from the CDS Block
*/

extern int32 CFE_PSP_GetResetArea(cpuaddr *PtrToResetArea, uint32 *SizeOfResetArea);
/*
** CFE_PSP_GetResetArea returns the location and size of the ES Reset information area.
** This area is preserved during a processor reset and is used to store the
** ER Log, System Log and reset related variables
*/

extern int32 CFE_PSP_GetUserReservedArea(cpuaddr *PtrToUserArea, uint32 *SizeOfUserArea);
/*
** CFE_PSP_GetUserReservedArea returns the location and size of the memory used for the cFE
** User reserved area.
*/

extern int32 CFE_PSP_GetVolatileDiskMem(cpuaddr *PtrToVolDisk, uint32 *SizeOfVolDisk);
/*
** CFE_PSP_GetVolatileDiskMem returns the location and size of the memory used for the cFE
** volatile disk.
*/

extern int32 CFE_PSP_GetKernelTextSegmentInfo(cpuaddr *PtrToKernelSegment, uint32 *SizeOfKernelSegment);
/*
** CFE_PSP_GetKernelTextSegmentInfo returns the location and size of the kernel memory.
*/

extern int32 CFE_PSP_GetCFETextSegmentInfo(cpuaddr *PtrToCFESegment, uint32 *SizeOfCFESegment);
/*
** CFE_PSP_GetCFETextSegmentInfo returns the location and size of the kernel memory.
*/

extern void CFE_PSP_WatchdogInit(void);
/*
** CFE_PSP_WatchdogInit configures the watchdog timer.
*/

extern void CFE_PSP_WatchdogEnable(void);
/*
** CFE_PSP_WatchdogEnable enables the watchdog timer.
*/

extern void CFE_PSP_WatchdogDisable(void);
/*
** CFE_PSP_WatchdogDisable disables the watchdog timer.
*/

extern void CFE_PSP_WatchdogService(void);
/*
** CFE_PSP_WatchdogService services the watchdog timer according to the
** value set in WatchDogSet.
*/

extern uint32 CFE_PSP_WatchdogGet(void);
/*
** CFE_PSP_WatchdogGet gets the watchdog time in milliseconds
*/

extern void CFE_PSP_WatchdogSet(uint32 WatchdogValue);
/*
** CFE_PSP_WatchdogSet sets the watchdog time in milliseconds
*/

extern void CFE_PSP_Panic(int32 ErrorCode);
/*
** CFE_PSP_Panic is called by the cFE Core startup code when it needs to abort the
** cFE startup. This should not be called by applications.
*/

extern int32 CFE_PSP_InitSSR(uint32 bus, uint32 device, char *DeviceName);
/*
** CFE_PSP_InitSSR will initialize the Solid state recorder memory for a particular platform
*/

extern int32 CFE_PSP_Decompress(char *srcFileName, char *dstFileName);
/*
** CFE_PSP_Decompress will uncompress the source file to the file specified in the
** destination file name. The Decompress uses the "gzip" algorithm. Files can
** be compressed using the "gzip" program available on almost all host platforms.
*/

extern void CFE_PSP_AttachExceptions(void);
/*
** CFE_PSP_AttachExceptions will setup the exception environment for the chosen platform
** On a board, this can be configured to look at a debug flag or switch in order to
** keep the standard OS exeption handlers, rather than restarting the system
*/

extern void CFE_PSP_SetDefaultExceptionEnvironment(void);
/*
**
**   CFE_PSP_SetDefaultExceptionEnvironment defines the CPU and FPU exceptions that are enabled for each cFE Task/App
**
**   Notes: The exception environment is local to each task Therefore this must be
**          called for each task that that wants to do floating point and catch exceptions
*/

extern uint32 CFE_PSP_Exception_GetCount(void);
extern int32  CFE_PSP_Exception_GetSummary(uint32 *ContextLogId, osal_id_t *TaskId, char *ReasonBuf, uint32 ReasonSize);
extern int32  CFE_PSP_Exception_CopyContext(uint32 ContextLogId, void *ContextBuf, uint32 ContextSize);

/*
** I/O Port API
*/
int32 CFE_PSP_PortRead8(cpuaddr PortAddress, uint8 *ByteValue);
int32 CFE_PSP_PortWrite8(cpuaddr PortAddress, uint8 ByteValue);
int32 CFE_PSP_PortRead16(cpuaddr PortAddress, uint16 *uint16Value);
int32 CFE_PSP_PortWrite16(cpuaddr PortAddress, uint16 uint16Value);
int32 CFE_PSP_PortRead32(cpuaddr PortAddress, uint32 *uint32Value);
int32 CFE_PSP_PortWrite32(cpuaddr PortAddress, uint32 uint32Value);

/*
** Memory API
*/
int32 CFE_PSP_MemRead8(cpuaddr MemoryAddress, uint8 *ByteValue);
int32 CFE_PSP_MemWrite8(cpuaddr MemoryAddress, uint8 ByteValue);
int32 CFE_PSP_MemRead16(cpuaddr MemoryAddress, uint16 *uint16Value);
int32 CFE_PSP_MemWrite16(cpuaddr MemoryAddress, uint16 uint16Value);
int32 CFE_PSP_MemRead32(cpuaddr MemoryAddress, uint32 *uint32Value);
int32 CFE_PSP_MemWrite32(cpuaddr MemoryAddress, uint32 uint32Value);

int32 CFE_PSP_MemCpy(void *dest, const void *src, uint32 n);
int32 CFE_PSP_MemSet(void *dest, uint8 value, uint32 n);

int32  CFE_PSP_MemValidateRange(cpuaddr Address, size_t Size, uint32 MemoryType);
uint32 CFE_PSP_MemRanges(void);
int32  CFE_PSP_MemRangeSet(uint32 RangeNum, uint32 MemoryType, cpuaddr StartAddr, size_t Size, size_t WordSize,
                           uint32 Attributes);
int32  CFE_PSP_MemRangeGet(uint32 RangeNum, uint32 *MemoryType, cpuaddr *StartAddr, size_t *Size, size_t *WordSize,
                           uint32 *Attributes);

int32 CFE_PSP_EepromWrite8(cpuaddr MemoryAddress, uint8 ByteValue);
int32 CFE_PSP_EepromWrite16(cpuaddr MemoryAddress, uint16 uint16Value);
int32 CFE_PSP_EepromWrite32(cpuaddr MemoryAddress, uint32 uint32Value);

int32 CFE_PSP_EepromWriteEnable(uint32 Bank);
int32 CFE_PSP_EepromWriteDisable(uint32 Bank);
int32 CFE_PSP_EepromPowerUp(uint32 Bank);
int32 CFE_PSP_EepromPowerDown(uint32 Bank);

/**
 * \brief Obtain the PSP version/baseline identifier string
 *
 * This retrieves the PSP version identifier string without extra info
 *
 * \returns Version string.  This is a fixed string and cannot be NULL.
 */
const char *CFE_PSP_GetVersionString(void);

/**
 * \brief Obtain the version code name
 *
 * This retrieves the PSP code name.  This is a compatibility indicator for the
 * overall NASA CFS ecosystem.  All modular components which are intended to
 * interoperate should report the same code name.
 *
 * \returns Code name.  This is a fixed string and cannot be NULL.
 */
const char *CFE_PSP_GetVersionCodeName(void);

/**
 * \brief Obtain the PSP numeric version numbers as uint8 values
 *
 * This retrieves the numeric PSP version identifier as an array of 4 uint8 values.
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
 * \param[out] VersionNumbers  A fixed-size array to be filled with the version numbers
 */
void CFE_PSP_GetVersionNumber(uint8 VersionNumbers[4]);

/**
 * \brief Obtain the PSP library numeric build number
 *
 * The build number is a monotonically increasing number that (coarsely)
 * reflects the number of commits/changes that have been merged since the
 * epoch release.  During development cycles this number should increase
 * after each subsequent merge/modification.
 *
 * Like other version information, this is a fixed number assigned at compile time.
 *
 * \returns The OSAL library build number
 */
uint32 CFE_PSP_GetBuildNumber(void);

#endif /* _cfe_psp_ */
