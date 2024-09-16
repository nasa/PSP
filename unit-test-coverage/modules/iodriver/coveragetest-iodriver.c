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

#include "iodriver_base.h"
#include "iodriver_impl.h"

CFE_PSP_IODriver_API_t Ut_NoopAPI = {NULL, NULL};

extern void                    iodriver_Init(uint32 PspModuleId);
extern CFE_PSP_IODriver_API_t *CFE_PSP_IODriver_GetAPI(uint32 PspModuleId);

static int32 Stub_DeviceCommand(uint32 CommandCode, uint16 Instance, uint16 SubChannel, CFE_PSP_IODriver_Arg_t arg)
{
    return UT_DEFAULT_IMPL(Stub_DeviceCommand);
}

static int32 Stub_DeviceMutex(uint32 CommandCode, uint16 Instance, uint16 SubChannel, CFE_PSP_IODriver_Arg_t arg)
{
    return UT_DEFAULT_IMPL(Stub_DeviceMutex);
}

/*
 * --------------------------------------------
 * Instantiation of a Stub IO Driver with no mutex
 * --------------------------------------------
 */
static void StubNoMut_Init(uint32 ModuleID)
{
    UT_DEFAULT_IMPL(StubNoMut_Init);
}

static CFE_PSP_IODriver_API_t StubNoMut_DevApi = {.DeviceCommand = Stub_DeviceCommand};

CFE_PSP_MODULE_DECLARE_IODEVICEDRIVER(StubNoMut);

/*
 * --------------------------------------------
 * Instantiation of a Stub IO Driver with mutex
 * --------------------------------------------
 */
static void StubWithMut_Init(uint32 ModuleID)
{
    UT_DEFAULT_IMPL(StubWithMut_Init);
}

static CFE_PSP_IODriver_API_t StubWithMut_DevApi = {.DeviceCommand = Stub_DeviceCommand,
                                                    .DeviceMutex   = Stub_DeviceMutex};

CFE_PSP_MODULE_DECLARE_IODEVICEDRIVER(StubWithMut);

/*
 * --------------------------------------------
 * HANDLER FUNCTIONS -- helpers for stubs
 * --------------------------------------------
 */

static void UtHandler_CFE_PSP_Module_GetAPIEntry(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* Handler for:
     * int32 CFE_PSP_Module_GetAPIEntry(uint32 PspModuleId, CFE_PSP_ModuleApi_t **API);
     */

    CFE_PSP_ModuleApi_t **API = UT_Hook_GetArgValueByName(Context, "API", CFE_PSP_ModuleApi_t **);
    int32                 status;

    /* This needs to output a proper value */
    UT_Stub_GetInt32StatusCode(Context, &status);
    if (status >= 0)
    {
        *API = UserObj;
    }
    else
    {
        *API = NULL;
    }
}

static void UtHandler_CFE_PSP_Module_FindByName(void *UserObj, UT_EntryKey_t FuncKey, const UT_StubContext_t *Context)
{
    /* Handler for:
     * int32 CFE_PSP_Module_FindByName(const char *ModuleName, uint32 *PspModuleId);
     */
    uint32 *PspModuleId = UT_Hook_GetArgValueByName(Context, "PspModuleId", uint32 *);
    int32   status;

    /* This needs to output a proper value */
    UT_Stub_GetInt32StatusCode(Context, &status);
    if (status >= 0 && UserObj != NULL)
    {
        *PspModuleId = *((uint32 *)UserObj);
    }
    else
    {
        *PspModuleId = 0;
    }
}

/*
 * --------------------------------------------
 * TEST FUNCTIONS
 * --------------------------------------------
 */

void Test_iodriver_Init(void)
{
    /* Test For:
     * void iodriver_Init(uint32 PspModuleId)
     */
    UtAssert_VOIDCALL(iodriver_Init(1));
}

void Test_CFE_PSP_IODriver_GetAPI(void)
{
    /* Test For:
     * CFE_PSP_IODriver_API_t *CFE_PSP_IODriver_GetAPI(uint32 PspModuleId)
     */
    CFE_PSP_IODriver_API_t *ApiPtr;

    /* Requesting a nonexistent module should return a default API */
    UtAssert_NOT_NULL(ApiPtr = CFE_PSP_IODriver_GetAPI(0));
    UtAssert_BOOL_TRUE(ApiPtr->DeviceCommand == NULL);
    UtAssert_BOOL_TRUE(ApiPtr->DeviceMutex == NULL);

    UT_SetDefaultReturnValue(UT_KEY(CFE_PSP_Module_GetAPIEntry), -1);
    UtAssert_NOT_NULL(ApiPtr = CFE_PSP_IODriver_GetAPI(0));
    UtAssert_BOOL_TRUE(ApiPtr->DeviceCommand == NULL);
    UtAssert_BOOL_TRUE(ApiPtr->DeviceMutex == NULL);

    UT_ResetState(UT_KEY(CFE_PSP_Module_GetAPIEntry));
    UT_SetHandlerFunction(UT_KEY(CFE_PSP_Module_GetAPIEntry), UtHandler_CFE_PSP_Module_GetAPIEntry,
                          (void *)&CFE_PSP_StubNoMut_API);
    UtAssert_NOT_NULL(ApiPtr = CFE_PSP_IODriver_GetAPI(0));
    UtAssert_BOOL_TRUE(ApiPtr->DeviceCommand == Stub_DeviceCommand);
}

void Test_CFE_PSP_IODriver_GetMutex(void)
{
    /* Test For:
     * osal_id_t CFE_PSP_IODriver_GetMutex(uint32 PspModuleId, int32 DeviceHash)
     */
    UtAssert_BOOL_TRUE(OS_ObjectIdDefined(CFE_PSP_IODriver_GetMutex(1, 2)));
    UtAssert_BOOL_TRUE(OS_ObjectIdDefined(CFE_PSP_IODriver_GetMutex(0, 4)));
    UtAssert_BOOL_FALSE(OS_ObjectIdDefined(CFE_PSP_IODriver_GetMutex(1, -1)));
}

void Test_CFE_PSP_IODriver_HashMutex(void)
{
    /* Test For:
     * int32 CFE_PSP_IODriver_HashMutex(int32 StartHash, int32 Datum)
     */

    /*
     * This is a basic hash function and should modify the value, but do
     * so in a way that makes a pseudo-random result.  It is not the intent
     * to "check" the result here because that would simply be implementing
     * the algoritm in reverse.  All this will confirm is the output value is
     * different than the input (StartHash).  There are no branches in this
     * routine, it is just a numeric calculation.
     */
    UtAssert_INT32_NEQ(CFE_PSP_IODriver_HashMutex(1, 2), 1);
    UtAssert_INT32_NEQ(CFE_PSP_IODriver_HashMutex(2, 3), 2);
}

void Test_CFE_PSP_IODriver_Command(void)
{
    /* Test For:
     * int32 CFE_PSP_IODriver_Command(const CFE_PSP_IODriver_Location_t *Location, uint32 CommandCode,
     * CFE_PSP_IODriver_Arg_t Arg)
     */
    const CFE_PSP_IODriver_Location_t UtLocation = {1, 1, 1};

    UT_SetHandlerFunction(UT_KEY(CFE_PSP_Module_GetAPIEntry), UtHandler_CFE_PSP_Module_GetAPIEntry,
                          (void *)&Ut_NoopAPI);
    UtAssert_INT32_EQ(CFE_PSP_IODriver_Command(&UtLocation, 1, CFE_PSP_IODriver_U32ARG(0)),
                      CFE_PSP_ERROR_NOT_IMPLEMENTED);

    UT_SetHandlerFunction(UT_KEY(CFE_PSP_Module_GetAPIEntry), UtHandler_CFE_PSP_Module_GetAPIEntry,
                          (void *)&CFE_PSP_StubNoMut_API);
    UtAssert_INT32_EQ(CFE_PSP_IODriver_Command(&UtLocation, 1, CFE_PSP_IODriver_U32ARG(0)), CFE_PSP_SUCCESS);
    UtAssert_STUB_COUNT(Stub_DeviceCommand, 1);
    UtAssert_STUB_COUNT(Stub_DeviceMutex, 0);

    UT_SetHandlerFunction(UT_KEY(CFE_PSP_Module_GetAPIEntry), UtHandler_CFE_PSP_Module_GetAPIEntry,
                          (void *)&CFE_PSP_StubWithMut_API);
    UtAssert_INT32_EQ(CFE_PSP_IODriver_Command(&UtLocation, 1, CFE_PSP_IODriver_U32ARG(0)), CFE_PSP_SUCCESS);
    UtAssert_STUB_COUNT(Stub_DeviceCommand, 2);
    UtAssert_STUB_COUNT(Stub_DeviceMutex, 1);
}

void Test_CFE_PSP_IODriver_FindByName(void)
{
    /* Test For:
     * int32 CFE_PSP_IODriver_FindByName(const char *DriverName, uint32 *PspModuleId)
     */
    uint32 ModuleID = 0;
    uint32 CheckID  = 1234;

    UT_SetDefaultReturnValue(UT_KEY(CFE_PSP_Module_FindByName), -100);
    UtAssert_INT32_EQ(CFE_PSP_IODriver_FindByName("UT", &ModuleID), -100);
    UT_ResetState(UT_KEY(CFE_PSP_Module_FindByName));

    UT_SetHandlerFunction(UT_KEY(CFE_PSP_Module_FindByName), UtHandler_CFE_PSP_Module_FindByName, &CheckID);
    UT_SetHandlerFunction(UT_KEY(CFE_PSP_Module_GetAPIEntry), UtHandler_CFE_PSP_Module_GetAPIEntry,
                          (void *)&Ut_NoopAPI);
    UtAssert_INT32_EQ(CFE_PSP_IODriver_FindByName("UT", &ModuleID), CFE_PSP_INVALID_MODULE_NAME);

    UT_SetHandlerFunction(UT_KEY(CFE_PSP_Module_GetAPIEntry), UtHandler_CFE_PSP_Module_GetAPIEntry,
                          (void *)&CFE_PSP_StubWithMut_API);
    UtAssert_INT32_EQ(CFE_PSP_IODriver_FindByName("UT", &ModuleID), CFE_PSP_SUCCESS);
    UtAssert_INT32_EQ(ModuleID, CheckID);

    UT_ResetState(UT_KEY(CFE_PSP_Module_GetAPIEntry));
    UT_SetDefaultReturnValue(UT_KEY(CFE_PSP_Module_GetAPIEntry), -101);
    UtAssert_INT32_EQ(CFE_PSP_IODriver_FindByName("UT", &ModuleID), -101);
}

/*
 * Macro to add a test case to the list of tests to execute
 */
#define ADD_TEST(test) UtTest_Add(test, ResetTest, NULL, #test)

void ResetTest(void)
{
    UT_ResetState(0);
}

/*
 * Register the test cases to execute with the unit test tool
 */
void UtTest_Setup(void)
{
    ADD_TEST(Test_iodriver_Init);
    ADD_TEST(Test_CFE_PSP_IODriver_GetAPI);
    ADD_TEST(Test_CFE_PSP_IODriver_GetMutex);
    ADD_TEST(Test_CFE_PSP_IODriver_HashMutex);
    ADD_TEST(Test_CFE_PSP_IODriver_Command);
    ADD_TEST(Test_CFE_PSP_IODriver_FindByName);
}
