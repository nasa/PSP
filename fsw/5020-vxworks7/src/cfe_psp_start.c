/******************************************************************************
**
** File:  cfe_psp_start.c
**
**      Copyright (c) 2004-2011, United States Government as represented by
**      Administrator for The National Aeronautics and Space Administration.
**      All Rights Reserved.
**
**      This is governed by the NASA Open Source Agreement and may be used,
**      distributed and modified only pursuant to the terms of that agreement.
**
** Purpose:
**   cFE PSP main entry point
**
******************************************************************************/

/*
**  Include Files
*/
#include <stdio.h>
#include <string.h>
#include <vxWorks.h>
#include <taskLib.h>
#include "osapi.h"
#include "cfe.h"
#include "cfe_psp.h"
#include "cfe_psp_memory.h"
#include "target_config.h"
#include <target_config.h>

#include <vxFdtLib.h>

extern VIRT_ADDR vxMmuEarlyRegMap(PHYS_ADDR p, size_t len); /* for pixis aux reg */
/*
** Macro Definitions
*/
#define CFE_PSP_TASK_PRIORITY    (30)
#define CFE_PSP_TASK_STACK_SIZE  (20 * 1024)

/* CFE_PSP_TIMER_PRINT_DBG
**
**   Debug flag
*/
#define CFE_PSP_TIMER_PRINT_DBG  FALSE

#define PSP_1HZ_INTERVAL 1000000

/*
**  External Function Prototypes
*/

/*
 * The preferred way to obtain the CFE tunable values at runtime is via
 * the dynamically generated configuration object.  This allows a single build
 * of the PSP to be completely CFE-independent.
 */

#define CFE_PSP_MAIN_FUNCTION        (*GLOBAL_CONFIGDATA.CfeConfig->SystemMain)
#define CFE_PSP_NONVOL_STARTUP_FILE  (GLOBAL_CONFIGDATA.CfeConfig->NonvolStartupFile)
#define CFE_PSP_1HZ_FUNCTION         (*GLOBAL_CONFIGDATA.CfeConfig->System1HzISR)

/*
**  Local Function Prototypes
*/
static int32 SetSysTasksPrio(void);
static int32 SetTaskPrio(const char* tName, int32 tgtPrio);
void CFE_PSP_Start(void);

/*
**  Local Global Variables
*/
static uint32 ResetType = 0;
static uint32 ResetSubtype = 0;
//static USER_SAFE_MODE_DATA_STRUCT safeModeUserData;
static uint32 PSP_1Hz_TimerId = 0;
static uint32 PSP_1Hz_ClockAccuracy = 0;

/*
 * The list of VxWorks task to change the task priority
 * to before finishing initialization.
 */

CFE_PSP_OS_Task_and_priority_t VxWorksTaskList[] =
{
    {"tLogTask", 0},
    {"tShell0", 201},
    {"tWdbTask", 203},
    {"tVxdbgTask", 200},
    {"tNet0", 25},         /* Should be set right below CI/TO */
    {"ipftps", 202},
    {"ipcom_syslogd", 205},
    {"ipcom_telnetd", 204}
};

/******************************************************************************
**  Function:  CFE_PSP_Main()
**
**  Purpose:
**    vxWorks/PSP Application entry point
**
**  Arguments:
**    None
**  Return:
**    None
******************************************************************************/
void CFE_PSP_Main(void)
{
    TASK_ID root_task_id = NULL;
    char name[] = "PSP_START";

    /* Need to add VX_FP_TASK (all tasks should just be created with it...
    ** to deal with an "SPE unknown exception" error as soon as this task
    ** would start on the SP0/PPC8548.
    */

    /* Note: When using e500vx_gnu tool chain, including VX_FP_TASK implicitly
    ** includes VX_SPE_TASK, which is needed when starting tasks that might
    ** use floating point on this processor.
    */
    OS_printf_enable();
    root_task_id = taskSpawn(name, CFE_PSP_TASK_PRIORITY,
                             VX_FP_TASK, CFE_PSP_TASK_STACK_SIZE,
                             (FUNCPTR) CFE_PSP_Start, 0,
                             0,0,0,0,0,0,0,0,0);

    if ((root_task_id == TASK_ID_NULL)||(root_task_id == TASK_ID_ERROR))
    {
        OS_printf("CFE_PSP_Main() - ERROR - Unable to spawn PSP_START task!");
    }
}

/******************************************************************************
**  Function:  CFE_PSP_Start()
**
**  Purpose:
**    Application startup entry point from OSAL BSP.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
void CFE_PSP_Start(void)
{
    int32 status = OS_SUCCESS;
    int32 time_status;
    int32 taskSetStatus = OS_SUCCESS;
    uint32 sys_timebase_id;
    uint32 fs_id;

    /* Initialize the OS API data structures */
    status = OS_API_Init();
    if (status != OS_SUCCESS)
    {
        OS_printf("CFE_PSP: CFE_PSP_Start() - OS_API_Init() failed (0x%X)\n",
               status);
        goto CFE_PSP_Start_Exit_Tag;
    }

    CFE_PSP_SetupReservedMemoryMap();

    /* Initialize the watchdog, it's left disabled */
    CFE_PSP_WatchdogInit();

    /* PSP Determine the reset type */
    /* SDS: use the pixis PX_AUX reg (offset 6) which is 0 on POR to determine POR,
     * as there is no reset cause register on this hardware */
    ResetType = CFE_PSP_RST_TYPE_POWERON; /* default value is safe */

    /* SDS: board is DDR so memory clears upon restart. In order to prevent the system
     * assuming the CDS (Critical data store) area of memory is not going to be clear,
     * treat all restarts as poweron for now */
#if 0
    {
        PHYS_ADDR pixis_phys_addr=0;
        VIRT_ADDR pixis_virt_addr=0;
        size_t pixis_size = 0;
        int offset = vxFdtNodeOffsetByCompatible(0, (char*)"fsl,fpga-ngpixis");
        if(offset>=0) {
            if(vxFdtDefRegGet(offset, 0, &pixis_phys_addr, &pixis_size)==OK) {
                pixis_virt_addr = vxMmuEarlyRegMap(pixis_phys_addr, pixis_size);
                if(pixis_virt_addr) {
                    if((*(volatile uint8_t*)(pixis_virt_addr+6))) ResetType = CFE_PSP_RST_TYPE_PROCESSOR;
                    (*(volatile uint8_t*)(pixis_virt_addr+6)) = 1; /* the 1 will persist across warm reset */
                }
            }
        }
    }
#endif

    /* Initialize the reserved memory */
    if (CFE_PSP_InitProcessorReservedMemory(ResetType) != OS_SUCCESS)
    {
        OS_printf("CFE_PSP: CFE_PSP_Start() - CFE_PSP_InitProcessorReservedMemory() failed (0x%x)\n",
                  status);
        goto CFE_PSP_Start_Exit_Tag;
    }

    time_status = OS_TimeBaseCreate(&sys_timebase_id, "cFS-Master", NULL);
    if(time_status == OS_SUCCESS) {
        time_status = OS_TimeBaseSet(sys_timebase_id, 10000, 10000);
        /* example pc-linux psp doesn't check return value? */
    }
    else {
        sys_timebase_id = 0;
    }

    status = OS_FileSysAddFixedMap(&fs_id, "host:/cf", "/cf");
    if(status != OS_SUCCESS)
    {
        /* startup can continue, but loads may fail later depending on config */
        OS_printf("CFE_PSP: OS_FileSysAddFixedMap() failure: %d\n", (int)status);
    }

    /*
    ** Adjust system task priorities so that tasks such as the shell are
    ** at a lower priority that the CFS apps
    */
    taskSetStatus = SetSysTasksPrio();

    /* Call cFE entry point. This will return when cFE startup is complete. */
    CFE_PSP_MAIN_FUNCTION(ResetType, ResetSubtype, 1, CFE_PSP_NONVOL_STARTUP_FILE);

    CFE_ES_WriteToSysLog("CFE_PSP: %s reset\n", (ResetType==CFE_PSP_RST_TYPE_POWERON)?"power on":"processor");

    OS_Application_Run();

    if (taskSetStatus != OS_SUCCESS)
    {
        CFE_ES_WriteToSysLog("CFE_PSP: CFE_PSP_Start() At least one vxWorks task priority set failed. System may have degraded performance.\n");
    }

    CFE_ES_WriteToSysLog("CFE_PSP: CFE_PSP_Start() done.\n");

CFE_PSP_Start_Exit_Tag:
    return;
}


/******************************************************************************
**  Function:  CFE_PSP_GetRestartType()
**
**  Purpose:
**    Provides the CFE PSP reset type and subtype
**
**  Arguments:
**    Output - resetSubType - Reset subtype
**
**  Return:
**    Reset type
******************************************************************************/
uint32 CFE_PSP_GetRestartType(uint32 *resetSubType)
{
    if (resetSubType != NULL)
    {
        *resetSubType = ResetSubtype;
    }

    return (ResetType);
}


/******************************************************************************
**  Function:  SetTaskPrio()
**
**  Purpose:
**    Changes default task priority to a given priority
**
**  Arguments:
**    Input - tName - Task name
**    Input - tgtPrio - New task priority
**
**  Return:
**     None
******************************************************************************/
static int32 SetTaskPrio(const char* tName, int32 tgtPrio)
{
    TASK_ID tid = NULL;
    int32 curPrio = 0;
    int32 newPrio = 0;
    int32 status = OS_SUCCESS;

    if ((tName != NULL) && (strlen(tName) > 0))
    {
        newPrio = tgtPrio;
        if (newPrio < 0)
        {
            newPrio = 0;
        }
        else if (newPrio > 255)
        {
            newPrio = 255;
        }

        tid = taskNameToId((char*)tName);
        if ((tid!=TASK_ID_NULL)&&(tid!=TASK_ID_ERROR))
        {
            if (taskPriorityGet(tid, (int *)&curPrio) != ERROR)
            {
                OS_printf("PSP: SetTaskPrio() - Setting %s priority from %d to %d\n",
                       tName, curPrio, newPrio);

                if (taskPrioritySet(tid, newPrio) == ERROR)
                {
                        OS_printf("PSP: taskPrioritySet() - Failed for %s priority from %d to %d\n",
                                  tName, curPrio, newPrio);
                        status = OS_ERROR;
                }

            }
        }
    }

    return status;
}


/******************************************************************************
**  Function:  SetSysTasksPrio()
**
**  Purpose:
**    Changes system task priorities so that they are lower than CFS system
**    task priorities
**
**    Note: tNet0 priority should be adjusted to be right below what ever
**    gets defined for CI/TO apps in your system if using the network
**    interface CCSDS/UDP for CI/TO apps.
**
**  Arguments:
**    None
**
**  Return:
**    None
******************************************************************************/
static int32 SetSysTasksPrio(void)
{
    int32 status = OS_SUCCESS;
    int32 index = 0;

    int32 numberOfTask = sizeof(VxWorksTaskList)/sizeof(CFE_PSP_OS_Task_and_priority_t);

    OS_printf("\nSetting system tasks' priorities for %d tasks.\n", numberOfTask);

    for (index = 0; index < numberOfTask; index++)
    {
        if (SetTaskPrio(VxWorksTaskList[index].VxWorksTaskName, VxWorksTaskList[index].VxWorksTaskPriority) != OS_SUCCESS)
        {
            status = OS_ERROR;
        }
    }

    return status;
}


/******************************************************************************
**  Function:  PSP_1HzLocalCallback()
**
**  Purpose:
**    The 1Hz call back handler calls the cfe 1Hz routine
**
**  Arguments:
**    Input TimerId - Id for 1Hz timer
**
**  Return:
**    (none)
*/
void PSP_1HzLocalCallback(uint32 TimerId)
{
#if CFE_PSP_TIMER_PRINT_DBG == TRUE
      OS_time_t LocalTime;
      CFE_PSP_GetTime(&LocalTime);
#endif
      CFE_PSP_1HZ_FUNCTION();
#if CFE_PSP_TIMER_PRINT_DBG == TRUE

      OS_printf("PSP_1HzLocalCallback: PSP Local Time: %d.%d\n", LocalTime.seconds,LocalTime.microsecs);
#endif
}
/******************************************************************************
**  Function:  OS_Application_Run()
**
**  Purpose:
**    Initializes the 1Hz timer connects the cFE 1Hz ISR for providing the
**    CFS 1Hz time sync, sync the scheduler's 1Hz major frame start to the
**    1Hz timer.
**
**  Arguments:
**    (none)
**
**  Return:
**    (none)
*/
void OS_Application_Run(void)
{
   int32  Status    = CFE_SUCCESS;

   /*Create the 1Hz timer for synchronizing the major frame*/
   Status = OS_TimerCreate(&PSP_1Hz_TimerId,
                            "PSP_1HZ_TIMER",
                            &PSP_1Hz_ClockAccuracy,
                            PSP_1HzLocalCallback);
   if (Status != CFE_SUCCESS)
   {
       CFE_ES_WriteToSysLog("Failed to create OS_Timer for 1Hz local time.\n");
   }
   else
   {
       /*Set the interval to one second in microseconds.*/
       Status = OS_TimerSet(PSP_1Hz_TimerId, PSP_1HZ_INTERVAL, PSP_1HZ_INTERVAL);
       if (Status != CFE_SUCCESS)
       {
           CFE_ES_WriteToSysLog("Failed to set OS_Timer for 1Hz local time.\n");
       }
   }

}

/*TODO have osal add conditional compile when SPE preset instead of FPU
 * Once that has occurred we can remove vxFpscrGet and vxFpscrSet
 * */
/******************************************************************************
**  Function:  vxFpscrGet()
**
**  Purpose:
**    Provides stub function for FPU exception handler, vxFpscrGet()
**
**    Added this function here so that the code can compile & run without error.
**
**    If there's code that calls these functions, we will get a message like so,
**       > ld < cfe-core.o
**       Warning: module 0x461d010 holds reference to undefined symbol vxFpscrGet.
**       Warning: module 0x461d010 holds reference to undefined symbol vxFpscrSet.
**
**    These do not seem to be included in 85xx build, but are defined as
**       "defined(_PPC_) && CPU != PPC440" in vxWorks osapi.c, line 2707, v4.2.1a
**
**    If this function is not used, stub it out like below. Otherwise, define it.
**
**  Arguments:
**    None
**
**  Return:
**    0
*******************************************************************************/
unsigned int vxFpscrGet(void)
{
    CFE_ES_WriteToSysLog("%s->%s<stub>:%d:\n", __FILE__, __func__, __LINE__);

    return (0);
}


/******************************************************************************
**  Function:  vxFpscrSet()
**
**  Purpose:
**    Provides stub function for FPU exception handler, vxFpscrSet()
**
**    Added this function here so that the code can compile & run without error.
**
**    If there's code that calls these functions, we will get a message like so,
**       > ld < cfe-core.o
**       Warning: module 0x461d010 holds reference to undefined symbol vxFpscrGet.
**       Warning: module 0x461d010 holds reference to undefined symbol vxFpscrSet.
**
**    These do not seem to be included in 85xx build, but are defined as
**       "defined(_PPC_) && CPU != PPC440" in vxWorks osapi.c, line 2707, v4.2.1a
**
**    If this function is not used, stub it out like below. Otherwise, define it.
**
**  Arguments:
**    Input - x - TODO: Describe x
**
**  Return:
**    None
*******************************************************************************/
void vxFpscrSet(unsigned int x)
{
    CFE_ES_WriteToSysLog("%s->%s<stub>:%d:\n", __FILE__, __func__, __LINE__);
}

