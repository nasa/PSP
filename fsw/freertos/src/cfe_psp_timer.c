#define CFE_PSP_TIMER_TICKS_PER_SECOND ((int32) configTICK_RATE_HZ)

uint32 CFE_PSP_GetTimerTicksPerSecond(void)
{
	return CFE_PSP_TIMER_TICKS_PER_SECOND;
}

uint32 CFE_PSP_GetTimerLow32Rollover(void)
{
	return 0;
}

void CFE_PSP_Get_Timebase(uint32 *Tbu, uint32 *Tbl)
{
	// SysTick is set up in HAL_Init
	return xTaskGetTickCount;
}
