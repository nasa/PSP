/************************************************************************
 * NASA Docket No. GSC-18,719-1, and identified as “core Flight System: 
 * Draco
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

/************************************************************************
 * Includes
 ************************************************************************/

#include "cfe_psp.h"

#include "iodriver_impl.h"
#include "iodriver_analog_io.h"
#include <stdarg.h>
#include <spyLib.h>
#include <private/spyLibP.h>

/********************************************************************
 * Local Defines
 ********************************************************************/
#ifdef OS_MAXIMUM_PROCESSORS
    #define VXWORKS_SYSMON_MAX_CPUS  OS_MAXIMUM_PROCESSORS
#else
    #define VXWORKS_SYSMON_MAX_CPUS  1
#endif

#define VXWORKS_SYSMON_AGGREGATE_SUBSYS   0
#define VXWORKS_SYSMON_CPULOAD_SUBSYS     1
#define VXWORKS_SYSMON_AGGR_CPULOAD_SUBCH 0
#define VXWORKS_SYSMON_SAMPLE_DELAY       1000
#define VXWORKS_SYSMON_TASK_PRIORITY      100
#define VXWORKS_SYSMON_STACK_SIZE         4096
#define VXWORKS_AUX_CLOCK_INTERRUPT_FREQ  100  /* Frequency to collect data (interrupts per second) */
#define VXWORKS_SYSMON_MAX_SCALE          100
#define VXWORKS_SYSMON_TASK_NAME          "VXWORKS SYSMON"
#define VXWORKS_SYSMON_MAX_SPY_TASKS      100 /* Max number of tasks to spy on */

#ifdef DEBUG_BUILD
#define VXWORKS_SYSMON_DEBUG(...) OS_printf(__VA_ARGS__)
#else
#define VXWORKS_SYSMON_DEBUG(...)
#endif

/********************************************************************
 * Local Type Definitions
 ********************************************************************/
typedef struct vxworks_sysmon_va_arg
{
    char *name;
    char *placeholder; /* empty */
    int  total_idle_percent;
    int  total_idle_ticks;
    int  idle_percent_since_last_report;
    int  idle_ticks_since_last_report;

} vxworks_sysmon_va_arg_t;

typedef struct vxworks_sysmon_cpuload_core
{
    CFE_PSP_IODriver_AdcCode_t avg_load;

    vxworks_sysmon_va_arg_t idle_state;
} vxworks_sysmon_cpuload_core_t;

typedef struct vxworks_sysmon_cpuload_state
{
    volatile bool is_running;
    volatile bool should_run;

    osal_id_t   task_id;

    uint8_t    num_cpus;

    vxworks_sysmon_cpuload_core_t per_core[VXWORKS_SYSMON_MAX_CPUS];

} vxworks_sysmon_cpuload_state_t;

typedef struct vxworks_sysmon_state
{
    uint32_t                     local_module_id;
    vxworks_sysmon_cpuload_state_t cpu_load;
} vxworks_sysmon_state_t;

/********************************************************************
 * Local Function Prototypes
 ********************************************************************/
static void    vxworks_sysmon_Init(uint32_t local_module_id);
static int32_t vxworks_sysmon_Start(vxworks_sysmon_cpuload_state_t *state);
static int32_t vxworks_sysmon_Stop(vxworks_sysmon_cpuload_state_t *state);

int32_t vxworks_sysmon_aggregate_dispatch(uint32_t CommandCode, uint16_t Subchannel, CFE_PSP_IODriver_Arg_t Arg);
int32_t vxworks_sysmon_calc_aggregate_cpu(vxworks_sysmon_cpuload_state_t *state, CFE_PSP_IODriver_AdcCode_t *Val);

/* Function that starts up vxworks_sysmon driver. */
static int32_t vxworks_sysmon_DevCmd(uint32_t CommandCode, uint16_t SubsystemId, uint16_t SubchannelId,
                                   CFE_PSP_IODriver_Arg_t Arg);

/********************************************************************
 * Global Data
 ********************************************************************/
/* vxworks_sysmon device command that is called by iodriver to start up vxworks_sysmon */
CFE_PSP_IODriver_API_t vxworks_sysmon_DevApi = {.DeviceCommand = vxworks_sysmon_DevCmd};

CFE_PSP_MODULE_DECLARE_IODEVICEDRIVER(vxworks_sysmon);

static vxworks_sysmon_state_t vxworks_sysmon_global;

static const char *vxworks_sysmon_subsystem_names[]  = {"aggregate", "per-cpu", NULL};
static const char *vxworks_sysmon_subchannel_names[] = {"cpu-load", NULL};

/***********************************************************************
 * Global Functions
 ********************************************************************/
void vxworks_sysmon_Init(uint32_t local_module_id)
{
    memset(&vxworks_sysmon_global, 0, sizeof(vxworks_sysmon_global));
    vxworks_sysmon_global.local_module_id = local_module_id;
}

int vxworks_sysmon_update_stat(const char *fmt, ...)
{
    vxworks_sysmon_cpuload_state_t *state = &vxworks_sysmon_global.cpu_load;
    vxworks_sysmon_cpuload_core_t *core_p = &state->per_core[state->num_cpus];

    int curr_load;
    va_list arg;
    memset(&core_p->idle_state, 0, sizeof(vxworks_sysmon_va_arg_t));

    va_start(arg, fmt);
    core_p->idle_state.name = va_arg(arg, char *);

    /* only want IDLE string */
    if(strncmp("IDLE", core_p->idle_state.name, 4) == 0)
    {
        if(state->num_cpus < VXWORKS_SYSMON_MAX_CPUS)
        {
            /*
            ** Example format: 
            ** (* printRtn) (spyFmt2, "IDLE", "", "", "", totalPerCent, spyIdleTicks,
            **               incPerCent, tmpIdleIncTicks);
            **
            ** NAME          ENTRY       TID   PRI  total % (ticks)  delta % (ticks)
            ** --------     --------    -----  ---  ---------------  ---------------
            ** IDLE                                  95% (    7990)   95% (    1998)
            **
            */
            core_p->idle_state.placeholder = va_arg(arg, char *);
            core_p->idle_state.placeholder = va_arg(arg, char *);
            core_p->idle_state.placeholder = va_arg(arg, char *);

            core_p->idle_state.total_idle_percent = va_arg(arg, int);
            core_p->idle_state.total_idle_ticks = va_arg(arg, int);
            core_p->idle_state.idle_percent_since_last_report = va_arg(arg, int);
            core_p->idle_state.idle_ticks_since_last_report = va_arg(arg, int);

            curr_load = VXWORKS_SYSMON_MAX_SCALE - core_p->idle_state.idle_percent_since_last_report;

            if (curr_load >= 100)
            {
                core_p->avg_load = 0xFFFFFF; /* max */
            }
            else if (curr_load <= 0)
            {
                core_p->avg_load = 0;
            }
            else
            {
                core_p->avg_load = (0x1000 * curr_load) / VXWORKS_SYSMON_MAX_SCALE ;
                core_p->avg_load |= (core_p->avg_load << 12); /* Expand from 12->24 bit */
            }

            VXWORKS_SYSMON_DEBUG("CFE_PSP(vxworks_sysmon): load=%06x\n", (unsigned int)core_p->avg_load);
            VXWORKS_SYSMON_DEBUG("Name: %s, Total Percent: %d, Total Ticks: %d, Idle Percent: %d, Idle Ticks: %d\n",
                                 core_p->idle_state.name,
                                 core_p->idle_state.total_idle_percent,
                                 core_p->idle_state.total_idle_ticks,
                                 core_p->idle_state.idle_percent_since_last_report,
                                 core_p->idle_state.idle_ticks_since_last_report);

            state->num_cpus++;

        } /* end of cpu check */
    } /* end of idle check */

    va_end(arg);

    return 0;
}

void vxworks_sysmon_Task(void)
{
    int status;
    vxworks_sysmon_cpuload_state_t *state = &vxworks_sysmon_global.cpu_load;

    /* Initialize */
    spyLibInit(VXWORKS_SYSMON_MAX_SPY_TASKS);
    memset(state->per_core, 0, VXWORKS_SYSMON_MAX_CPUS * sizeof(vxworks_sysmon_cpuload_core_t));

    /* 
    ** Begin collecting data by enabling the auxilary clock interrupts at a frequency of interrupts per 
    ** second  
    */
    status = spyClkStartCommon(VXWORKS_AUX_CLOCK_INTERRUPT_FREQ, (FUNCPTR)OS_printf);
    if (status != OK)
    {
        state->should_run = false;
        state->is_running = false;
        OS_printf("CFE_PSP(vxworks_sysmon): Error Initializing Auxillary Clock: Status %d\n", status);
    }

    while (state->should_run)
    {
        OS_TaskDelay(VXWORKS_SYSMON_SAMPLE_DELAY);

        state->num_cpus = 0;
        spyReportCommon( (FUNCPTR)vxworks_sysmon_update_stat);
    }

    spyClkStopCommon(); /* Disable auxillary clock interrupts */

}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * vxworks_sysmon_Start()
 * ------------------------------------------------------
 *  Starts the cpu load watcher function
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
static int32_t vxworks_sysmon_Start(vxworks_sysmon_cpuload_state_t *state)
{
    uint32_t  StatusCode;

    if (state->is_running)
    {
        /* already running, nothing to do */
        StatusCode = CFE_PSP_SUCCESS;
    }
    else
    {
        /* start clean */
        memset(state, 0, sizeof(*state));
        state->should_run = true;
        StatusCode = OS_TaskCreate(&state->task_id, 
                                   VXWORKS_SYSMON_TASK_NAME, 
                                   vxworks_sysmon_Task,
                                   NULL, 
                                   VXWORKS_SYSMON_STACK_SIZE, 
                                   VXWORKS_SYSMON_TASK_PRIORITY, 
                                   0);
        if(StatusCode !=  OS_SUCCESS)
        {
            perror("vxworks_task_create()");
            StatusCode = CFE_PSP_ERROR;
            state->should_run = false;
        }
        else
        {

            OS_printf("CFE_PSP(VXWORKS_SYSMON): Started CPU utilization monitoring\n");
            state->is_running = true;
            StatusCode        = CFE_PSP_SUCCESS;
        } 
    }
    return StatusCode;
}

int32_t vxworks_sysmon_Stop(vxworks_sysmon_cpuload_state_t *state)
{
    if (state->is_running)
    {
        state->should_run = false;
        state->is_running = false;
        OS_TaskDelete(state->task_id);

        spyClkStopCommon(); /* Disable auxillary clock interrupts */
    }

    return CFE_PSP_SUCCESS;
}

int32_t vxworks_sysmon_calc_aggregate_cpu(vxworks_sysmon_cpuload_state_t *state, CFE_PSP_IODriver_AdcCode_t *Val)
{

    uint8_t  cpu;
    uint32_t sum;

    sum = 0;
    for (cpu = 0; cpu < VXWORKS_SYSMON_MAX_CPUS; cpu++ )
    {
        sum += state->per_core[cpu].avg_load; 
    }

    sum /= VXWORKS_SYSMON_MAX_CPUS;
    *Val = sum;

    VXWORKS_SYSMON_DEBUG("CFE_PSP(vxworks_sysmon): Aggregate CPU load=%08X\n", (unsigned int)sum);

    return CFE_PSP_SUCCESS;
}

int32_t vxworks_sysmon_aggregate_dispatch(uint32_t CommandCode, uint16_t Subchannel, CFE_PSP_IODriver_Arg_t Arg)
{
    int32_t                       StatusCode;
    vxworks_sysmon_cpuload_state_t *state;

    /* There is just one global cpuload object */
    state      = &vxworks_sysmon_global.cpu_load;
    
    StatusCode = CFE_PSP_ERROR_NOT_IMPLEMENTED;
    switch (CommandCode)
    {
        case CFE_PSP_IODriver_NOOP:
        case CFE_PSP_IODriver_ANALOG_IO_NOOP:
            VXWORKS_SYSMON_DEBUG("CFE_PSP(vxworks_sysmon): Noop \n");
            break;
        case CFE_PSP_IODriver_SET_RUNNING: 
        {
            if (Arg.U32)
            {
                StatusCode = vxworks_sysmon_Start(state);
            }
            else
            {
                StatusCode = vxworks_sysmon_Stop(state);
            }
            break;
        }
        case CFE_PSP_IODriver_GET_RUNNING:                                    
        {
            StatusCode = state->is_running;
            break;
        }
        case CFE_PSP_IODriver_SET_CONFIGURATION: /**< const string argument (device-dependent content) */
        case CFE_PSP_IODriver_GET_CONFIGURATION: /**< void * argument (device-dependent content) */
        {
            /* not implemented for now */
            break;
        }
        case CFE_PSP_IODriver_LOOKUP_SUBSYSTEM: /**< const char * argument, looks up name and returns positive
                                                    value for subsystem number, negative value for error */
        {
            uint16_t i;

            for (i = 0; vxworks_sysmon_subsystem_names[i] != NULL; ++i)
            {
                if (strcmp(Arg.ConstStr, vxworks_sysmon_subsystem_names[i]) == 0)
                {
                    StatusCode = i;
                    break;
                }
            }

            break;
        }
        case CFE_PSP_IODriver_LOOKUP_SUBCHANNEL: /**< const char * argument, looks up name and returns positive
                                                    value for channel number, negative value for error */
        {
            uint16_t i;

            for (i = 0; vxworks_sysmon_subchannel_names[i] != NULL; ++i)
            {
                if (strcmp(Arg.ConstStr, vxworks_sysmon_subchannel_names[i]) == 0)
                {
                    StatusCode = i;
                    break;
                }
            }

            break;
        }
        case CFE_PSP_IODriver_QUERY_DIRECTION: /**< CFE_PSP_IODriver_Direction_t argument */
        {
            CFE_PSP_IODriver_Direction_t *DirPtr = (CFE_PSP_IODriver_Direction_t *)Arg.Vptr;
            if (DirPtr != NULL)
            {
                *DirPtr    = CFE_PSP_IODriver_Direction_INPUT_ONLY;
                StatusCode = CFE_PSP_SUCCESS;
            }
            break;
        }
        case CFE_PSP_IODriver_ANALOG_IO_READ_CHANNELS:
        {
            CFE_PSP_IODriver_AnalogRdWr_t *RdWr = Arg.Vptr;

            if (RdWr->NumChannels == 1 && Subchannel == VXWORKS_SYSMON_AGGR_CPULOAD_SUBCH)
            {
                StatusCode = vxworks_sysmon_calc_aggregate_cpu(state, RdWr->Samples);
            }
            break;
        }
        default:
            break;
    }

    return StatusCode;
}

int32_t vxworks_sysmon_cpu_load_dispatch(uint32_t CommandCode, uint16_t Subchannel, CFE_PSP_IODriver_Arg_t Arg)
{
    int32_t                       StatusCode;
    vxworks_sysmon_cpuload_state_t *state;

    /* There is just one global cpuload object */
    state      = &vxworks_sysmon_global.cpu_load;
    StatusCode = CFE_PSP_ERROR_NOT_IMPLEMENTED;
    switch (CommandCode)
    {
        case CFE_PSP_IODriver_NOOP:
        case CFE_PSP_IODriver_ANALOG_IO_NOOP:
        {
            /* NO-OP should return success -
             * This is a required opcode as "generic" clients may use it to
             * determine if a certain set of opcodes are supported or not
             */
            StatusCode = CFE_PSP_SUCCESS;
            break;
        }
        case CFE_PSP_IODriver_ANALOG_IO_READ_CHANNELS:
        {
            CFE_PSP_IODriver_AnalogRdWr_t *RdWr = Arg.Vptr;
            uint32_t                       ch;

            if (Subchannel < VXWORKS_SYSMON_MAX_CPUS && (Subchannel + RdWr->NumChannels) <= VXWORKS_SYSMON_MAX_CPUS)
            {
                for (ch = Subchannel; ch < (Subchannel + RdWr->NumChannels); ++ch)
                {
                    RdWr->Samples[ch] = state->per_core[ch].avg_load;
                }
            }

            break;
        }
        default:
            break;
    }

    return StatusCode;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*    vxworks_sysmon_DevCmd()                               */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * \brief Main entry point for API.
 *
 * This function is called through iodriver to invoke the vxworks_sysmon module.
 *
 * \par Assumptions, External Events, and Notes:
 *          None
 *
 * \param[in] CommandCode  The CFE_PSP_IODriver_xxx command.
 * \param[in] SubsystemId  The monitor subsystem identifier
 * \param[in] SubchannelId The monitor subchannel identifier
 * \param[in] Arg          The arguments for the corresponding command.
 *
 * \returns Status code
 * \retval #CFE_PSP_SUCCESS if successful
 */
int32_t vxworks_sysmon_DevCmd(uint32_t CommandCode, uint16_t SubsystemId, uint16_t SubchannelId,
                            CFE_PSP_IODriver_Arg_t Arg)
{
    int32_t StatusCode;

    StatusCode = CFE_PSP_ERROR_NOT_IMPLEMENTED;
    switch (SubsystemId)
    {
        case VXWORKS_SYSMON_AGGREGATE_SUBSYS:
            StatusCode = vxworks_sysmon_aggregate_dispatch(CommandCode, SubchannelId, Arg);
            break;
        case VXWORKS_SYSMON_CPULOAD_SUBSYS:
            StatusCode = vxworks_sysmon_cpu_load_dispatch(CommandCode, SubchannelId, Arg);
            break;
        default:
            /* not implemented */
            break;
    }

    return StatusCode;
}
