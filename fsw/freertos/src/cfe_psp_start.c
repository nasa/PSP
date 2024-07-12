#include "cmsis_os.h"

#include "cfe_psp.h"
#include "cfe_psp_config.h"

#include "target_config.h"

#define CFE_PSP_MAIN_FUNCTION (*GLOBAL_CONFIGDATA.CfeConfig->SystemMain)

#define CFE_PSP_NONVOL_STARTUP_FILE (GLOBAL_CONFIGDATA.CfeConfig->NonvolStartupFile)


void CFE_PSP_Restart(uint32 resetType)
{
	if (resetType == CFE_PSP_RST_TYPE_POWERON) 
	{
		CFE_PSP_ReservedMemoryMap.BootPtr->bsp_reset_type = CFE_PSP_RST_TYPE_POWERON;
		CFE_PSP_FlushCaches(1, ReservedMemBlock.BlockPtr, ReservedMemBlock.BlockSize);
		
		NVIC_SystemReset();
	}
	else
	{
		CFE_PSP_ReservedMemoryMap.BootPtr->bsp_reset_type = CFE_PSP_RST_TYPE_PROCESSOR;
		CFE_PSP_FlushCaches(1, ReservedMemBlock.BlockPtr, ReservedMemBlock.BlockSize);
		/* FIXME: reboot without wiping memory */
	}
}


/* TODO: review this implementation by pztrick */

int CFE_PSP_Setup(void){
	return CFE_PSP_SUCCESS;
}

void CFE_PSP_Panic(int32 ErrorCode){
	__asm("bkpt 1");
	// vTaskEndScheduler();
	OS_ApplicationExit(ErrorCode);
}

// OSAL:main() invokes PSP:OS_Application_Startup() inside a FreeRTOS task
void OS_Application_Startup(void){
	int32 status;
	uint32 reset_type;
	uint32 reset_subtype;
	
	CFE_PSP_SetupReservedMemoryMap();

	status = OS_API_Init();
	if(status != OS_SUCCESS){
		OS_ApplicationExit(status);
	}

	if(CFE_PSP_Setup() != CFE_PSP_SUCCESS){
		CFE_PSP_Panic(CFE_PSP_ERROR);
	}

	// @FIXME should try to read reset_type from NVM BootPtr
	reset_type = CFE_PSP_RST_TYPE_POWERON;
	reset_subtype = CFE_PSP_RST_SUBTYPE_POWER_CYCLE;
	CFE_PSP_InitProcessorReservedMemory(reset_type);

	CFE_PSP_MAIN_FUNCTION(reset_type, reset_subtype, 1, CFE_PSP_NONVOL_STARTUP_FILE);

	vTaskDelete(NULL);
}
