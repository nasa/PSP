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
/*
 * Based on RTEMS5 cpuusagereport.c
 */

/************************************************************************
 * Includes
 ************************************************************************/

#include "cfe_psp.h"

#include "iodriver_impl.h"
#include "iodriver_analog_io.h"

#include <rtems.h>
#include <rtems/cpuuse.h>
#include <rtems/score/threadimpl.h>
#include <rtems/rtems/tasks.h>

/********************************************************************
 * Local Defines
 ********************************************************************/
#ifdef OS_MAXIMUM_PROCESSORS
#define RTEMS_SYSMON_MAX_CPUS OS_MAXIMUM_PROCESSORS
#else
#define RTEMS_SYSMON_MAX_CPUS 1
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
    Timestamp_Control          last_run_time;
    Timestamp_Control          idle_last_uptime;

} rtems_sysmon_cpuload_core_t;

typedef struct rtems_sysmon_cpuload_state
{
    volatile bool is_running;
    volatile bool should_run;

    rtems_id   task_id;
    rtems_name task_name;

    uint8_t                     num_cpus;
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
static void    rtems_sysmon_Init(uint32_t local_module_id);
static int32_t rtems_sysmon_Start(rtems_sysmon_cpuload_state_t *state);
static int32_t rtems_sysmon_Stop(rtems_sysmon_cpuload_state_t *state);

int32_t rtems_sysmon_aggregate_dispatch(uint32_t CommandCode, uint16_t Subchannel, CFE_PSP_IODriver_Arg_t Arg);
int32_t rtems_sysmon_calc_aggregate_cpu(rtems_sysmon_cpuload_state_t *state, CFE_PSP_IODriver_AdcCode_t *Val);

/* Function that starts up rtems_sysmon driver. */
static int32_t rtems_sysmon_DevCmd(uint32_t CommandCode, uint16_t SubsystemId, uint16_t SubchannelId,
                                   CFE_PSP_IODriver_Arg_t Arg);

/********************************************************************
 * Global Data
 ********************************************************************/
/* This object provides the uptime timestamp at the last CPU usage reset. */
extern Timestamp_Control CPU_usage_Uptime_at_last_reset;

/* rtems_sysmon device command that is called by iodriver to start up rtems_sysmon */
CFE_PSP_IODriver_API_t rtems_sysmon_DevApi = {.DeviceCommand = rtems_sysmon_DevCmd};

CFE_PSP_MODULE_DECLARE_IODEVICEDRIVER(rtems_sysmon);

static rtems_sysmon_state_t rtems_sysmon_global;

static const char *rtems_sysmon_subsystem_names[]  = {"aggregate", "per-cpu", NULL};
static const char *rtems_sysmon_subchannel_names[] = {"cpu-load", NULL};

/***********************************************************************
 * Global Functions
 ********************************************************************/
void rtems_sysmon_Init(uint32_t local_module_id)
{
    memset(&rtems_sysmon_global, 0, sizeof(rtems_sysmon_global));

    rtems_sysmon_global.local_module_id = local_module_id;
}

static bool rtems_cpu_usage_vistor(Thread_Control *the_thread, void *arg)
{
    rtems_sysmon_cpuload_state_t *state  = (rtems_sysmon_cpuload_state_t *)arg;
    rtems_sysmon_cpuload_core_t * core_p = &state->per_core[state->num_cpus];

    Timestamp_Control uptime_at_last_calc      = core_p->last_run_time;
    Timestamp_Control idle_uptime_at_last_calc = core_p->idle_last_uptime;
    Timestamp_Control current_uptime;
    Timestamp_Control idle_task_uptime;
    Timestamp_Control idle_uptime_elapsed;
    Timestamp_Control total_elapsed;

    char     name[38];
    uint32_t ival;
    uint32_t fval;
    bool     status = false;

    _Thread_Get_name(the_thread, name, sizeof(name));
    if (strncmp("IDLE", name, 4) == 0)
    {
#if __RTEMS_MAJOR__ == 5
        _Thread_Get_CPU_time_used(the_thread, &idle_task_uptime);
#else /* RTEMS 6 */
        idle_task_uptime = _Thread_Get_CPU_time_used_after_last_reset(the_thread);
#endif

        _TOD_Get_uptime(&current_uptime);
        _Timestamp_Subtract(&idle_uptime_at_last_calc, &idle_task_uptime, &idle_uptime_elapsed);
        _Timestamp_Subtract(&uptime_at_last_calc, &current_uptime, &total_elapsed);
        _Timestamp_Divide(&idle_uptime_elapsed, &total_elapsed, &ival,
                          &fval); /* ival - points to the integer portion */
                                  /* fval - points to the thousandths of percentage */

        core_p->last_run_time    = current_uptime;
        core_p->idle_last_uptime = idle_task_uptime;

        if (ival >= 100)
        {
            core_p->avg_load = 0xFFFFFF; /* max */
        }
        else if (total_elapsed == 0)
        {
            core_p->avg_load = 0;
        }
        else
        {
            while (fval > 999)
            {
                fval /= 10;
            } /* Keep 3 most significant digits. Should not occur. */
            core_p->avg_load = (RTEMS_SYSMON_MAX_SCALE - ((ival * 1000) + fval)); /* Get percentages as integer */

            /*
            ** Mimic ADC so that "analogio" API can be used with out modification. API assumes 24 bits.
            ** First calculate out of 0x1000 and then duplicate it to expand to 24 bits. Doing this prevents
            ** an overflow. avg_load has a "real" resolution of 12 bits.
            */
            core_p->avg_load = (0x1000 * core_p->avg_load) / RTEMS_SYSMON_MAX_SCALE;
            core_p->avg_load |= (core_p->avg_load << 12);
        }

#ifdef DEBUG_BUILD
        rtems_cpu_usage_report();

        uint32_t microsec = _Timestamp_Get_nanoseconds(&idle_uptime_elapsed) / TOD_NANOSECONDS_PER_MICROSECOND;
        uint32_t sec      = _Timestamp_Get_seconds(&idle_uptime_elapsed);
        RTEMS_SYSMON_DEBUG("\nCFE_PSP(rtems_sysmon): IDLE cpu time elapsed = %7u.%06u, IDLE percentages =%4u.%03u\n",
                           sec, microsec, ival, fval);

        microsec = _Timestamp_Get_nanoseconds(&total_elapsed) / TOD_NANOSECONDS_PER_MICROSECOND;
        sec      = _Timestamp_Get_seconds(&total_elapsed);
        RTEMS_SYSMON_DEBUG("CFE_PSP(rtems_sysmon): Total elapsed CPU time = %7u.%06u, CPU Load =%08X\n", sec, microsec,
                           core_p->avg_load);
#endif

        state->num_cpus++;
        if (state->num_cpus >= RTEMS_SYSMON_MAX_CPUS)
        {
            /* stop checking when all idle tasks has been found */
            status = true;
        }
    }

    /* return true to exit iterating tasks */
    return status;
}

void rtems_sysmon_update_stat(rtems_sysmon_cpuload_state_t *state)
{
    state->num_cpus = 0;
    rtems_task_iterate(rtems_cpu_usage_vistor, state);
}

rtems_task rtems_sysmon_Task(rtems_task_argument arg)
{
    rtems_sysmon_cpuload_state_t *state = (rtems_sysmon_cpuload_state_t *)arg;
    int                           i;

    /* Initialize */
    rtems_cpu_usage_reset();

    memset(state->per_core, 0, RTEMS_SYSMON_MAX_CPUS * sizeof(rtems_sysmon_cpuload_core_t));
    for (i = 0; i < RTEMS_SYSMON_MAX_CPUS; i++)
    {
        state->per_core[i].last_run_time = CPU_usage_Uptime_at_last_reset;
    }

    while (state->should_run)
    {

        OS_TaskDelay(RTEMS_SYSMON_SAMPLE_DELAY);
        rtems_sysmon_update_stat(state);
    }

    rtems_task_delete(RTEMS_SELF);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * rtems_sysmon_Start()
 * ------------------------------------------------------
 *  Starts the cpu load watcher function
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
static int32_t rtems_sysmon_Start(rtems_sysmon_cpuload_state_t *state)
{
    int32_t           StatusCode;
    rtems_status_code status;

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

        state->should_run = true;
        state->task_name  = rtems_build_name('R', 'S', 'M', ' ');
        status            = rtems_task_create(state->task_name, RTEMS_SYSMON_TASK_PRIORITY, RTEMS_SYSMON_STACK_SIZE,
                                   RTEMS_DEFAULT_MODES, RTEMS_DEFAULT_ATTRIBUTES, &state->task_id);
        if (status != RTEMS_SUCCESSFUL)
        {
            perror("rtems_task_create()");
            state->should_run = false;
        }
        else
        {
            status = rtems_task_start(state->task_id, rtems_sysmon_Task, (rtems_task_argument)state);
            if (status != RTEMS_SUCCESSFUL)
            {
                perror("rtems_task_start()");
                rtems_task_delete(state->task_id);
                state->should_run = false;
            }
            else
            {
                OS_printf("CFE_PSP(RTEMS_SysMon): Started CPU utilization monitoring\n");

                StatusCode        = CFE_PSP_SUCCESS;
                state->is_running = true;
            }
        }
    }
    return StatusCode;
}

int32_t rtems_sysmon_Stop(rtems_sysmon_cpuload_state_t *state)
{
    if (state->is_running)
    {
        state->should_run = false;
        state->is_running = false;
        rtems_task_delete(state->task_id);
    }

    return CFE_PSP_SUCCESS;
}

int32_t rtems_sysmon_calc_aggregate_cpu(rtems_sysmon_cpuload_state_t *state, CFE_PSP_IODriver_AdcCode_t *Val)
{

    uint8_t  cpu;
    uint32_t sum;

    sum = 0;
    for (cpu = 0; cpu < RTEMS_SYSMON_MAX_CPUS; cpu++)
    {
        sum += state->per_core[cpu].avg_load;
    }

    sum /= RTEMS_SYSMON_MAX_CPUS;
    *Val = sum;

    RTEMS_SYSMON_DEBUG("CFE_PSP(rtems_sysmon): Aggregate CPU load=%08X\n", (unsigned int)sum);

    return CFE_PSP_SUCCESS;
}

int32_t rtems_sysmon_aggregate_dispatch(uint32_t CommandCode, uint16_t Subchannel, CFE_PSP_IODriver_Arg_t Arg)
{
    int32_t                       StatusCode;
    rtems_sysmon_cpuload_state_t *state;

    /* There is just one global cpuload object */
    state = &rtems_sysmon_global.cpu_load;

    StatusCode = CFE_PSP_ERROR_NOT_IMPLEMENTED;
    switch (CommandCode)
    {
        case CFE_PSP_IODriver_NOOP:
        case CFE_PSP_IODriver_ANALOG_IO_NOOP:
            RTEMS_SYSMON_DEBUG("CFE_PSP(RTEMS_SysMon): Noop \n");
            break;
        case CFE_PSP_IODriver_SET_RUNNING:
        {
            if (Arg.U32)
            {
                StatusCode = rtems_sysmon_Start(state);
            }
            else
            {
                StatusCode = rtems_sysmon_Stop(state);
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

            for (i = 0; rtems_sysmon_subsystem_names[i] != NULL; ++i)
            {
                if (strcmp(Arg.ConstStr, rtems_sysmon_subsystem_names[i]) == 0)
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

            for (i = 0; rtems_sysmon_subchannel_names[i] != NULL; ++i)
            {
                if (strcmp(Arg.ConstStr, rtems_sysmon_subchannel_names[i]) == 0)
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

            if (RdWr->NumChannels == 1 && Subchannel == RTEMS_SYSMON_AGGR_CPULOAD_SUBCH)
            {
                StatusCode = rtems_sysmon_calc_aggregate_cpu(state, RdWr->Samples);
            }
            break;
        }
        default:
            break;
    }

    return StatusCode;
}

int32_t rtems_sysmon_cpu_load_dispatch(uint32_t CommandCode, uint16_t Subchannel, CFE_PSP_IODriver_Arg_t Arg)
{
    int32_t                       StatusCode;
    rtems_sysmon_cpuload_state_t *state;

    /* There is just one global cpuload object */
    state      = &rtems_sysmon_global.cpu_load;
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

            if (Subchannel < RTEMS_SYSMON_MAX_CPUS && (Subchannel + RdWr->NumChannels) <= RTEMS_SYSMON_MAX_CPUS)
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
/*    rtems_sysmon_DevCmd()                               */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/**
 * \brief Main entry point for API.
 *
 * This function is called through iodriver to invoke the rtems_sysmon module.
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
int32_t rtems_sysmon_DevCmd(uint32_t CommandCode, uint16_t SubsystemId, uint16_t SubchannelId,
                            CFE_PSP_IODriver_Arg_t Arg)
{
    int32_t StatusCode;

    StatusCode = CFE_PSP_ERROR_NOT_IMPLEMENTED;
    switch (SubsystemId)
    {
        case RTEMS_SYSMON_AGGREGATE_SUBSYS:
            StatusCode = rtems_sysmon_aggregate_dispatch(CommandCode, SubchannelId, Arg);
            break;
        case RTEMS_SYSMON_CPULOAD_SUBSYS:
            StatusCode = rtems_sysmon_cpu_load_dispatch(CommandCode, SubchannelId, Arg);
            break;
        default:
            /* not implemented */
            break;
    }

    return StatusCode;
}
