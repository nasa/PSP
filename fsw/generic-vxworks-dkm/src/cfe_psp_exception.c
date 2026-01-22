/************************************************************************
 * NASA Docket No. GSC-19,200-1, and identified as "cFS Draco"
 *
 * Copyright (c) 2023 United States Government as represented by the
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

/******************************************************************************
**
** File:  cfe_psp_exception.c
**
**      generic-vxworks (7.x) Version
**
** Purpose:
**   cFE PSP Exception related functions.
**
** History:
**   2007/05/29  A. Cudmore      | vxWorks 6.2 MCP750 version
**   2016/04/07  M.Grubb         | Updated for PSP version 1.3
**
******************************************************************************/

/*
**  Include Files
*/
#include <stdio.h>
#include <string.h>
#include <vxWorks.h>
#include <sysLib.h>
#include "fppLib.h"
#include "excLib.h"
#include "taskLib.h"

/*
** cFE includes
*/
#include "common_types.h"
#include "osapi.h"

#include "cfe_psp.h"
#include "cfe_psp_config.h"
#include "cfe_psp_exceptionstorage_types.h"
#include "cfe_psp_exceptionstorage_api.h"
#include "cfe_psp_memory.h"

#include "target_config.h"

/*
**
** LOCAL FUNCTION PROTOTYPES
**
*/

void CFE_PSP_ExceptionHook(TASK_ID task_id, int vector, void *vpEsf);

/***************************************************************************
 **                        FUNCTIONS DEFINITIONS
 ***************************************************************************/

/*
**
**   Purpose: This function Initializes the task exceptions and adds a hook
**              into the VxWorks exception handling.  The below hook is called
**              for every exception that VxWorks catches.
**
**   Notes: if desired - to attach a custom handler put following code in
**          this function:  excConnect ((VOIDFUNCPTR*)VECTOR, ExceptionHandler);
**
*/

void CFE_PSP_AttachExceptions(void)
{
    excHookAdd(CFE_PSP_ExceptionHook);
    OS_printf("CFE_PSP: Attached cFE Exception Handler. Context Size = %lu bytes.\n",
              (unsigned long)sizeof(CFE_PSP_Exception_ContextDataEntry_t));
    CFE_PSP_Exception_Reset();
}

/*
**
** Purpose: Make the proper call to CFE_ES_EXCEPTION_FUNCTION (defined in
**          cfe_es_platform.cfg)
**
** Notes:   pEsf - pointer to exception stack frame.
**          fppSave - When it makes this call, it captures the last floating
**                      point context - which may not be valid.  If a floating
**                      point exception occurs you can be almost 100% sure
**                      that this will reflect the proper context.  But if another
**                      type of exception occurred then this has the possibility
**                      of not being valid.  Specifically if a task that is not
**                      enabled for floating point causes a non-floating point
**                      exception, then the meaning of the floating point context
**                      will not be valid.  If the task is enabled for floating point,
**                      then it will be valid.
**
*/
void CFE_PSP_ExceptionHook(TASK_ID task_id, int vector, void *vpEsf)
{
    CFE_PSP_Exception_LogData_t *Buffer;

    Buffer = CFE_PSP_Exception_GetNextContextBuffer();
    if (Buffer != NULL)
    {
       /*
        * Immediately get the time when exception occurred
        *
        * This is because the remainder of exception processing might be done
        * in a cleanup job as a low priority background task, and might be
        * considerably delayed from the time the actual exception occurred.
        */
        OS_GetLocalTime(&Buffer->context_info.time_stamp);

        Buffer->sys_task_id         = task_id;
        Buffer->context_info.vector = vector;

        /*
         * Save Exception Stack frame
         */
        /* memcpy(&Buffer->context_info.esf, vpEsf, sizeof(Buffer->context_info.esf)); */

        /*
         * Save floating point registers
         */
        fppSave(&Buffer->context_info.fp);

        /*
         * Save total size of context info.
         * (This PSP always fills the entire structure)
         */
        Buffer->context_size = sizeof(Buffer->context_info);

        CFE_PSP_Exception_WriteComplete();
    }

    if (GLOBAL_CFE_CONFIGDATA.SystemNotify != NULL)
    {
        /* notify the CFE of the event */
        GLOBAL_CFE_CONFIGDATA.SystemNotify();
    }
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
void CFE_PSP_SetDefaultExceptionEnvironment(void)
{
   return;    
}

/*
 * Purpose: Translate a stored exception log entry into a summary string
 */
int32 CFE_PSP_ExceptionGetSummary_Impl(const CFE_PSP_Exception_LogData_t *Buffer, char *ReasonBuf, uint32 ReasonSize)
{
    const char *TaskName;

    /*
    ** Get the vxWorks task name
    */
    TaskName = taskName(Buffer->sys_task_id);

    if (TaskName == NULL)
    {
        TaskName = "NULL";
    }

    snprintf(ReasonBuf, ReasonSize, "Vector=0x%06X, vxWorks Task Name=%s, Task ID=0x%08X", Buffer->context_info.vector,
             TaskName, Buffer->sys_task_id);

    return CFE_PSP_SUCCESS;
}
