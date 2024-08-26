#ifndef _cfe_psp_config_
#define _cfe_psp_config_

// FreeRTOS headers
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"


/*
** This define sets the number of memory ranges that are defined in the memory range definition
** table.
*/
#define CFE_PSP_MEM_TABLE_SIZE 2

/*
 * The tick period that will be configured in the RTOS for the simulated
 * time base, in microseconds.  This in turn is used to drive the 1hz clock
 * and other functions.
 *
 * To minimize jitter in the resulting callbacks, it should be an even
 * divisor of 1000000 usec.
 *
 * Note - 10ms/100Hz is chosen to also allow this same timebase to be
 * used to drive the CFS SCH minor frame callbacks in its default config.
 */
#define CFE_PSP_SOFT_TIMEBASE_PERIOD 10000

// Memory tables
// cfe_psp_memory.c
#define CFE_PSP_MEMALIGN_MASK ((cpuaddr) 0x40)  // ARM may be designed with 64 byte processor cache
typedef struct
{
    uint32 bsp_reset_type;
    uint32 reserved1;
    uint32 reserved2;
    uint32 reserved3;
} CFE_PSP_ReservedMemoryBootRecord_t;


// Exception handling
// @FIXME needs to be implemented with cfe_psp_exception.c
#define CFE_PSP_MAX_EXCEPTION_ENTRIES 4
typedef UBaseType_t CFE_PSP_Exception_SysTaskId_t;
typedef struct
{
    uint32 reserved1;
} CFE_PSP_Exception_ContextDataEntry_t;

// /*
//  * A random 32-bit value that is used as the "validity flag"
//  * of the PC-Linux boot record structure.  This is simply
//  * a value that is unlikely to occur unless specifically set.
//  */
// #define CFE_PSP_BOOTRECORD_VALID   ((uint32)0x2aebe984)
// #define CFE_PSP_BOOTRECORD_INVALID (~CFE_PSP_BOOTRECORD_VALID)


/*
** Watchdog minimum and maximum values ( in milliseconds )
*/
// @FIXME needs to be implemented with cfe_psp_watchdog.c
#define CFE_PSP_WATCHDOG_MIN 0  // millieconds
#define CFE_PSP_WATCHDOG_MAX 0xFFFFFFFF  // milliseconds

/*
** Number of EEPROM banks on this platform
*/
#define CFE_PSP_NUM_EEPROM_BANKS 0

#endif

