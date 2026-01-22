/************************************************************************
 * NASA Docket No. GSC-19,200-1, and identified as "cFS Draco"
 *
 * Copyright (c) 2023 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

/******************************************************************************
** File:  cfe_psp_start.c
**
** Purpose:
**   cFE PSP main entry point.
**
** History:
**   2004/09/23  J.P. Swinski    | Initial version,
**   2004/10/01  P.Kutt          | Replaced OS API task delay with VxWorks functions
**                                 since OS API is initialized later.
**   2016/04/07  M.Grubb         | Updated for PSP version 1.3
**
******************************************************************************/

/*
**  Include Files
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <sys/time.h>
#include "vxWorks.h"

/*
** cFE includes
*/
#include "common_types.h"
#include "osapi.h"

#include "cfe_psp.h"
#include "cfe_psp_memory.h"
#include "cfe_psp_module.h"

#include "parg.h"

/*
**  External Declarations
*/

/*
 * The preferred way to obtain the CFE tunable values at runtime is via
 * the dynamically generated configuration object.  This allows a single build
 * of the PSP to be completely CFE-independent.
 */
#include "target_config.h"

#define CFE_PSP_MAIN_FUNCTION       (*GLOBAL_CONFIGDATA.CfeConfig->SystemMain)
#define CFE_PSP_1HZ_FUNCTION        (*GLOBAL_CONFIGDATA.CfeConfig->System1HzISR)
#define CFE_PSP_NONVOL_STARTUP_FILE (GLOBAL_CONFIGDATA.CfeConfig->NonvolStartupFile)
#define CFE_PSP_CPU_ID              (GLOBAL_CONFIGDATA.Default_CpuId)
#define CFE_PSP_CPU_NAME            (GLOBAL_CONFIGDATA.Default_CpuName)
#define CFE_PSP_SPACECRAFT_ID       (GLOBAL_CONFIGDATA.Default_SpacecraftId)

#define CFE_PSP_KERNEL_NAME_LENGTH_MAX 16

/*
** Typedefs for this module
*/

/*
** Prototypes for this module
*/
void CFE_PSP_DisplayUsage(char *Name);
void CFE_PSP_ProcessArgumentDefaults(CFE_PSP_CommandData_t *CommandDataDefault);

/*
** Global data for this module
*/
CFE_PSP_CommandData_t   CommandData;
int32                   CFE_PSP_SpacecraftId;
uint32                  CFE_PSP_CpuId;
char                    CFE_PSP_CpuName[CFE_PSP_CPU_NAME_LENGTH];
CFE_PSP_IdleTaskState_t CFE_PSP_IdleTaskState;

/*
** getopts parameter passing options string
*/
static const char *optString = "R:S:C:I:N:F:h";

/*
** getopts_long long form argument table
*/
static const struct parg_option longOpts[] = {{"reset",   PARG_REQARG, NULL, 'R'},
                                              {"subtype", PARG_REQARG, NULL, 'S'},
                                              {"cpuid",   PARG_REQARG, NULL, 'C'},
                                              {"scid",    PARG_REQARG, NULL, 'I'},
                                              {"cpuname", PARG_REQARG, NULL, 'N'},
                                              {"cfsid",   PARG_REQARG, NULL, 'F'},
                                              {"help",    PARG_NOARG,  NULL, 'h'},
                                              {NULL,      PARG_NOARG,  NULL, 0}};
/*
** OS_Application_Run is called by the OSAL BSP after initialization
*/
void OS_Application_Run(void)
{
    int      sig;
    int      ret;
    sigset_t sigset;

    /*
     * Now that all main tasks are created,
     * this original thread will exist just to service signals
     * that aren't directed to a specific task.
     *
     * OSAL sets a very conservative signal mask that
     * blocks most signals. Start by unblocking the
     * ones that should be handled.
     *
     * Unblock SIGQUIT so the user can force exit the CFE
     * by pressing CTRL+\ (default handler).  Also allow
     * SIGTERM for which a handler was installed in CFE_PSP_AttachExceptions()
     * Unblock SIGCNCL to allow pthread_cancel to work on this thread.
     */
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGQUIT);
    sigaddset(&sigset, SIGTERM);
    sigaddset(&sigset, SIGCNCL);
    pthread_sigmask(SIG_UNBLOCK, &sigset, NULL);

    /*
     * Reset to the signal for background events (SIGUSR1)
     */
    sigemptyset(&sigset);
    sigaddset(&sigset, CFE_PSP_EXCEPTION_EVENT_SIGNAL);

    /*
    ** just wait for events to occur and notify CFE
    **
    ** "shutdownreq" will become true if CFE calls CFE_PSP_Restart(),
    ** indicating a request to gracefully exit and restart CFE.
    */
    while (!CFE_PSP_IdleTaskState.ShutdownReq)
    {
        /* go idle and wait for an event */
        ret = sigwait(&sigset, &sig);

        if (ret == 0 && !CFE_PSP_IdleTaskState.ShutdownReq && sig == CFE_PSP_EXCEPTION_EVENT_SIGNAL &&
            GLOBAL_CFE_CONFIGDATA.SystemNotify != NULL)
        {
            /* notify the CFE of the event */
            GLOBAL_CFE_CONFIGDATA.SystemNotify();
        }
    }

    /*
     * This happens if an unhandled exception occurs, or if the user presses CTRL+C
     */
    OS_printf("\nCFE_PSP: Shutdown initiated - Exiting cFE\n");
    OS_TaskDelay(100);

    OS_DeleteAllObjects();
}

/*
** CFE_PSP_OS_EventHandler
**
** This function is called by the OSAL to handle specific events
** such as task creation and deletion.
**
** Note that some of the items here are a work in progress:
**   - setting the processor affinity of tasks
**   - assigning a name to each task using the non-posix pthread_setname_np
**     - this is commented out because it is not supported in vxWorks SR0650
*/
int32 CFE_PSP_OS_EventHandler(OS_Event_t event, osal_id_t object_id, void *data)
{
    char      taskname[OS_MAX_API_NAME];
    sigset_t  sigset;

    /*
    ** VxWorks RTP work todo: enable processor affinity
    ** cpu_set_t cpuset;
    */

    memset(taskname, 0, sizeof(taskname));

    switch (event)
    {
        case OS_EVENT_RESOURCE_ALLOCATED:
            /* resource/id is newly allocated but not yet created.  Invoked within locked region. */
            break;
        case OS_EVENT_RESOURCE_CREATED:
            /* resource/id has been fully created/finalized.  Invoked outside locked region. */
            break;
        case OS_EVENT_RESOURCE_DELETED:
            /* resource/id has been deleted.  Invoked outside locked region. */
            break;
        case OS_EVENT_TASK_STARTUP:
        {
            /* New task is starting. Invoked from within the task context. */
            /* Get the name from OSAL and propagate to the pthread/system layer */
            if (OS_GetResourceName(object_id, taskname, sizeof(taskname)) == OS_SUCCESS)
            {
                /*
                 * Example mechanism for setting thread affinity
                 *
                 * Could assign based on task name, pattern within name (CFE_* on 0,
                 * *_CN where N is desired core), round robin or whatever the requrements are.
                 *
                 * Just assigning all "CFE_*" tasks to core zero and let the rest float.
                 */
                /*
                ** VxWorks RTP work todo: enable processor affinity
                ** if (strncmp(taskname, "CFE_", 4) == 0)
                ** {
                **    CPU_ZERO(&cpuset);
                **    CPU_SET(0, &cpuset);
                **    pthread_setaffinity_np(pthread_self(), sizeof(cpuset), &cpuset);
                ** }
		*/
                /*
                 * glibc/kernel has an internal limit for this name.
                 * If the OSAL name is longer, just truncate it.
                 * Otherwise the name isn't set at all - this assumes the first
                 * chars of the name is better for debug than none of it.
                 */
                if (strlen(taskname) >= CFE_PSP_KERNEL_NAME_LENGTH_MAX)
                {
                    taskname[CFE_PSP_KERNEL_NAME_LENGTH_MAX - 1] = 0;
                }
		/* pthread_setname_np is not in the VxWorks SR650 SDK */
		/* SR0650 supports pthread_attr_setname, but that would require an OSAL modification */
                /* pthread_setname_np(pthread_self(), taskname);  */

                /*
                ** Unblock the SIGCNCL signal used by VxWorks pthread_cancel implementation
                */
                sigemptyset(&sigset);
                sigaddset(&sigset, SIGCNCL);
                pthread_sigmask(SIG_UNBLOCK, &sigset, NULL);
            }
            break;
        }

        default:
            break;
    }

    return OS_SUCCESS;
}

/******************************************************************************
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
void OS_Application_Startup(void)
{
    uint32            reset_type;
    uint32            reset_subtype;
    osal_id_t         fs_id;
    int               opt       = 0;
    int               longIndex = 0;
    int32             Status;
    char *const      *argv;
    int               argc;
    struct parg_state ps;

    /*
    ** Initialize the CommandData struct
    */
    memset(&(CommandData), 0, sizeof(CFE_PSP_CommandData_t));

    /*
    ** Process the arguments with getopt_long(), then
    ** start the cFE
    */
    argc = OS_BSP_GetArgC();
    argv = OS_BSP_GetArgV();

    parg_init(&ps);
    opt  = parg_getopt_long(&ps, argc, argv, optString, longOpts, &longIndex);

    while (opt != -1)
    {
        switch (opt)
        {
            case 'R':
                strncpy(CommandData.ResetType, ps.optarg, CFE_PSP_RESET_NAME_LENGTH - 1);
                CommandData.ResetType[CFE_PSP_RESET_NAME_LENGTH - 1] = 0;

                if ((strncmp(CommandData.ResetType, "PO", CFE_PSP_RESET_NAME_LENGTH) != 0) &&
                    (strncmp(CommandData.ResetType, "PR", CFE_PSP_RESET_NAME_LENGTH) != 0))
                {
                    printf("\nERROR: Invalid Reset Type: %s\n\n", CommandData.ResetType);
                    CommandData.GotResetType = 0;
                    CFE_PSP_DisplayUsage(argv[0]);
                    break;
                }
                printf("CFE_PSP: Reset Type: %s\n", (char *)ps.optarg);
                CommandData.GotResetType = 1;
                break;
            case 'S':
                CommandData.SubType = strtol(ps.optarg, NULL, 0);
                if (CommandData.SubType < 1 || CommandData.SubType > 5)
                {
                    printf("\nERROR: Invalid Reset SubType: %s\n\n", ps.optarg);
                    CommandData.SubType    = 0;
                    CommandData.GotSubType = 0;
                    CFE_PSP_DisplayUsage(argv[0]);
                    break;
                }
                printf("CFE_PSP: Reset SubType: %d\n", (int)CommandData.SubType);
                CommandData.GotSubType = 1;
                break;

            case 'N':
                strncpy(CommandData.CpuName, ps.optarg, CFE_PSP_CPU_NAME_LENGTH - 1);
                CommandData.CpuName[CFE_PSP_CPU_NAME_LENGTH - 1] = 0;
                printf("CFE_PSP: CPU Name: %s\n", CommandData.CpuName);
                CommandData.GotCpuName = 1;
                break;

            case 'C':
                CommandData.CpuId = strtol(ps.optarg, NULL, 0);
                printf("CFE_PSP: CPU ID: %d\n", (int)CommandData.CpuId);
                CommandData.GotCpuId = 1;
                break;

            case 'I':
                CommandData.SpacecraftId = strtol(ps.optarg, NULL, 0);
                printf("CFE_PSP: Spacecraft ID: %d\n", (int)CommandData.SpacecraftId);
                CommandData.GotSpacecraftId = 1;
                break;

            case 'F':
                strncpy(CommandData.CfsId, ps.optarg, CFE_PSP_CFS_ID_LENGTH - 1);
                CommandData.CfsId[CFE_PSP_CFS_ID_LENGTH - 1] = 0;
                printf("CFE_PSP: cFS ID: %s\n", CommandData.CfsId);
                CommandData.GotCfsId = 1;
                break;

            case 'h':
                CFE_PSP_DisplayUsage(argv[0]);
                break;

            default:
                CFE_PSP_DisplayUsage(argv[0]);
                break;
        }
        opt = parg_getopt_long(&ps, argc, argv, optString, longOpts, &longIndex);
    } /* end while */

    /*
    ** Set the defaults for values that were not given for the
    ** optional arguments, and check for arguments that are required.
    */
    CFE_PSP_ProcessArgumentDefaults(&CommandData);

    /*
    ** Assign the Spacecraft ID, CPU ID, and CPU Name
    */
    CFE_PSP_SpacecraftId = CommandData.SpacecraftId;
    CFE_PSP_CpuId        = CommandData.CpuId;
    strncpy(CFE_PSP_CpuName, CommandData.CpuName, sizeof(CFE_PSP_CpuName) - 1);
    CFE_PSP_CpuName[sizeof(CFE_PSP_CpuName) - 1] = 0;

    /*
    ** Set the reset subtype
    */
    reset_subtype = CommandData.SubType;

    /*
    ** Initialize the OS API
    */
    Status = OS_API_Init();
    if (Status != OS_SUCCESS)
    {
        /* irrecoverable error if OS_API_Init() fails. */
        /* note: use printf here, as OS_printf may not work */
        printf("CFE_PSP: OS_API_Init() failure\n");
        CFE_PSP_Panic(Status);

        /*
         * normally CFE_PSP_Panic() does not return, except
         * during unit testing.  This return avoids executing
         * the rest of this function in that case.
         */
        return;
    }

    /*
    ** Set up the virtual FS mapping for the "/cf" directory
    ** On this platform it will use the CF:0 physical device.
    **
    ** VxWorks RTP TODO: Possibly pass the CF path with a command line option
    ** to make this more portable.
    */
#ifdef VXSDK_RPI4
    Status = OS_FileSysAddFixedMap(&fs_id, "/sd0a/cpu1/cf", "/cf");
#else
    Status = OS_FileSysAddFixedMap(&fs_id, "/host.host/cpu1/cf", "/cf");
#endif
    if (Status != OS_SUCCESS)
    {
        /* Print for informational purposes --
         * startup can continue, but loads may fail later, depending on config. */
        OS_printf("CFE_PSP: OS_FileSysAddFixedMap() failure: %d\n", (int)Status);
    }

    /*
    ** Register the event handler
    */
    OS_RegisterEventHandler(CFE_PSP_OS_EventHandler);

    /*
    ** Setup the pointer to the reserved area in vxWorks.
    ** This must be done before any of the reset variables are used.
    */
    CFE_PSP_SetupReservedMemoryMap();

    /*
    ** Initialize the statically linked modules (if any)
    */
    CFE_PSP_ModuleInit();

    /*
     * Prepare for exception handling in the idle task
     */
    memset(&CFE_PSP_IdleTaskState, 0, sizeof(CFE_PSP_IdleTaskState));
    CFE_PSP_IdleTaskState.ThreadID = pthread_self();

    /*
     * determine reset type...
     * If not specified at the command line, then check the "boot record"
     */
    reset_type = 0;
    if (!CommandData.GotResetType)
    {
        reset_type = CFE_PSP_RST_TYPE_POWERON;
        if (CFE_PSP_ReservedMemoryMap.BootPtr->ValidityFlag == CFE_PSP_BOOTRECORD_VALID ||
            CFE_PSP_ReservedMemoryMap.BootPtr->ValidityFlag == CFE_PSP_BOOTRECORD_INVALID)
        {
            reset_type = CFE_PSP_ReservedMemoryMap.BootPtr->NextResetType;
        }
    }
    else if (strncmp("PR", CommandData.ResetType, 2) == 0)
    {
        reset_type = CFE_PSP_RST_TYPE_PROCESSOR;
    }

    if (reset_type == CFE_PSP_RST_TYPE_PROCESSOR)
    {
        OS_printf("CFE_PSP: Starting the cFE with a PROCESSOR reset.\n");
    }
    else
    {
        /* catch-all for anything else */
        reset_type = CFE_PSP_RST_TYPE_POWERON;
        OS_printf("CFE_PSP: Starting the cFE with a POWER ON reset.\n");
    }

    /*
     * If CFE fails to boot with a processor reset,
     * then make sure next time it uses a power on reset.
     */
    if (reset_type == CFE_PSP_RST_TYPE_PROCESSOR)
    {
        CFE_PSP_ReservedMemoryMap.BootPtr->bsp_reset_type = CFE_PSP_RST_TYPE_POWERON;
    }

    /*
    ** Initialize the reserved memory
    */
    CFE_PSP_InitProcessorReservedMemory(reset_type);

    /*
    ** Call cFE entry point. This will return when cFE startup
    ** is complete.
    */
    CFE_PSP_MAIN_FUNCTION(reset_type, reset_subtype, 1, CFE_PSP_NONVOL_STARTUP_FILE);
}

/******************************************************************************
**
**  Purpose:
**    Display program usage, and exit.
**
**  Arguments:
**    Name -- the name of the binary.
**
**  Return:
**    (none)
*/
void CFE_PSP_DisplayUsage(char *Name)
{
    printf("usage : %s [-R <value>] [-S <value>] [-C <value] [-N <value] [-I <value] [-h] \n", Name);
    printf("\n");
    printf("        All parameters are optional and can be used in any order\n");
    printf("\n");
    printf("        Parameters include:\n");
    printf("        -R [ --reset ] Reset Type is one of:\n");
    printf("             PO   for Power On reset ( default )\n");
    printf("             PR   for Processor Reset\n");
    printf("        -S [ --subtype ] Reset Sub Type is one of\n");
    printf("             1   for  Power on ( default )\n");
    printf("             2   for  Push Button Reset\n");
    printf("             3   for  Hardware Special Command Reset\n");
    printf("             4   for  Watchdog Reset\n");
    printf("             5   for  Reset Command\n");
    printf("        -C [ --cpuid ]   CPU ID is an integer CPU identifier.\n");
    printf("             The default  CPU ID is from the platform configuration file: %d\n", CFE_PSP_CPU_ID);
    printf("        -N [ --cpuname ] CPU Name is a string to identify the CPU.\n");
    printf("             The default  CPU Name is from the platform configuration file: %s\n", CFE_PSP_CPU_NAME);
    printf("        -F [ --cfsid ] cFS ID is a string to identify the cFS Instance when running multiple RTPs.\n");
    printf("             The default cFS ID is created by combining the Spacecraft ID and CPU ID\n");
    printf("        -I [ --scid ]    Spacecraft ID is an integer Spacecraft identifier.\n");
    printf("             The default Spacecraft ID is from the mission configuration file: %d\n",
           CFE_PSP_SPACECRAFT_ID);
    printf("        -h [ --help ]    This message.\n");
    printf("\n");
    printf("       Example invocation:\n");
    printf(" \n");
    printf("       Short form:\n");
    printf("       %s -R PO -S 1 -C 1 -N CPU1 -I 32 -F cfs1\n", Name);
    printf("       Long form:\n");
    printf("       %s --reset PO --subtype 1 --cpuid 1 --cpuname CPU1 --scid 32 --cfsid cfs1\n", Name);
    printf(" \n");

    exit(EXIT_FAILURE);
}
/******************************************************************************
**
**  Purpose:
**    This function assigns defaults to parameters and checks to make sure
**    the user entered required parameters
**
**  Arguments:
**    CFE_PSP_CommandData_t *CommandDataDefault -- A pointer to the command parameters.
**
**  Return:
**    (none)
*/
void CFE_PSP_ProcessArgumentDefaults(CFE_PSP_CommandData_t *CommandDataDefault)
{
    if (CommandDataDefault->GotSubType == 0)
    {
        CommandDataDefault->SubType = 1;
        printf("CFE_PSP: Default Reset SubType = 1\n");
        CommandDataDefault->GotSubType = 1;
    }

    if (CommandDataDefault->GotCpuId == 0)
    {
        CommandDataDefault->CpuId = CFE_PSP_CPU_ID;
        printf("CFE_PSP: Default CPU ID = %d\n", CFE_PSP_CPU_ID);
        CommandDataDefault->GotCpuId = 1;
    }

    if (CommandDataDefault->GotSpacecraftId == 0)
    {
        CommandDataDefault->SpacecraftId = CFE_PSP_SPACECRAFT_ID;
        printf("CFE_PSP: Default Spacecraft ID = %d\n", CFE_PSP_SPACECRAFT_ID);
        CommandDataDefault->GotSpacecraftId = 1;
    }

    if (CommandDataDefault->GotCpuName == 0)
    {
        strncpy(CommandDataDefault->CpuName, CFE_PSP_CPU_NAME, CFE_PSP_CPU_NAME_LENGTH - 1);
        CommandDataDefault->CpuName[CFE_PSP_CPU_NAME_LENGTH - 1] = 0;
        printf("CFE_PSP: Default CPU Name: %s\n", CFE_PSP_CPU_NAME);
        CommandDataDefault->GotCpuName = 1;
    }

    if (CommandDataDefault->GotCfsId == 0)
    {
        strncpy(CommandDataDefault->CfsId, CFE_PSP_CFS_ID, CFE_PSP_CFS_ID_LENGTH - 1);
        CommandDataDefault->CfsId[CFE_PSP_CFS_ID_LENGTH - 1] = 0;
        printf("CFE_PSP: Default cFS ID: %s\n", CFE_PSP_CFS_ID);
        CommandDataDefault->GotCfsId = 1;
    }
}

