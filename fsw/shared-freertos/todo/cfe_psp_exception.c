// #include <string.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include "common_types.h"
// #include "osapi.h"


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
**   Purpose: No-op on this platform, implemented for API compatibility.
**
*/
void CFE_PSP_AttachExceptions(void)
{
    OS_printf("CFE_PSP: %s called\n", __func__);
    CFE_PSP_Exception_Reset();
}


/*
 * Purpose: Translate a stored exception log entry into a summary string
 */
int32 CFE_PSP_ExceptionGetSummary_Impl(const CFE_PSP_Exception_LogData_t *Buffer, char *ReasonBuf, uint32 ReasonSize)
{
    /* exceptions are not yet implemented on this platform */
    return CFE_PSP_ERROR_NOT_IMPLEMENTED;
}

/*
**
**   Not implemented.
**
*/
void CFE_PSP_SetDefaultExceptionEnvironment(void)
{
}
