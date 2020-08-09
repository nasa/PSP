/******************************************************************************
**
** File:  cfe_psp_exception.c
**
**      Copyright (c) 2004-2011, United States Government as represented by
**      Administrator for The National Aeronautics and Space Administration.
**      All Rights Reserved.
**
**      This is governed by the NASA Open Source Agreement and may be used,
**      distributed and modified only pursuant to the terms of that agreement.
**
** Purpose:
**   cFE PSP Exception related functions.
**
**   In original version of this code, the following loading error was noted:
**
**     > ld < cfe-core.o
**     Warning: module 0x22e1010 holds reference to undefined symbol fppRestore.
**     Warning: module 0x22e1010 holds reference to undefined symbol fppSave.
**
**   The following was found in the VxWorks 6.9 architecture supplement, pg 179,
**   for PPC85xx:
**
**     Do not confuse the hardware floating-point provided by the FPU with that
**     provided by the SPE (see 6.3.10 Signal Processing Engine Support, p.190).
**     If using the e500v2diab or e500v2gnu toolchains, you must use the speSave()
**     speSave() and speRestore() routines to save and restore floating-point
**     context.
**
**     The e500 core's SPE is a hardware double precision unit capable of both
**     scalar and vector(SIMD) computation.
**
******************************************************************************/

/*
**  Include Files
*/
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <vxWorks.h>
#include <sysLib.h>
#include <fppLib.h>
#include "excLib.h"
#include "taskLib.h"
#include "speLib.h"
#include "arch/ppc/vxPpcLib.h"
#include "arch/ppc/esfPpc.h"
#include <private/edrLibP.h>
#include "cfe_psp_exceptionstorage_api.h"

/*
** cFE includes
*/
#include "common_types.h"
#include "osapi.h"

#include "cfe_psp.h"
#include "cfe_psp_config.h"
#include "cfe_psp_memory.h"
#include <target_config.h>


/*
** cFE includes
*/

/*
** BSP Specific defines
*/

/*
**  External Declarations
*/
STATUS edrErrorPolicyHookRemove(void);

/*
** Global variables
*/
#include <target_config.h>

BOOL overRideDefaultedrPolicyHandlerHook = FALSE;

/* The EDR_POLICY_HANDLER_HOOK is a function pointer defined
 * in the header file edrLibP.h.
 */
LOCAL EDR_POLICY_HANDLER_HOOK currentedrPolicyHandlerHook = NULL;


/*
** Local Function Prototypes
*/


/******************************************************************************
**  Function: CFE_PSP_edrPolicyHandlerHook
**
**  Purpose:
**    Makes the proper call to CFE_ES_ProcessCoreException
**
**    Notes: When speSave() is called, it captures the last floating point
**           context, which may not be valid. If a floating point exception
**           occurs you can be almost 100% sure that this will reflect the
**           proper context. But if another type of exception occurred then
**           this has the possibility of not being valid. Specifically if a
**           task that is not enabled for floating point causes a non-floating
**           point exception, then the meaning of the floating point context
**           will not be valid.  If the task is enabled for floating point,
**           then it will be valid.
**
**  Arguments:
**    Input - type -
**            EDR_FACILITY_KERNEL 	- VxWorks kernel events
              EDR_FACILITY_INTERRUPT 	- interrupt handler events
              EDR_FACILITY_INIT 	- system startup events
              EDR_FACILITY_BOOT 	- system boot events
              EDR_FACILITY_REBOOT 	- system restart events
              EDR_FACILITY_RTP 	- RTP system events
              EDR_FACILITY_USER 	- user generated events
**    Input - pInfo_param -
**            A pointer to an architecture-specific EXC_INFO structure,
**            in case of exceptions, with CPU exception information. The exception
**            information is saved by the default VxWorks exception handler.
**            The structure is defined for each architecture in one of these
**            files:  target/h/arch/arch/excArchLib.h For example:  target/h/arch/ppc/excPpcLib.h
**    Input - debug -
**            This flag indicates whether the ED&R system is in debug (also known as lab) mode,
**            or in field (or deployed) mode.
**
**
**  Return:
**        TRUE  - Do not stop offending task
**        FALSE - Stop offending task
**
******************************************************************************/
BOOL CFE_PSP_edrPolicyHandlerHook(int type, void *pInfo_param, BOOL debug)
{
    CFE_PSP_Exception_LogData_t* Buffer;
    BOOL returnStatus = FALSE;
    EDR_TASK_INFO* pInfo = (EDR_TASK_INFO*)pInfo_param;

    Buffer = CFE_PSP_Exception_GetNextContextBuffer();
    if (Buffer != NULL)
    {
        /*
         * Immediately get a snapshot of the timebase when exception occurred
         *
         * This is because the remainder of exception processing might be done
         * in a cleanup job as a low priority background task, and might be
         * considerably delayed from the time the actual exception occurred.
         */
        vxTimeBaseGet(&Buffer->context_info.timebase_upper, &Buffer->context_info.timebase_lower);

        Buffer->sys_task_id = pInfo->taskId;
        Buffer->context_info.vector = pInfo->vector;

        /*
         * Save Exception Stack frame
         */
        memcpy(&Buffer->context_info.esf, pInfo->pEsf, sizeof(Buffer->context_info.esf));
        /*
        ** Save floating point registers
        */
        fppSave(&Buffer->context_info.fp);

        CFE_PSP_Exception_WriteComplete();

        if (overRideDefaultedrPolicyHandlerHook == FALSE)
        {
            if (currentedrPolicyHandlerHook != NULL)
            {
                returnStatus = currentedrPolicyHandlerHook(type, pInfo, debug);
            }
        }
    }
    if (GLOBAL_CFE_CONFIGDATA.SystemNotify != NULL)
    {
        /* notify the CFE of the event */
        GLOBAL_CFE_CONFIGDATA.SystemNotify();
    }
    return returnStatus;
}


/******************************************************************************
**  Function: CFE_PSP_AttachExceptions
**
**  Purpose:
**    This function Initializes the VxWorks EDR Ploicy handling. The handler
**    is called for every exception that other handlers do not handle.
**
**    Notes: The floating point exceptions are handled by the default floating
**           point exception handler, which does a graceful recovery from
**           floating point exceptions in the file speExcLib.c.
**
**  Arguments:
**    None
**
**  Return:
**    None
******************************************************************************/
void CFE_PSP_AttachExceptions(void)
{
	currentedrPolicyHandlerHook = edrPolicyHandlerHookGet();
    if (currentedrPolicyHandlerHook != NULL)
    {
        /* The call to edrErrorPolicyHookRemove will return ERROR if the handler
         * is NULL otherwise it set the handler to NULL. No action was required but
         * ignoring an error is a bad practice.
         */
        if (edrErrorPolicyHookRemove() == ERROR)
        {
                OS_printf("CFE_PSP_AttachException() - edrErrorPolicyHookRemove() failed for address 0x%llx ", (uint64)currentedrPolicyHandlerHook);
                currentedrPolicyHandlerHook = NULL;
        }

    }

    if (edrPolicyHandlerHookAdd(CFE_PSP_edrPolicyHandlerHook) == ERROR)
    {
        OS_printf("CFE_PSP_AttachException() - edrPolicyHandlerHookAdd() failed "
               "for CFE_PSP_edrPolicyHandlerHook()");
    }
    else
    {
        OS_printf("CFE_PSP_AttacheException() - Attached cFE Exception Handler. ");
    }
}



/******************************************************************************
**  Function: CFE_PSP_SetDefaultExceptionEnvironment
**
**  Purpose:
**    This function sets a default exception environment that can be used
**
**    Notes: The exception environment is local to each task. Therefore, this
**           must be called for each task that wants to do floating point and
**           catch exceptions. Currently, this is automatically called from
**           OS_TaskRegister() for every task.
**
**  Arguments:
**    None
**
**  Return:
**    None
******************************************************************************/
void CFE_PSP_SetDefaultExceptionEnvironment(void)
{
    /* TODO: Determine the proper exception environment for the SP0 */
}

/*
 * Name: CFE_PSP_ExceptionGetSummary_Impl
 *
 * Purpose: Translate a stored exception log entry into a summary string
 */
int32 CFE_PSP_ExceptionGetSummary_Impl(const CFE_PSP_Exception_LogData_t* Buffer, char *ReasonBuf, uint32 ReasonSize)
{
    const char *TaskName;

    /*
    ** Get the vxWorks task name
    */
    TaskName = taskName(Buffer->sys_task_id);

    if ( TaskName == NULL )
    {
        TaskName = "NULL";
    }

    snprintf(ReasonBuf, ReasonSize, "Vector=0x%06X, vxWorks Task Name=%s, Task ID=0x%08X",
            Buffer->context_info.vector,TaskName,Buffer->sys_task_id);

    return CFE_PSP_SUCCESS;
}

