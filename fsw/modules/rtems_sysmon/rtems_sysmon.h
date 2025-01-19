/************************************************************************
 * NASA Docket No. GSC-18,719-1, and identified as “core Flight System: Bootes”
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

/**
 * \file
 *
 * Internal header for rtems_sysmon.c
 */

#ifndef RTEMS_SYSMON_H_
#define RTEMS_SYSMON_H_

/********************************************************************
 * Local Defines
 ********************************************************************/
#ifdef OS_MAXIMUM_PROCESSORS
    #define RTEMS_SYSMON_MAX_CPUS  OS_MAXIMUM_PROCESSORS
#else
    #define RTEMS_SYSMON_MAX_CPUS  1
#endif

#define RTEMS_SYSMON_AGGREGATE_SUBSYS   0
#define RTEMS_SYSMON_CPULOAD_SUBSYS     1
#define RTEMS_SYSMON_AGGR_CPULOAD_SUBCH 0
#define RTEMS_SYSMON_SAMPLE_DELAY       1000
#define RTEMS_SYSMON_TASK_PRIORITY      100
#define RTEMS_SYSMON_STACK_SIZE         4096
#define RTEMS_SYSMON_MAX_SCALE          100000

#ifdef DEBUG_BUILD
#define RTEMS_SYSMON_DEBUG(...) OS_printf(__VA_ARGS__)
#else
#define RTEMS_SYSMON_DEBUG(...)
#endif


/********************************************************************
 * Local Type Definitions
 ********************************************************************/
typedef struct rtems_sysmon_cpuload_core
{
    CFE_PSP_IODriver_AdcCode_t avg_load;
    Timestamp_Control last_run_time;
    Timestamp_Control idle_last_uptime;

} rtems_sysmon_cpuload_core_t;

typedef struct rtems_sysmon_cpuload_state
{
    volatile bool is_running;
    volatile bool should_run;

    rtems_id   task_id;
    rtems_name task_name;

    uint8_t    num_cpus;
    rtems_sysmon_cpuload_core_t per_core[RTEMS_SYSMON_MAX_CPUS];

} rtems_sysmon_cpuload_state_t;

typedef struct rtems_sysmon_state
{
    uint32_t                     local_module_id;
    rtems_sysmon_cpuload_state_t cpu_load;
} rtems_sysmon_state_t;


/********************************************************************
 * Local Function Prototypes
 ********************************************************************/
rtems_task rtems_sysmon_Task(rtems_task_argument arg);
void rtems_sysmon_update_stat(rtems_sysmon_cpuload_state_t *state);
bool rtems_cpu_usage_visitor(Thread_Control *the_thread, void *arg);

int32_t rtems_sysmon_Start(rtems_sysmon_cpuload_state_t *state);
int32_t rtems_sysmon_Stop(rtems_sysmon_cpuload_state_t *state);

int32_t rtems_sysmon_aggregate_dispatch(uint32_t CommandCode, uint16_t Subchannel, CFE_PSP_IODriver_Arg_t Arg);
int32_t rtems_sysmon_calc_aggregate_cpu(rtems_sysmon_cpuload_state_t *state, CFE_PSP_IODriver_AdcCode_t *Val);

/* Function that starts up rtems_sysmon driver. */
int32_t rtems_sysmon_DevCmd(uint32_t CommandCode, uint16_t SubsystemId, uint16_t SubchannelId,
                            CFE_PSP_IODriver_Arg_t Arg);


#endif /* RTEMS_SYSMON_H_ */
