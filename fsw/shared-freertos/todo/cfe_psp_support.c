#include "cfe_psp.h"
#include "cfe_psp_config.h"
#include "cfe_psp_memory.h"


/* The target config allows refs into global CONFIGDATA object(s) for CFE runtime settings */
#include <target_config.h>

#define CFE_PSP_CPU_ID        (GLOBAL_CONFIGDATA.Default_CpuId)
#define CFE_PSP_CPU_NAME      (GLOBAL_CONFIGDATA.Default_CpuName)
#define CFE_PSP_SPACECRAFT_ID (GLOBAL_CONFIGDATA.Default_SpacecraftId)


/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
uint32 CFE_PSP_GetProcessorId(void)
{
    return CFE_PSP_CPU_ID;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
uint32 CFE_PSP_GetSpacecraftId(void)
{
    return CFE_PSP_SPACECRAFT_ID;
}

/*----------------------------------------------------------------
 *
 * Implemented per public API
 * See description in header file for argument/return detail
 *
 *-----------------------------------------------------------------*/
const char *CFE_PSP_GetProcessorName(void)
{
    return CFE_PSP_CPU_NAME;
}


void CFE_PSP_Restart(uint32 resetType){
    // @FIXME not implemented
     // #if (sizeof(long) == sizeof(int32))
    OS_printf("CFE_PSP_Restart(%lu). Not implemented.\n", (long unsigned int)resetType);
    // #elif (sizeof(int) == sizeof(int32))
    // OS_printf("CFE_PSP_Restart(%u). Not implemented.\n", resetType);
    // #else
    // #error
    // #endif

    CFE_PSP_Panic(CFE_PSP_ERROR_NOT_IMPLEMENTED);    
}
