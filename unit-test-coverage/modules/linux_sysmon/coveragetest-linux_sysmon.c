/************************************************************************
 * NASA Docket No. GSC-18,719-1, and identified as “core Flight System: Bootes”
 *
 * Copyright (c) 2020 United States Government as represented by the
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

/*
 *
 *    Copyright (c) 2020, United States government as represented by the
 *    administrator of the National Aeronautics Space Administration.
 *    All rights reserved. This software was created at NASA Goddard
 *    Space Flight Center pursuant to government contracts.
 *
 *    This is governed by the NASA Open Source Agreement and may be used,
 *    distributed and modified only according to the terms of that agreement.
 *
 */

/**
 * \file
 * \ingroup  modules
 *
 * Coverage test for VxWorks timebase module implementation
 */

#include "utassert.h"
#include "utstubs.h"
#include "uttest.h"

#include "cfe_psp.h"
#include "cfe_psp_config.h"
#include "cfe_psp_module.h"

#include "PCS_arch_ppc_vxPpcLib.h"

/*
 * Reference to the API entry point for the module
 */
extern CFE_PSP_ModuleApi_t CFE_PSP_timebase_vxworks_API;

const CFE_PSP_ModuleApi_t *TgtAPI = &CFE_PSP_timebase_vxworks_API;

UT_PSP_TimeBase_VxWorks_TestConfig_t UT_PSP_TIMEBASE_VXWORKS_TESTCONFIG;

typedef struct
{
    uint32 u;
    uint32 l;
} PSP_VxWorks_TimeBaseVal_t;

void ModuleTest_ResetState(void)
{
    memset(&UT_PSP_TIMEBASE_VXWORKS_TESTCONFIG, 0, sizeof(UT_PSP_TIMEBASE_VXWORKS_TESTCONFIG));
}

int32 UTHOOK_vxTimeBaseGet(void *UserObj, int32 StubRetcode, uint32 CallCount, const UT_StubContext_t *Context)
{
    PSP_VxWorks_TimeBaseVal_t *val = UserObj;
    uint32 *                   u   = UT_Hook_GetArgValueByName(Context, "u", uint32 *);
    uint32 *                   l   = UT_Hook_GetArgValueByName(Context, "l", uint32 *);

    *u = val->u;
    *l = val->l;

    return StubRetcode;
}

void Test_Nominal(void)
{
    OS_time_t                 OsTime;
    PSP_VxWorks_TimeBaseVal_t VxTime;

    memset(&OsTime, 0, sizeof(OsTime));

    /* Nominal test with a simple 1:1 ratio */
    UT_PSP_TIMEBASE_VXWORKS_TESTCONFIG.PeriodNumerator   = 1;
    UT_PSP_TIMEBASE_VXWORKS_TESTCONFIG.PeriodDenominator = 1;
    TgtAPI->Init(0);
    UtAssert_UINT32_EQ(CFE_PSP_GetTimerTicksPerSecond(), 1000000000);

    /* Check operation of CFE_PSP_GetTime() */
    UT_SetHookFunction(UT_KEY(PCS_vxTimeBaseGet), UTHOOK_vxTimeBaseGet, &VxTime);
    VxTime.u = 0;
    VxTime.l = 10000;
    CFE_PSP_GetTime(&OsTime);

    UtAssert_UINT32_EQ(OS_TimeGetNanosecondsPart(OsTime), 10000);
}

void Test_Non_Reducible(void)
{
    OS_time_t                 OsTime;
    PSP_VxWorks_TimeBaseVal_t VxTime;
    int64                     TestTime;

    memset(&OsTime, 0, sizeof(OsTime));

    /* Use an oddball ratio of of some primes, will not be reducible */
    /* Ratio is 43*3 / 53*2  => 129/106 */
    /* This translates to about ~1.217ns per tick */
    UT_PSP_TIMEBASE_VXWORKS_TESTCONFIG.PeriodNumerator   = 43 * 3;
    UT_PSP_TIMEBASE_VXWORKS_TESTCONFIG.PeriodDenominator = 53 * 2;
    TgtAPI->Init(0);
    UtAssert_UINT32_EQ(CFE_PSP_GetTimerTicksPerSecond(), 821705426);

    /*
     * Check operation of CFE_PSP_GetTime()
     *
     * This test requires that the conversion uses the actual ratio,
     * otherwise a rounding error will be noticed.
     * For example:
     * Conversion using 1.217ns/tick yields 52269758 usec (wrong).
     * Conversion using actual ratio yields 52268947 usec.
     */

    UT_SetHookFunction(UT_KEY(PCS_vxTimeBaseGet), UTHOOK_vxTimeBaseGet, &VxTime);
    VxTime.u = 10;
    VxTime.l = 5000;
    CFE_PSP_GetTime(&OsTime);

    TestTime = OS_TimeGetTotalMicroseconds(OsTime);
    UtAssert_True(TestTime == 52268947, "CFE_PSP_GetTime() Microseconds (%lld) == 52268947", (long long)TestTime);
}

void Test_Reducible_1(void)
{
    OS_time_t                 OsTime;
    PSP_VxWorks_TimeBaseVal_t VxTime;
    int64                     TestTime;

    memset(&OsTime, 0, sizeof(OsTime));

    /* Test with a ratio that is also 1:1, but can be reduced */
    UT_PSP_TIMEBASE_VXWORKS_TESTCONFIG.PeriodNumerator   = 1000;
    UT_PSP_TIMEBASE_VXWORKS_TESTCONFIG.PeriodDenominator = 1000;
    TgtAPI->Init(0);
    UtAssert_UINT32_EQ(CFE_PSP_GetTimerTicksPerSecond(), 1000000000);

    /*
     * Check operation of CFE_PSP_GetTime()
     *
     * Externally calculated value should be 10376293541461622 usec.
     * If overflow occurs then value will be wrong.
     */
    UT_SetHookFunction(UT_KEY(PCS_vxTimeBaseGet), UTHOOK_vxTimeBaseGet, &VxTime);
    VxTime.u = 0x90000000; /* nearing 64-bit limit */
    VxTime.l = 0;
    CFE_PSP_GetTime(&OsTime);

    TestTime = OS_TimeGetTotalMicroseconds(OsTime);
    UtAssert_True(TestTime == 10376293541461622, "CFE_PSP_GetTime() Microseconds (%lld) == 10376293541461622",
                  (long long)TestTime);
}

void Test_Reducible_2(void)
{
    OS_time_t                 OsTime;
    PSP_VxWorks_TimeBaseVal_t VxTime;
    int64                     TestTime;

    memset(&OsTime, 0, sizeof(OsTime));

    /* Test with a ratio that can be reduced */
    /* Final reduced ratio should be 12:5 with 100ns OS ticks */
    UT_PSP_TIMEBASE_VXWORKS_TESTCONFIG.PeriodNumerator   = 84000;
    UT_PSP_TIMEBASE_VXWORKS_TESTCONFIG.PeriodDenominator = 350;
    TgtAPI->Init(0);
    UtAssert_UINT32_EQ(CFE_PSP_GetTimerTicksPerSecond(), 4166666);

    /*
     * Check operation of CFE_PSP_GetTime()
     *
     * Externally calculated value should be 276701161105643274 usec.
     * If overflow occurs then value will be wrong.
     */
    UT_SetHookFunction(UT_KEY(PCS_vxTimeBaseGet), UTHOOK_vxTimeBaseGet, &VxTime);
    VxTime.u = 0x10000000; /* nearing 64-bit limit */
    VxTime.l = 0;
    CFE_PSP_GetTime(&OsTime);

    TestTime = OS_TimeGetTotalMicroseconds(OsTime);
    UtAssert_True(TestTime == 276701161105643274, "CFE_PSP_GetTime() Microseconds(%lld) == 276701161105643274",
                  (long long)TestTime);
}

void Test_Rollover(void)
{
    /* This function always returns 0 */
    UtAssert_UINT32_EQ(CFE_PSP_GetTimerLow32Rollover(), 0);
}

/******************************************************************************
**
**  Purpose:
**    Provides a common interface to system timebase. This routine
**    is in the BSP because it is sometimes implemented in hardware and
**    sometimes taken care of by the RTOS.
**
**  Arguments:
**
**  Return:
**  Timebase register value
*/
void Test_Get_Timebase(void)
{
    PSP_VxWorks_TimeBaseVal_t VxTime;
    uint32                    tbu;
    uint32                    tbl;

    /* The value from vxTimeBaseGet() should be passed through unchanged */
    UT_SetHookFunction(UT_KEY(PCS_vxTimeBaseGet), UTHOOK_vxTimeBaseGet, &VxTime);
    VxTime.u = 0x00112233;
    VxTime.l = 0x44556677;

    CFE_PSP_Get_Timebase(&tbu, &tbl);

    UtAssert_UINT32_EQ(tbu, VxTime.u);
    UtAssert_UINT32_EQ(tbl, VxTime.l);
}

/*
 * Macro to add a test case to the list of tests to execute
 */
#define ADD_TEST(test) UtTest_Add(test, ModuleTest_ResetState, NULL, #test)

/*
 * Register the test cases to execute with the unit test tool
 */
void UtTest_Setup(void)
{
    ADD_TEST(Test_Nominal);
    ADD_TEST(Test_Non_Reducible);
    ADD_TEST(Test_Reducible_1);
    ADD_TEST(Test_Reducible_2);
    ADD_TEST(Test_Rollover);
    ADD_TEST(Test_Get_Timebase);
}
/***********************************************************************
 *  Copyright (c) 2017, United States government as represented by the
 *  administrator of the National Aeronautics and Space Administration.
 *  All rights reserved. This software was created at NASA Glenn
 *  Research Center pursuant to government contracts.
 *
 *  \file linux_sysmon.c
 *
 ***********************************************************************/

/*
 * NOTE: This relies on the Linux Kernel sched stats via the /proc filesystem.
 * Documented here: https://docs.kernel.org/scheduler/sched-stats.html
 */

/************************************************************************
 * Includes
 ************************************************************************/

#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>
#include <poll.h>

#include "cfe_psp.h"
#include "cfe_psp_module.h"
#include "osapi-clock.h"

#include "iodriver_impl.h"
#include "iodriver_analog_io.h"

/********************************************************************
 * Local Defines
 ********************************************************************/

#define LINUX_SYSMON_AGGREGATE_SUBSYS   0
#define LINUX_SYSMON_CPULOAD_SUBSYS     1
#define LINUX_SYSMON_AGGR_CPULOAD_SUBCH 0
#define LINUX_SYSMON_MAX_CPUS           128
#define LINUX_SYSMON_SAMPLE_DELAY       30

#ifdef DEBUG_BUILD
#define LINUX_SYSMON_DEBUG(...) OS_printf(__VA_ARGS__)
#else
#define LINUX_SYSMON_DEBUG(...)
#endif

/********************************************************************
 * Local Type Definitions
 ********************************************************************/

typedef struct linux_sysmon_cpuload_core
{
    CFE_PSP_IODriver_AdcCode_t avg_load;
    unsigned long              last_run_time;
} linux_sysmon_cpuload_core_t;

typedef struct linux_sysmon_cpuload_state
{
    volatile bool is_running;
    volatile bool should_run;

    uint8_t   num_cpus;
    pthread_t task_id;
    int       dev_fd;
    uint32_t  num_samples;
    uint64_t  last_sample_time;

    linux_sysmon_cpuload_core_t per_core[LINUX_SYSMON_MAX_CPUS];
} linux_sysmon_cpuload_state_t;

typedef struct linux_sysmon_state
{
    uint32_t                     local_module_id;
    linux_sysmon_cpuload_state_t cpu_load;
} linux_sysmon_state_t;

/********************************************************************
 * Local Function Prototypes
 ********************************************************************/

static void *  linux_sysmon_Task(void *arg);
static int32_t linux_sysmon_Start(linux_sysmon_cpuload_state_t *state);
static int32_t linux_sysmon_Stop(linux_sysmon_cpuload_state_t *state);
static void    linux_sysmon_Init(uint32_t local_module_id);

/* Function that starts up linux_sysmon driver. */
static int32_t linux_sysmon_DevCmd(uint32_t CommandCode, uint16_t SubsystemId, uint16_t SubchannelId,
                                   CFE_PSP_IODriver_Arg_t Arg);

/********************************************************************
 * Global Data
 ********************************************************************/

/* linux_sysmon device command that is called by iodriver to start up linux_sysmon */
CFE_PSP_IODriver_API_t linux_sysmon_DevApi = {.DeviceCommand = linux_sysmon_DevCmd};

CFE_PSP_MODULE_DECLARE_IODEVICEDRIVER(linux_sysmon);

static linux_sysmon_state_t linux_sysmon_global;

static const char *linux_sysmon_subsystem_names[]  = {"aggregate", "per-cpu", NULL};
static const char *linux_sysmon_subchannel_names[] = {"cpu-load", NULL};

/***********************************************************************
 * Global Functions
 ********************************************************************/

void linux_sysmon_Init(uint32_t local_module_id)
{
    memset(&linux_sysmon_global, 0, sizeof(linux_sysmon_global));

    linux_sysmon_global.local_module_id = local_module_id;
}

void linux_sysmon_read_cpuuse_line(const char *line_data, unsigned int *cpu_num, unsigned long *run_time)
{
    unsigned long value;
    const char *  val_end;
    int           val_count;

    /* each "cpu" line contains the cpu number followed by 9 values */
    for (val_count = 0; val_count < 10 && *line_data != 0; ++val_count)
    {
        while (isspace((unsigned char)*line_data))
        {
            ++line_data;
        }
        value = strtoul(line_data, (char **)&val_end, 10);
        if (val_end == line_data)
        {
            /* not a number, something went wrong */
            break;
        }

        line_data = val_end;

        switch (val_count)
        {
            case 0: /* this is the cpu number */
                *cpu_num = value;
                break;

            case 7: /* this is the number of nanoseconds spent executing instructions on this CPU */
                *run_time = value;
                break;

            default: /* don't care about this one */
                break;
        }
    }
}

void linux_sysmon_update_schedstat(linux_sysmon_cpuload_state_t *state, int elapsed_ms)
{
    unsigned int  cpu_time_ms;
    unsigned int  cpu_num;
    unsigned int  highest_cpu_num;
    unsigned long run_time;
    char          line_data[256];
    size_t        line_size;
    ssize_t       line_rdsz;
    char *        eol_p;

    linux_sysmon_cpuload_core_t *core_p;

    line_size       = 0;
    highest_cpu_num = 0;

    /* Reset to beginning of file to re-read it */
    lseek(state->dev_fd, 0, SEEK_SET);

    while (true)
    {
        line_rdsz = read(state->dev_fd, &line_data[line_size], sizeof(line_data) - line_size);
        if (line_rdsz <= 0)
        {
            /* error (not expected) or EOF, stop reading */
            break;
        }

        /* check for newline char */
        eol_p = memchr(&line_data[line_size], '\n', line_rdsz);
        line_size += line_rdsz;

        while (eol_p != NULL)
        {
            *eol_p = 0;
            ++eol_p;

            if (strncmp("cpu", line_data, 3) == 0)
            {
                cpu_num  = -1;
                run_time = 0;
                linux_sysmon_read_cpuuse_line(&line_data[3], &cpu_num, &run_time);

                if (cpu_num < LINUX_SYSMON_MAX_CPUS)
                {
                    core_p = &state->per_core[cpu_num];
                    if (cpu_num > highest_cpu_num)
                    {
                        highest_cpu_num = cpu_num;
                    }
                }
                else
                {
                    core_p = NULL;
                }

                if (core_p != NULL)
                {
                    cpu_time_ms =
                        OS_TimeGetTotalMilliseconds(OS_TimeFromTotalNanoseconds(run_time - core_p->last_run_time));
                    core_p->last_run_time = run_time;
                    if (cpu_time_ms >= elapsed_ms)
                    {
                        core_p->avg_load = 0xFFFFFF; /* max */
                    }
                    else if (elapsed_ms == 0)
                    {
                        core_p->avg_load = 0;
                    }
                    else
                    {
                        core_p->avg_load = (0x1000 * cpu_time_ms) / elapsed_ms;
                        core_p->avg_load |= (core_p->avg_load << 12); /* Expand from 12->24 bit */
                    }
                    LINUX_SYSMON_DEBUG("CFE_PSP(linux_sysmon): CPU%u time_ms=%u ms, load=%06x\n", cpu_num, cpu_time_ms,
                                       (unsigned int)core_p->avg_load);
                }
            }

            line_rdsz = eol_p - &line_data[0];
            if (line_rdsz < line_size)
            {
                memmove(line_data, eol_p, line_size - line_rdsz);
                line_size -= line_rdsz;
            }
            else
            {
                line_size = 0;
            }

            eol_p = memchr(line_data, '\n', line_size);
        }

        if (line_size >= sizeof(line_data))
        {
            /* not supposed to happen, drop data */
            OS_printf("CFE_PSP(linux_sysmon): malformed data from /proc/schedstat\n");
            break;
        }
    }

    state->num_cpus = 1 + highest_cpu_num;
}

void *linux_sysmon_Task(void *arg)
{
    linux_sysmon_cpuload_state_t *state = arg;

    OS_time_t     last_sample;
    OS_time_t     curr_sample;
    OS_time_t     next_sample;
    int           msec_diff;
    struct pollfd pfd;

    CFE_PSP_GetTime(&next_sample);
    curr_sample = next_sample;
    memset(&pfd, 0, sizeof(pfd));

    linux_sysmon_update_schedstat(state, 0);

    while (state->should_run)
    {
        next_sample = OS_TimeAdd(next_sample, OS_TimeFromTotalSeconds(LINUX_SYSMON_SAMPLE_DELAY));
        msec_diff   = OS_TimeGetTotalMilliseconds(OS_TimeSubtract(next_sample, curr_sample));
        if (msec_diff > 0)
        {
            poll(&pfd, 0, msec_diff);
        }

        last_sample = curr_sample;
        CFE_PSP_GetTime(&curr_sample);
        msec_diff = OS_TimeGetTotalMilliseconds(OS_TimeSubtract(curr_sample, last_sample));
        linux_sysmon_update_schedstat(state, msec_diff);
    }

    return NULL;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * linux_sysmon_Start()
 * ------------------------------------------------------
 *  Starts the cpu load watcher function
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int32_t linux_sysmon_Start(linux_sysmon_cpuload_state_t *state)
{
    int32_t StatusCode;
    int32_t DelayCount;

    DelayCount = 0;
    if (state->is_running)
    {
        /* already running, nothing to do */
        StatusCode = CFE_PSP_SUCCESS;
    }
    else
    {
        /* start clean */
        memset(state, 0, sizeof(*state));
        StatusCode = CFE_PSP_ERROR;

        state->dev_fd = open("/proc/schedstat", O_RDONLY);
        if (state->dev_fd < 0)
        {
            perror("open(/proc/schedstat)");
        }
        else
        {
            state->should_run = true;
            if (pthread_create(&state->task_id, NULL, linux_sysmon_Task, state) < 0)
            {
                perror("pthread_create()");

                /* Clean up */
                state->should_run = false;
                close(state->dev_fd);
            }
            else
            {
                /* wait for the "num_cpus" to become nonzero, this should be
                 * initialized in the first sample taken by the worker task */
                while (state->num_cpus == 0 && DelayCount < 100000000 /*jphfix*/)
                {
                    ++DelayCount;
                    OS_TaskDelay(10);
                }

                if (state->num_cpus == 0)
                {
                    OS_printf("CFE_PSP(Linux_SysMon): Failed to detect number of CPUs\n");

                    /* Clean up */
                    state->should_run = false;
                    pthread_cancel(state->task_id);
                    pthread_join(state->task_id, NULL);
                    close(state->dev_fd);
                }
                else
                {
                    OS_printf("CFE_PSP(Linux_SysMon): Started CPU utilization monitoring on %u CPU(s)\n",
                              (unsigned int)state->num_cpus);

                    StatusCode        = CFE_PSP_SUCCESS;
                    state->is_running = true;
                }
            }
        }
    }

    return StatusCode;
}

int32_t linux_sysmon_Stop(linux_sysmon_cpuload_state_t *state)
{
    if (state->is_running)
    {
        state->should_run = false;
        state->is_running = false;
        pthread_cancel(state->task_id);
        pthread_join(state->task_id, NULL);
        close(state->dev_fd);
    }

    return CFE_PSP_SUCCESS;
}

int32_t linux_sysmon_calc_aggregate_cpu(linux_sysmon_cpuload_state_t *state, CFE_PSP_IODriver_AdcCode_t *Val)
{
    uint8_t  cpu;
    uint32_t sum;

    sum = 0;
    for (cpu = 0; cpu < state->num_cpus; ++cpu)
    {
        sum += state->per_core[cpu].avg_load;
    }

    if (cpu == 0)
    {
        *Val = 0;
        return CFE_PSP_ERROR;
    }

    /* average of all cpus */
    sum /= cpu;
    LINUX_SYSMON_DEBUG("CFE_PSP(linux_sysmon): Aggregate CPU load=%06x\n", (unsigned int)sum);
    *Val = sum;

    return CFE_PSP_SUCCESS;
}

int32_t linux_sysmon_aggregate_dispatch(uint32_t CommandCode, uint16_t Subchannel, CFE_PSP_IODriver_Arg_t Arg)
{
    int32_t                       StatusCode;
    linux_sysmon_cpuload_state_t *state;

    /* There is just one global cpuload object */
    state      = &linux_sysmon_global.cpu_load;
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
        /* Start/stop opcodes */
        case CFE_PSP_IODriver_SET_RUNNING: /**< int32_t argument, 0=stop 1=start device */
        {
            if (Arg.U32)
            {
                StatusCode = linux_sysmon_Start(state);
            }
            else
            {
                StatusCode = linux_sysmon_Stop(state);
            }
            break;
        }
        case CFE_PSP_IODriver_GET_RUNNING: /**< no argument, returns positive nonzero (true) if running and zero (false)
                                              if stopped, negative on error */
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

            for (i = 0; linux_sysmon_subsystem_names[i] != NULL; ++i)
            {
                if (strcmp(Arg.ConstStr, linux_sysmon_subsystem_names[i]) == 0)
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

            for (i = 0; linux_sysmon_subchannel_names[i] != NULL; ++i)
            {
                if (strcmp(Arg.ConstStr, linux_sysmon_subchannel_names[i]) == 0)
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

            if (RdWr->NumChannels == 1 && Subchannel == LINUX_SYSMON_AGGR_CPULOAD_SUBCH)
            {
                StatusCode = linux_sysmon_calc_aggregate_cpu(state, RdWr->Samples);
            }
            break;
        }
        default:
            break;
    }

    return StatusCode;
}

int32_t linux_sysmon_cpu_load_dispatch(uint32_t CommandCode, uint16_t Subchannel, CFE_PSP_IODriver_Arg_t Arg)
{
    int32_t                       StatusCode;
    linux_sysmon_cpuload_state_t *state;

    /* There is just one global cpuload object */
    state      = &linux_sysmon_global.cpu_load;
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

            if (Subchannel < state->num_cpus && (Subchannel + RdWr->NumChannels) <= state->num_cpus)
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
/*    linux_sysmon_DevCmd()                                         */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * \brief Main entry point for API.
 *
 * This function is called through iodriver to invoke the linux_sysmon module.
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
int32_t linux_sysmon_DevCmd(uint32_t CommandCode, uint16_t SubsystemId, uint16_t SubchannelId,
                            CFE_PSP_IODriver_Arg_t Arg)
{
    int32_t StatusCode;

    StatusCode = CFE_PSP_ERROR_NOT_IMPLEMENTED;
    switch (SubsystemId)
    {
        case LINUX_SYSMON_AGGREGATE_SUBSYS:
            StatusCode = linux_sysmon_aggregate_dispatch(CommandCode, SubchannelId, Arg);
            break;
        case LINUX_SYSMON_CPULOAD_SUBSYS:
            StatusCode = linux_sysmon_cpu_load_dispatch(CommandCode, SubchannelId, Arg);
            break;
        default:
            /* not implemented */
            break;
    }

    return StatusCode;
}
