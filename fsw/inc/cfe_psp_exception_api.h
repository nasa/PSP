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

#ifndef CFE_PSP_EXCEPTION_API_H
#define CFE_PSP_EXCEPTION_API_H

/******************************************************************************
 INCLUDE FILES
 ******************************************************************************/

#include "common_types.h"
#include "osapi.h"

#include "cfe_psp_error.h"

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Sets up the exception environment for the chosen platform
 *
 * On a board, this can be configured to look at a debug flag or switch in order
 * to keep the standard OS exception handlers, rather than restarting the system.
 */
void CFE_PSP_AttachExceptions(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Defines the CPU and FPU exceptions that are enabled for each cFE Task/App
 *
 * This function sets a default exception environment that can be used
 *
 * @note The exception environment is local to each task. Therefore, this must
 * be Called for each task that wants to do floating point and catch exceptions.
 */
void CFE_PSP_SetDefaultExceptionEnvironment(void);

/*--------------------------------------------------------------------------------------*/
/**
 * @brief Returns the unread exception count
 *
 * @return The unread exception count
 */
uint32 CFE_PSP_Exception_GetCount(void);

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
int32 CFE_PSP_Exception_GetSummary(uint32 *ContextLogId, osal_id_t *TaskId, char *ReasonBuf, uint32 ReasonSize);

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
int32 CFE_PSP_Exception_CopyContext(uint32 ContextLogId, void *ContextBuf, uint32 ContextSize);

#endif
