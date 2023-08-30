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
 **********************************************************************/

/*
 *
 *    Copyright (c) 2023, United States government as represented by the
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
 * Coverage test for VxWorks Sysmon
 */

#include "utassert.h"
#include "utstubs.h"
#include "uttest.h"

#include "cfe_psp.h"
#include "cfe_psp_config.h"
#include "cfe_psp_module.h"

#include "PCS_spyLib.h"
#include "PCS_spyLibP.h"

#include "coveragetest-vxworks_sysmon.h"

/*
 * Reference to the API entry point for the module
 */
extern CFE_PSP_ModuleApi_t CFE_PSP_vxworks_sysmon_API;
const CFE_PSP_ModuleApi_t *TgtAPI = &CFE_PSP_vxworks_sysmon_API;

void ModuleTest_ResetState(void)
{
    TgtAPI->Init(0); /* Init Vxworks Sysmon */
}

void Test_Entry_Nominal(void)
{
    int32 StatusCode;
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
    int32 IsRunningStatus;;
    CFE_PSP_IODriver_AdcCode_t     Sample;
    CFE_PSP_IODriver_AnalogRdWr_t  RdWr = {.NumChannels = 1, .Samples = &Sample};;    
    CFE_PSP_IODriver_Direction_t QueryDirArg;
    CFE_PSP_IODriver_API_t *EntryAPI = TgtAPI->ExtendedApi;

    /* Nominal Case: Aggregate Dispatch Noop CMD (Not Impl) */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_NOOP, 0, 0, CFE_PSP_IODriver_U32ARG(0)); /* Entry Point */
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Nominal Case: IO Driver NOOP");

    /* Nominal Case: Aggregate Dispatch Noop CMD (Not Impl) */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_ANALOG_IO_NOOP, 0, 0, CFE_PSP_IODriver_U32ARG(0));
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Nominal Case:  ANALOG IO NOOP");

    /* Nominal Case: Start Vxworks Sysmon */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_SET_RUNNING, 0, 0, CFE_PSP_IODriver_U32ARG(1));
    IsRunningStatus = EntryAPI->DeviceCommand(CFE_PSP_IODriver_GET_RUNNING, 0, 0, CFE_PSP_IODriver_U32ARG(1));
    UtAssert_True(StatusCode == CFE_PSP_SUCCESS, "Nominal Case: Start Vxworks Sysmon");
    UtAssert_True(IsRunningStatus == true, "Nominal Case: Vxworks Sysmon running status set");

    /* Nominal Case: VxWorks Sysmon already running */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_SET_RUNNING, 0, 0, CFE_PSP_IODriver_U32ARG(1));
    IsRunningStatus = EntryAPI->DeviceCommand(CFE_PSP_IODriver_GET_RUNNING, 0, 0, CFE_PSP_IODriver_U32ARG(1));
    UtAssert_True(StatusCode == CFE_PSP_SUCCESS, "Nominal Case: Vxworks Sysmon Already Running");
    UtAssert_True(IsRunningStatus == true, "Nominal Case: Vxworks Sysmon running status already set");

    /* Nominal Case: Stop Vxworks Sysmon */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_SET_RUNNING, 0, 0, CFE_PSP_IODriver_U32ARG(0));
    IsRunningStatus = EntryAPI->DeviceCommand(CFE_PSP_IODriver_GET_RUNNING, 0, 0, CFE_PSP_IODriver_U32ARG(1));
    UtAssert_True(StatusCode == CFE_PSP_SUCCESS, "Nominal Case: Stop Vxworks Sysmon");
    UtAssert_True(IsRunningStatus == false, "Nominal Case: Vxworks Sysmon running status disabled");   

    /* Nominal Case: Vxworks Sysmon already stop */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_SET_RUNNING, 0, 0, CFE_PSP_IODriver_U32ARG(0));
    IsRunningStatus = EntryAPI->DeviceCommand(CFE_PSP_IODriver_GET_RUNNING, 0, 0, CFE_PSP_IODriver_U32ARG(1));
    UtAssert_True(StatusCode == CFE_PSP_SUCCESS, "Nominal Case: Vxworks Sysmon already stopped");
    UtAssert_True(IsRunningStatus == false, "Nominal Case: Vxworks Sysmon running status already disabled"); 
    
    /* Nominal Case: Set Configuration (Not Impl) */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_SET_CONFIGURATION, 0, 0, CFE_PSP_IODriver_U32ARG(0)); 
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Nominal Case: Set Configuration");

    /* Nominal Case: Get Configuration (Not Impl) */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_GET_CONFIGURATION, 0, 0, CFE_PSP_IODriver_U32ARG(0)); 
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Nominal Case: Get Configuration");

    /* Nominal Case: Look Up per-cpu Subsystem */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_LOOKUP_SUBSYSTEM, 0, 0, 
                                           CFE_PSP_IODriver_CONST_STR("per-cpu"));
    UtAssert_True(StatusCode == 1, "Nominal Case: Look up per-cpu subsytem");

    /* Nominal Case: Look Up aggregate Subsystem */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_LOOKUP_SUBSYSTEM, 0, 0, 
                                           CFE_PSP_IODriver_CONST_STR("aggregate"));
    UtAssert_True(StatusCode == 0, "Nominal Case: Look up aggregate subsytem");

    /* Nominal Case: Look Up cpu-load subchannel */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_LOOKUP_SUBCHANNEL, 0, 0, 
                                           CFE_PSP_IODriver_CONST_STR("cpu-load"));
    UtAssert_True(StatusCode == 0, "Nominal Case: Look up cpu-load subchannel");

    /* Nominal Case: Query Direction */
    QueryDirArg = CFE_PSP_IODriver_Direction_DISABLED;
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_QUERY_DIRECTION, 0, 0, CFE_PSP_IODriver_VPARG(&QueryDirArg));
    UtAssert_True(StatusCode == CFE_PSP_SUCCESS, "Nominal Case: VxWorks Sysmon Driver Query Direction Status Code");
    UtAssert_True(QueryDirArg == CFE_PSP_IODriver_Direction_INPUT_ONLY, "Nominal Case: VxWorks Sysmon Direction (INPUT ONLY)");

    /* Nominal Case: Analog IO Read Channel */
    Sample = -1;
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_ANALOG_IO_READ_CHANNELS, 0, 0, CFE_PSP_IODriver_VPARG(&RdWr));
    UtAssert_True(StatusCode == CFE_PSP_SUCCESS, "Nominal Case: VxWorks Sysmon Aggregate CPU Load Status Code");
    UtAssert_True(Sample == 0, "Nominal Case: VxWorks Sysmon Aggregate CPU");

}

void Test_Aggregate_Error(void)
{
    CFE_PSP_IODriver_API_t *EntryAPI = TgtAPI->ExtendedApi;
    int32 StatusCode;
    int32 IsRunningStatus;
    CFE_PSP_IODriver_AdcCode_t     Sample;
    CFE_PSP_IODriver_AnalogRdWr_t  RdWr = {.NumChannels = 1, .Samples = &Sample};; 

    /* Error Case: Look Up Subsystem Not Found */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_LOOKUP_SUBSYSTEM, 0, 0, 
                                           CFE_PSP_IODriver_CONST_STR("Empty"));
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Error Case: Subsystem Not Found");

    /* Error Case: Look Up Subchannel Not Found */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_LOOKUP_SUBCHANNEL, 0, 0, 
                                           CFE_PSP_IODriver_CONST_STR("Empty"));
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Error Case: Subchannel Not Found");

    /* Error Case: NULL Query Direction */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_QUERY_DIRECTION, 0, 0, CFE_PSP_IODriver_VPARG(NULL));
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Error Case: NULL Query Direction Status Code");

    /* Error Case: Analog IO Read, Wrong Channel Number */
    Sample = -1;
    RdWr.NumChannels = 0;
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_ANALOG_IO_READ_CHANNELS, 0, 0, CFE_PSP_IODriver_VPARG(&RdWr));
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Error Case: Analog IO Read, Wrong Channel Number");

    /* Error Case: Analog IO Read, Wrong Channel Subchannel */
    Sample = -1;
    RdWr.NumChannels = 1;
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_ANALOG_IO_READ_CHANNELS, 0, 5, CFE_PSP_IODriver_VPARG(&RdWr));
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Error Case: Analog IO Read, Wrong Subchannel");

    /* Error Case: Command Code Not Found */
    StatusCode = EntryAPI->DeviceCommand(40, 0, 0, CFE_PSP_IODriver_U32ARG(0)); 
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Error Case: Aggregated Substem, Bad Command Code");

    /* Error Case: Unable To Start Child Process */
    UT_SetDeferredRetcode(UT_KEY(OS_TaskCreate), 1, OS_ERROR);
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_SET_RUNNING, 0, 0, CFE_PSP_IODriver_U32ARG(1));
    IsRunningStatus = EntryAPI->DeviceCommand(CFE_PSP_IODriver_GET_RUNNING, 0, 0, CFE_PSP_IODriver_U32ARG(1));
    UtAssert_True(StatusCode == CFE_PSP_ERROR, "Error Case: Creating Child Process, Status Code");
    UtAssert_True(IsRunningStatus == false, "Error Case: Creating Child Process, Running Status");
}

void Test_Dispatch_Nominal(void)
{
    CFE_PSP_IODriver_API_t *EntryAPI = TgtAPI->ExtendedApi;
    CFE_PSP_IODriver_AdcCode_t     Sample[2];
    CFE_PSP_IODriver_AnalogRdWr_t  RdWr = {.NumChannels = 1, .Samples = Sample};
    int32 StatusCode;

    /* Nominal Case: Dispatch IO Driver NOOP */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_NOOP, 1, 0, CFE_PSP_IODriver_U32ARG(1));
    UtAssert_True(StatusCode == CFE_PSP_SUCCESS, "Nominal Case: Dispatch IO Driver NOOP ");

    /* Nominal Case: Dispatch Analog IO NOOP */
    StatusCode = EntryAPI->DeviceCommand(CFE_PSP_IODriver_ANALOG_IO_NOOP, 1, 0, CFE_PSP_IODriver_U32ARG(1));
    UtAssert_True(StatusCode == CFE_PSP_SUCCESS, "Nominal Case: Dispatch Analog IO NOOP");

    /* Nominal Case: Dispatch Analog Read Channels */
    Sample[0] = -1;
    Sample[1] = -1;
    EntryAPI->DeviceCommand(CFE_PSP_IODriver_ANALOG_IO_READ_CHANNELS, 1, 0, CFE_PSP_IODriver_VPARG(&RdWr));
    UtAssert_True(Sample[0] == 0 && Sample[1] == -1, "Nominal Case: Dispatch cpuload");
}

void Test_Dispatch_Error(void)
{
    CFE_PSP_IODriver_API_t *EntryAPI = TgtAPI->ExtendedApi;
    CFE_PSP_IODriver_AdcCode_t     Sample[2];
    CFE_PSP_IODriver_AnalogRdWr_t  RdWr = {.NumChannels = 1, .Samples = Sample};
    int StatusCode;

    /* Error Case: Dispatch Analog Read Channels, Subchannel >= Max Cpu */
    /* Default max cpu == 1 */
    Sample[0] = -1;
    Sample[1] = -1;
    EntryAPI->DeviceCommand(CFE_PSP_IODriver_ANALOG_IO_READ_CHANNELS, 1, 2, CFE_PSP_IODriver_VPARG(&RdWr));
    UtAssert_True(Sample[0] == -1 && Sample[1] == -1, "Error Case: Dispatch cpuload, subchannel >= max cpu");

    /* Error Case: Dispatch Analog Read Channels, NumChannels > max cpu */
    RdWr.NumChannels = 2;
    EntryAPI->DeviceCommand(CFE_PSP_IODriver_ANALOG_IO_READ_CHANNELS, 1, 0, CFE_PSP_IODriver_VPARG(&RdWr));
    UtAssert_True(Sample[0] == -1 && Sample[1] == -1, "Error Case: Dispatch cpuload, NumChannels > max cpu");

    /* Error Case: Command Code Not Found */
    StatusCode = EntryAPI->DeviceCommand(10, 1, 0, CFE_PSP_IODriver_U32ARG(1));
    UtAssert_True(StatusCode == CFE_PSP_ERROR_NOT_IMPLEMENTED, "Error Case: Command Code Not Found");
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
    ADD_TEST(Test_Entry_Nominal);
    ADD_TEST(Test_Aggregate_Nominal);
    ADD_TEST(Test_Aggregate_Error);
    ADD_TEST(Test_Dispatch_Nominal);
    ADD_TEST(Test_Dispatch_Error);
}
