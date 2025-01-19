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
 *    Copyright (c) 2025, United States government as represented by the
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
 * Coverage test for rtems_sysmon module implementation
 */

#include "utassert.h"
#include "utstubs.h"
#include "uttest.h"

#include "coveragetest-rtems_sysmon.h"
#include "coveragetest-rtems_sysmon_utils.h"

/*
 * Reference to the API entry point for the module
 */
const CFE_PSP_ModuleApi_t *   TgtAPI = &CFE_PSP_rtems_sysmon_API;
PCS_Timestamp_Control  PCS_CPU_usage_Uptime_at_last_reset;


void Test_Init_Nominal(void)
{
    int id = 2;

    TgtAPI->Init(id); /* Init rtems Sysmon */
    UtAssert_True(rtems_sysmon_global.local_module_id == id, "Nominal Case: Init RTEMS Sysmon");
}

void Test_Task_Nominal(void)
{
    int DelayCounter = 0;

    /* Nominal Case: rtems sysmon task */
    rtems_sysmon_global.cpu_load.should_run = true;
    UT_SetHookFunction(UT_KEY(OS_TaskDelay), (UT_HookFunc_t)UT_TaskDelay_Hook, &DelayCounter);
    rtems_sysmon_Task((rtems_task_argument) &rtems_sysmon_global.cpu_load);

    UtAssert_True(rtems_sysmon_global.cpu_load.should_run == false && DelayCounter == 1, "Nominal Case: RTEMS Sysmon Task");
}

void Test_Entry_Nominal(void)
{
    int32                   StatusCode;
    CFE_PSP_IODriver_API_t *EntryAPI = TgtAPI->ExtendedApi;

    /* Nominal Case: Aggregate Subsystem */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_NOOP, 0, 0, CFE_PSP_IODriver_U32ARG(0));
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Nominal Case: Aggregate Subsystem");

    /* Nominal Case: Cpuload Subsystem */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_NOOP, 1, 0, CFE_PSP_IODriver_U32ARG(0));
    UtAssert_True(StatusCode == CFE_PSP_SUCCESS, "Nominal Case: Cpuload Subsystem");

    /* Nominal Case: No Subsystem */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_NOOP, 2, 0, CFE_PSP_IODriver_U32ARG(0));
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Nominal Case: No Subsystem");
}

void Test_Aggregate_Nominal(void)
{
    int32 StatusCode;
    int32 IsRunningStatus;

    CFE_PSP_IODriver_AdcCode_t    Sample;
    CFE_PSP_IODriver_AnalogRdWr_t RdWr = {.NumChannels = 1, .Samples = &Sample};
    
    CFE_PSP_IODriver_Direction_t QueryDirArg;
    CFE_PSP_IODriver_API_t *     EntryAPI = TgtAPI->ExtendedApi;

    /* Nominal Case: Aggregate Dispatch Noop CMD (Not Impl) */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_NOOP, 0, 0, CFE_PSP_IODriver_U32ARG(0)); /* Entry Point */
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Nominal Case: IO Driver NOOP");

    /* Nominal Case: Aggregate Dispatch Noop CMD (Not Impl) */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_ANALOG_IO_NOOP, 0, 0, CFE_PSP_IODriver_U32ARG(0));
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Nominal Case:  ANALOG IO NOOP");

    /* Nominal Case: Start RTEMS Sysmon */
    StatusCode      = EntryAPI->DeviceCommand(CFE_PSP_IODriver_SET_RUNNING, 0, 0, CFE_PSP_IODriver_U32ARG(1));
    IsRunningStatus = EntryAPI->DeviceCommand(CFE_PSP_IODriver_GET_RUNNING, 0, 0, CFE_PSP_IODriver_U32ARG(1));
    UtAssert_True(StatusCode == CFE_PSP_SUCCESS, "Nominal Case: Start RTEMS Sysmon");
    UtAssert_True(IsRunningStatus == true, "Nominal Case: RTEMS Sysmon running status set");

    /* Nominal Case: RTEMS Sysmon already running */
    StatusCode      = EntryAPI->DeviceCommand(CFE_PSP_IODriver_SET_RUNNING, 0, 0, CFE_PSP_IODriver_U32ARG(1));
    IsRunningStatus = EntryAPI->DeviceCommand(CFE_PSP_IODriver_GET_RUNNING, 0, 0, CFE_PSP_IODriver_U32ARG(1));
    UtAssert_True(StatusCode == CFE_PSP_SUCCESS, "Nominal Case: RTEMS Sysmon Already Running");
    UtAssert_True(IsRunningStatus == true, "Nominal Case: RTEMS Sysmon running status already set");

    /* Nominal Case: Stop RTEMS Sysmon */
    StatusCode      = EntryAPI->DeviceCommand(CFE_PSP_IODriver_SET_RUNNING, 0, 0, CFE_PSP_IODriver_U32ARG(0));
    IsRunningStatus = EntryAPI->DeviceCommand(CFE_PSP_IODriver_GET_RUNNING, 0, 0, CFE_PSP_IODriver_U32ARG(1));
    UtAssert_True(StatusCode == CFE_PSP_SUCCESS, "Nominal Case: Stop RTEMS Sysmon");
    UtAssert_True(IsRunningStatus == false, "Nominal Case: RTEMS Sysmon running status disabled");

    /* Nominal Case: RTEMS Sysmon already stop */
    StatusCode      = EntryAPI->DeviceCommand(CFE_PSP_IODriver_SET_RUNNING, 0, 0, CFE_PSP_IODriver_U32ARG(0));
    IsRunningStatus = EntryAPI->DeviceCommand(CFE_PSP_IODriver_GET_RUNNING, 0, 0, CFE_PSP_IODriver_U32ARG(1));
    UtAssert_True(StatusCode == CFE_PSP_SUCCESS, "Nominal Case: RTEMS Sysmon already stopped");
    UtAssert_True(IsRunningStatus == false, "Nominal Case: RTEMS Sysmon running status already disabled");

    /* Nominal Case: Set Configuration (Not Impl) */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_SET_CONFIGURATION, 0, 0, CFE_PSP_IODriver_U32ARG(0));
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Nominal Case: Set Configuration");

    /* Nominal Case: Get Configuration (Not Impl) */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_GET_CONFIGURATION, 0, 0, CFE_PSP_IODriver_U32ARG(0));
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Nominal Case: Get Configuration");

    /* Nominal Case: Look Up per-cpu Subsystem */
    StatusCode =
        EntryAPI->DeviceCommand(CFE_PSP_IODriver_LOOKUP_SUBSYSTEM, 0, 0, CFE_PSP_IODriver_CONST_STR("per-cpu"));
    UtAssert_True(StatusCode == 1, "Nominal Case: Look up per-cpu subsytem");

    /* Nominal Case: Look Up aggregate Subsystem */
    StatusCode =
        EntryAPI->DeviceCommand(CFE_PSP_IODriver_LOOKUP_SUBSYSTEM, 0, 0, CFE_PSP_IODriver_CONST_STR("aggregate"));
    UtAssert_True(StatusCode == 0, "Nominal Case: Look up aggregate subsytem");

    /* Nominal Case: Look Up cpu-load subchannel */
    StatusCode =
        EntryAPI->DeviceCommand(CFE_PSP_IODriver_LOOKUP_SUBCHANNEL, 0, 0, CFE_PSP_IODriver_CONST_STR("cpu-load"));
    UtAssert_True(StatusCode == 0, "Nominal Case: Look up cpu-load subchannel");

    /* Nominal Case: Query Direction */
    QueryDirArg = CFE_PSP_IODriver_Direction_DISABLED;
    StatusCode  = EntryAPI->DeviceCommand(CFE_PSP_IODriver_QUERY_DIRECTION, 0, 0, CFE_PSP_IODriver_VPARG(&QueryDirArg));
    UtAssert_True(StatusCode == CFE_PSP_SUCCESS, "Nominal Case: RTEMS Sysmon Driver Query Direction Status Code");
    UtAssert_True(QueryDirArg == CFE_PSP_IODriver_Direction_INPUT_ONLY,
                  "Nominal Case: RTEMS Sysmon Direction (INPUT ONLY)");

    /* Nominal Case: Analog IO Read Channel */
    Sample     = -1;
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_ANALOG_IO_READ_CHANNELS, 0, 0, CFE_PSP_IODriver_VPARG(&RdWr));
    UtAssert_True(StatusCode == CFE_PSP_SUCCESS, "Nominal Case: RTEMS Sysmon Aggregate CPU Load Status Code");
    UtAssert_True(Sample == 0, "Nominal Case: RTEMS Sysmon Aggregate CPU");
}

void Test_Aggregate_Error(void)
{
    CFE_PSP_IODriver_API_t *      EntryAPI = TgtAPI->ExtendedApi;
    int32                         StatusCode;
    int32                         IsRunningStatus;
    CFE_PSP_IODriver_AdcCode_t    Sample;
    CFE_PSP_IODriver_AnalogRdWr_t RdWr = {.NumChannels = 1, .Samples = &Sample};

    /* Error Case: Look Up Subsystem Not Found */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_LOOKUP_SUBSYSTEM, 0, 0, CFE_PSP_IODriver_CONST_STR("Empty"));
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Error Case: Subsystem Not Found");

    /* Error Case: Look Up Subchannel Not Found */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_LOOKUP_SUBCHANNEL, 0, 0, CFE_PSP_IODriver_CONST_STR("Empty"));
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Error Case: Subchannel Not Found");

    /* Error Case: NULL Query Direction */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_QUERY_DIRECTION, 0, 0, CFE_PSP_IODriver_VPARG(NULL));
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Error Case: NULL Query Direction Status Code");

    /* Error Case: Analog IO Read, Wrong Channel Number */
    Sample           = -1;
    RdWr.NumChannels = 0;
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_ANALOG_IO_READ_CHANNELS, 0, 0, CFE_PSP_IODriver_VPARG(&RdWr));
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Error Case: Analog IO Read, Wrong Channel Number");

    /* Error Case: Analog IO Read, Wrong Channel Subchannel */
    Sample           = -1;
    RdWr.NumChannels = 1;
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_ANALOG_IO_READ_CHANNELS, 0, 5, CFE_PSP_IODriver_VPARG(&RdWr));
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Error Case: Analog IO Read, Wrong Subchannel");

    /* Error Case: Command Code Not Found */
    StatusCode = EntryAPI->DeviceCommand(40, 0, 0, CFE_PSP_IODriver_U32ARG(0));
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Error Case: Aggregated Substem, Bad Command Code");

    /* Error Case: Unable To Create Child Process */
    UT_SetDeferredRetcode(UT_KEY(PCS_rtems_task_create), 1, OS_ERROR);
    StatusCode      = EntryAPI->DeviceCommand(CFE_PSP_IODriver_SET_RUNNING, 0, 0, CFE_PSP_IODriver_U32ARG(1));
    IsRunningStatus = EntryAPI->DeviceCommand(CFE_PSP_IODriver_GET_RUNNING, 0, 0, CFE_PSP_IODriver_U32ARG(1));
    UtAssert_True(StatusCode == CFE_PSP_ERROR, "Error Case: Creating Child Process, Status Code");
    UtAssert_True(IsRunningStatus == false, "Error Case: Creating Child Process, Running Status");

    /* Error Case: Unable To Start Child Process */
    UT_SetDeferredRetcode(UT_KEY(PCS_rtems_task_create), 1, RTEMS_SUCCESSFUL);
    UT_SetDeferredRetcode(UT_KEY(PCS_rtems_task_start), 1, OS_ERROR);
    StatusCode      = EntryAPI->DeviceCommand(CFE_PSP_IODriver_SET_RUNNING, 0, 0, CFE_PSP_IODriver_U32ARG(1));
    IsRunningStatus = EntryAPI->DeviceCommand(CFE_PSP_IODriver_GET_RUNNING, 0, 0, CFE_PSP_IODriver_U32ARG(1));
    UtAssert_True(StatusCode == CFE_PSP_ERROR, "Error Case: Creating Starting Child Process, Status Code");
    UtAssert_True(IsRunningStatus == false, "Error Case: Creating Starting Child Process, Running Status");
}

void Test_Dispatch_Cpuload_Nominal(void)
{
    CFE_PSP_IODriver_API_t *      EntryAPI = TgtAPI->ExtendedApi;
    CFE_PSP_IODriver_AdcCode_t    Sample[2];
    CFE_PSP_IODriver_AnalogRdWr_t RdWr = {.NumChannels = 1, .Samples = Sample};
    int32                         StatusCode;

    /* Nominal Case: Dispatch IO Driver NOOP */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_NOOP, 1, 0, CFE_PSP_IODriver_U32ARG(1));
    UtAssert_True(StatusCode == CFE_PSP_SUCCESS, "Nominal Case: Dispatch IO Driver NOOP ");

    /* Nominal Case: Dispatch Analog IO NOOP */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_ANALOG_IO_NOOP, 1, 0, CFE_PSP_IODriver_U32ARG(1));
    UtAssert_True(StatusCode == CFE_PSP_SUCCESS, "Nominal Case: Dispatch Analog IO NOOP");

    /* Nominal Case: Dispatch Analog Read Channels */
    Sample[0]  = -1;
    Sample[1]  = -1;
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_ANALOG_IO_READ_CHANNELS, 1, 0, CFE_PSP_IODriver_VPARG(&RdWr));
    UtAssert_True(StatusCode == CFE_PSP_SUCCESS && Sample[0] == 0 && Sample[1] == -1, "Nominal Case: Dispatch cpuload");
}

void Test_Dispatch_Cpuload_Error(void)
{
    CFE_PSP_IODriver_API_t *      EntryAPI = TgtAPI->ExtendedApi;
    CFE_PSP_IODriver_AdcCode_t    Sample[2];
    CFE_PSP_IODriver_AnalogRdWr_t RdWr = {.NumChannels = 1, .Samples = Sample};
    int                           StatusCode;

    /* Error Case: Dispatch Analog Read Channels, Subchannel >= Max Cpu */
    /* Default max cpu == 1 */
    Sample[0]  = -1;
    Sample[1]  = -1;
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_ANALOG_IO_READ_CHANNELS, 1, 2, CFE_PSP_IODriver_VPARG(&RdWr));
    UtAssert_True(Sample[0] == -1 && Sample[1] == -1 && StatusCode == CFE_PSP_ERROR,
                  "Error Case: Dispatch cpuload, subchannel >= max cpu");

    /* Error Case: Dispatch Analog Read Channels, NumChannels > max cpu */
    RdWr.NumChannels = 2;
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_ANALOG_IO_READ_CHANNELS, 1, 0, CFE_PSP_IODriver_VPARG(&RdWr));
    UtAssert_True(StatusCode == CFE_PSP_ERROR && Sample[0] == -1 && Sample[1] == -1,
                  "Error Case: Dispatch cpuload, NumChannels > max cpu");

    /* Error Case: Command Code Not Found */
    StatusCode = EntryAPI->DeviceCommand(10, 1, 0, CFE_PSP_IODriver_U32ARG(1));
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Error Case: Command Code Not Found");
}

void Test_Cpu_Visitor_Nominal(void)
{
    PCS_Thread_Control Thread;
    UT_ThreadGetNameData_t UT_ThreadGetNameData;
    rtems_sysmon_cpuload_state_t Arg;
    UT_TimeDivideData_t UT_TimeDivideData;
    int32 AverageLoadCalc;

    UT_SetHookFunction(UT_KEY(PCS_Thread_Get_name), (UT_HookFunc_t)UT_ThreadGetName_Hook, &UT_ThreadGetNameData);
    UT_SetHookFunction(UT_KEY(PCS_Timestamp_Divide), (UT_HookFunc_t)UT_TimestampDivide_Hook, &UT_TimeDivideData);

    /* Nominal Test: Thread Not IDLE Task */
    memset(UT_ThreadGetNameData.Name, 0, sizeof(UT_ThreadGetNameData.Name));
    memset(&Arg, 0, sizeof(Arg));

    strncpy(UT_ThreadGetNameData.Name, "Testing", 7);
    UT_ThreadGetNameData.Size = 7;

    UtAssert_BOOL_FALSE(rtems_cpu_usage_visitor(&Thread, &Arg));
    UtAssert_True(Arg.per_core[0].avg_load == 0, "Nominal Case: Not Idle Task");

    /* Nominal Case Idle Task */
    /* 100% CPU util. */
    memset(UT_ThreadGetNameData.Name, 0, sizeof(UT_ThreadGetNameData.Name));
    memset(&Arg, 0, sizeof(Arg));
    memset(&UT_TimeDivideData, 0, sizeof(UT_TimeDivideData));

    strncpy(UT_ThreadGetNameData.Name, "IDLE", 4);
    UT_ThreadGetNameData.Size = 4;

    UT_TimeDivideData.IntValue = 100;
    UT_TimeDivideData.FraValue = 0;

    UtAssert_BOOL_TRUE(rtems_cpu_usage_visitor(&Thread, &Arg));
    UtAssert_True(Arg.per_core[0].avg_load == 0xFFFFFF, "Nominal Case: 100 percents cpu utilization");

    /* Nominal Case Idle Task */
    /* 50 percent util */
    memset(UT_ThreadGetNameData.Name, 0, sizeof(UT_ThreadGetNameData.Name));
    memset(&Arg, 0, sizeof(Arg));
    memset(&UT_TimeDivideData, 0, sizeof(UT_TimeDivideData));

    strncpy(UT_ThreadGetNameData.Name, "IDLE", 4);
    UT_ThreadGetNameData.Size = 4;

    UT_TimeDivideData.IntValue = 50;
    UT_TimeDivideData.FraValue = 0;
    UT_TimeDivideData.TotalElapsed = 10;
    UT_TimeDivideData.IdleUptimeElapsed = 5;

    UtAssert_BOOL_TRUE(rtems_cpu_usage_visitor(&Thread, &Arg)); 

    AverageLoadCalc = 0x1000 * UT_TimeDivideData.IntValue / 100;
    AverageLoadCalc |= (AverageLoadCalc << 12);
    UtAssert_True(Arg.per_core[0].avg_load == AverageLoadCalc, "Nominal Case: 50 percents cpu utilization");

    /* Nominal Case Idle Task */
    /* 49.999 percent util */
    memset(UT_ThreadGetNameData.Name, 0, sizeof(UT_ThreadGetNameData.Name));
    memset(&Arg, 0, sizeof(Arg));
    memset(&UT_TimeDivideData, 0, sizeof(UT_TimeDivideData));

    strncpy(UT_ThreadGetNameData.Name, "IDLE", 4);
    UT_ThreadGetNameData.Size = 4;

    UT_TimeDivideData.IntValue = 50;
    UT_TimeDivideData.FraValue = 9990;
    UT_TimeDivideData.TotalElapsed = 10; /* placeholder */
    UT_TimeDivideData.IdleUptimeElapsed = 5; /* placeholder*/

    UtAssert_BOOL_TRUE(rtems_cpu_usage_visitor(&Thread, &Arg)); 

    /* convert int and fra part of percentages into integer. 
    ** Then convert into an percentages and normalizes out of 0x1000 
    */
    AverageLoadCalc =  (UT_TimeDivideData.IntValue * 1000) + (UT_TimeDivideData.FraValue / 10); /* Combine fraction and int to one number */
    AverageLoadCalc = (0x1000 * (100000 - AverageLoadCalc)) / 100000;
    AverageLoadCalc |= (AverageLoadCalc << 12);
    UtAssert_True(Arg.per_core[0].avg_load == AverageLoadCalc, "Nominal Case: 49.001 percents cpu utilization");

    /* Nominal Case Idle Task */
    /* 0 percent util */
    memset(UT_ThreadGetNameData.Name, 0, sizeof(UT_ThreadGetNameData.Name));
    memset(&Arg, 0, sizeof(Arg));
    memset(&UT_TimeDivideData, 0, sizeof(UT_TimeDivideData));

    strncpy(UT_ThreadGetNameData.Name, "IDLE", 4);
    UT_ThreadGetNameData.Size = 4;

    UT_TimeDivideData.IntValue = 0;
    UT_TimeDivideData.FraValue = 0;
    UT_TimeDivideData.TotalElapsed = 0;
    UT_TimeDivideData.IdleUptimeElapsed = 0;

    UtAssert_BOOL_TRUE(rtems_cpu_usage_visitor(&Thread, &Arg)); 
    UtAssert_True(Arg.per_core[0].avg_load == 0, "Nominal Case: 0 percents cpu utilization");

    /* Nominal Case: Max Cpu not reach */
    memset(UT_ThreadGetNameData.Name, 0, sizeof(UT_ThreadGetNameData.Name));
    memset(&Arg, 0, sizeof(Arg));
    memset(&UT_TimeDivideData, 0, sizeof(UT_TimeDivideData));

    strncpy(UT_ThreadGetNameData.Name, "IDLE", 4);
    Arg.num_cpus = -1;
    UtAssert_BOOL_FALSE(rtems_cpu_usage_visitor(&Thread, &Arg)); 
    UtAssert_True(Arg.num_cpus == 0, "Nominal Case: CPU Number increment");

}

/*
 * Register the test cases to execute with the unit test tool
 */
void UtTest_Setup(void)
{
    ADD_TEST(Test_Init_Nominal);
    ADD_TEST(Test_Entry_Nominal);
    ADD_TEST(Test_Aggregate_Nominal);
    ADD_TEST(Test_Aggregate_Error);
    ADD_TEST(Test_Dispatch_Cpuload_Nominal);
    ADD_TEST(Test_Dispatch_Cpuload_Error);
    ADD_TEST(Test_Cpu_Visitor_Nominal);
    ADD_TEST(Test_Task_Nominal);

}
