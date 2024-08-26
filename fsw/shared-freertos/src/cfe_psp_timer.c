#include "cfe_psp.h"
#include "cfe_psp_config.h"

#define CFE_PSP_TIMER_TICKS_PER_SECOND ((int32) configTICK_RATE_HZ)

// @FIXME research if this value for CFE_PSP_TIMER_LOW32_ROLLOVER is correct
#define CFE_PSP_TIMER_LOW32_ROLLOVER 0

uint32 CFE_PSP_GetTimerTicksPerSecond(void)
{
    return CFE_PSP_TIMER_TICKS_PER_SECOND;
}

uint32 CFE_PSP_GetTimerLow32Rollover(void)
{
    return CFE_PSP_TIMER_LOW32_ROLLOVER;
}
