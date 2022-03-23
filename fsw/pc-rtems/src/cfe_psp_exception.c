/******************************************************************************
**
** File:  cfe_psp_exception.c
**
**      m5235bcc Coldfire RTEMS Version
**
** Purpose:
**   cFE BSP Exception related functions.
**
** History:
**   2007/09/23  A. Cudmore      | RTEMS Coldfire m5235bcc version
**
******************************************************************************/

/*
**  Include Files
*/
#include <stdio.h>
#include <string.h>

/*
** cFE includes
*/
#include "common_types.h"
#include "osapi.h"

#include "cfe_psp.h"
#include "cfe_psp_config.h"
#include "cfe_psp_memory.h"
#include "cfe_psp_exceptionstorage_types.h"
#include "cfe_psp_exceptionstorage_api.h"

/*
**
** LOCAL FUNCTION PROTOTYPES
**
*/

/***************************************************************************
 **                        FUNCTIONS DEFINITIONS
 ***************************************************************************/

/*
**
**   Name: CFE_PSP_AttachExceptions
**
**   Purpose: No-op on this platform, implemented for API compatibility.
**
*/
void CFE_PSP_AttachExceptions(void)
{
    OS_printf("CFE_PSP: CFE_PSP_AttachExceptions Called\n");
    CFE_PSP_Exception_Reset();
}

/*
 * Name: CFE_PSP_ExceptionGetSummary_Impl
 *
 * Purpose: Translate a stored exception log entry into a summary string
 */
int32 CFE_PSP_ExceptionGetSummary_Impl(const CFE_PSP_Exception_LogData_t *Buffer, char *ReasonBuf, uint32 ReasonSize)
{
    /* exceptions are not yet implemented on this platform */
    return CFE_PSP_ERROR_NOT_IMPLEMENTED;
}

/*
**
**   Name: CFE_PSP_SetDefaultExceptionEnvironment
**
**   Purpose: This function sets a default exception environment that can be used
**
**   Notes: The exception environment is local to each task Therefore this must be
**          called for each task that that wants to do floating point and catch exceptions
*/
void CFE_PSP_SetDefaultExceptionEnvironment(void)
{
    return;
}
