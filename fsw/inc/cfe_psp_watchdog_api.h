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

#ifndef CFE_PSP_WATCHDOG_API_H
#define CFE_PSP_WATCHDOG_API_H

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

/** @name Definitions for PSP PANIC types */
/** \{ */
#define CFE_PSP_PANIC_STARTUP         1
#define CFE_PSP_PANIC_VOLATILE_DISK   2
#define CFE_PSP_PANIC_MEMORY_ALLOC    3
#define CFE_PSP_PANIC_NONVOL_DISK     4
#define CFE_PSP_PANIC_STARTUP_SEM     5
#define CFE_PSP_PANIC_CORE_APP        6
#define CFE_PSP_PANIC_GENERAL_FAILURE 7
/** \} */

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

/******************************************************************************
 FUNCTION PROTOTYPES
 ******************************************************************************/

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Entry point back to the BSP to restart the processor.
 *
 * The flight software calls this routine to restart the processor.
 *
 * @param[in] resetType Type of reset
 */
void CFE_PSP_Restart(uint32 resetType);

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
uint32 CFE_PSP_GetRestartType(uint32 *restartSubType);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Configures the watchdog timer.
 *
 * To set up the timer resolution and/or other settings custom to this platform.
 */
void CFE_PSP_WatchdogInit(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Enables the watchdog timer.
 */
void CFE_PSP_WatchdogEnable(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Disables the watchdog timer.
 */
void CFE_PSP_WatchdogDisable(void);

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
void CFE_PSP_WatchdogService(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Gets the watchdog time in milliseconds
 *
 * @return The current watchdog value
 */
uint32 CFE_PSP_WatchdogGet(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Sets the watchdog time in milliseconds
 *
 * @param[in] WatchdogValue New watchdog value to set
 */
void CFE_PSP_WatchdogSet(uint32 WatchdogValue);

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
void CFE_PSP_Panic(int32 ErrorCode);

#endif
