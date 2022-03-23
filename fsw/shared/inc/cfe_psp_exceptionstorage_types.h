/**
 * \file
 *
 * Provides a generic storage buffer ring for exceptions
 */

#ifndef CFE_PSP_EXCEPTIONSTORAGE_TYPES_H_
#define CFE_PSP_EXCEPTIONSTORAGE_TYPES_H_

#include "cfe_psp.h"
#include "cfe_psp_config.h"

/*
 * The "MetaData" stores ephemeral exception information
 * which only has meaning within the currently-running process.
 *
 * This data is important for diagnosing the exception, but it
 * is NOT saved to any persistent log because it will not be
 * relevant once the process ends.
 */
struct CFE_PSP_Exception_LogData
{
    uint32                               context_id;   /**< a unique ID assigned to this exception entry */
    uint32                               context_size; /**< actual size of the "context_info" data */
    CFE_PSP_Exception_SysTaskId_t        sys_task_id;  /**< the BSP-specific task info (not osal abstracted id) */
    CFE_PSP_Exception_ContextDataEntry_t context_info;
};

struct CFE_PSP_ExceptionStorage
{
    volatile uint32                  NumWritten;
    volatile uint32                  NumRead;
    struct CFE_PSP_Exception_LogData Entries[CFE_PSP_MAX_EXCEPTION_ENTRIES];
};

typedef struct CFE_PSP_Exception_LogData CFE_PSP_Exception_LogData_t;
typedef struct CFE_PSP_ExceptionStorage  CFE_PSP_ExceptionStorage_t;

#endif /* CFE_PSP_EXCEPTIONSTORAGE_TYPES_H_ */
