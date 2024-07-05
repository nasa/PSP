#include "cfe_psp.h"
#include "cfe_psp_config.h"

uint32 CFE_PSP_WatchdogValue = CFE_PSP_WATCHDOG_MAX;

void CFE_PSP_WatchdogInit(void)
{
	CFE_PSP_WatchdogValue = CFE_PSP_WATCHDOG_MAX;
}

void CFE_PSP_WatchdogEnable(void)
{
	/* TODO */
}

void CFE_PSP_WatchdogDisable(void)
{
	/* TODO */
}

void CFE_PSP_WatchdogService(void)
{
	/* TODO */
}

uint32 CFE_PSP_WatchdogGet(void)
{
	return CFE_PSP_WatchdogValue;
}

void CFE_PSP_WatchdogSet(uint32 WatchdogValue)
{
	CFE_PSP_WatchdogValue = WatchdogValue;
}
