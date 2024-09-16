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
 * \ingroup  shared
 */

#include "utassert.h"
#include "utstubs.h"

#include "cfe_psp_module.h"

/* This test needs to set conditions within the global to reach all code */
extern CFE_PSP_ModuleListGlobal_t CFE_PSP_MODULE_LIST_GLOBAL;

static void InitStub(uint32 PspModuleId)
{
    UT_DEFAULT_IMPL(InitStub);
}

CFE_PSP_ModuleApi_t UT_API_INVALID         = {.ModuleType = CFE_PSP_MODULE_TYPE_INVALID};
CFE_PSP_ModuleApi_t UT_API_SIMPLE_NO_INIT  = {.ModuleType = CFE_PSP_MODULE_TYPE_SIMPLE};
CFE_PSP_ModuleApi_t UT_API_SIMPLE_COMPLETE = {.ModuleType = CFE_PSP_MODULE_TYPE_SIMPLE, .Init = InitStub};

static CFE_StaticModuleLoadEntry_t UT_STATIC_MODULE_LIST1[] = {{.Name = "UT1", .Api = &UT_API_INVALID},
                                                               {.Name = "UT2", .Api = &UT_API_SIMPLE_NO_INIT},
                                                               {.Name = "UT3", .Api = &UT_API_SIMPLE_COMPLETE},
                                                               {.Name = NULL, .Api = NULL}};

static CFE_StaticModuleLoadEntry_t UT_STATIC_MODULE_LIST2[] = {{.Name = "UT4", .Api = &UT_API_SIMPLE_COMPLETE},
                                                               {.Name = "UT5", .Api = &UT_API_SIMPLE_NO_INIT},
                                                               {.Name = NULL, .Api = NULL}};

void Test_CFE_PSP_ModuleInitList(void)
{
    /* Test Case for:
     * void CFE_PSP_ModuleInitList(CFE_PSP_ModuleListWrapper_t *WrapPtr, uint32 BaseId, CFE_StaticModuleLoadEntry_t
     * *ListPtr)
     */
    CFE_PSP_ModuleListWrapper_t ModList;

    /* This returns the number of modules in the list */
    UtAssert_VOIDCALL(CFE_PSP_ModuleInitList(&ModList, 0xA0000, UT_STATIC_MODULE_LIST1));
    UtAssert_STUB_COUNT(InitStub, 1);
    UtAssert_UINT32_EQ(ModList.ListLen, 3);

    UtAssert_VOIDCALL(CFE_PSP_ModuleInitList(&ModList, 0xB0000, UT_STATIC_MODULE_LIST2));
    UtAssert_STUB_COUNT(InitStub, 2);
    UtAssert_UINT32_EQ(ModList.ListLen, 2);
}

void Test_CFE_PSP_ModuleInit(void)
{
    /* Test Case for:
     * void CFE_PSP_ModuleInit(void)
     */
    UtAssert_VOIDCALL(CFE_PSP_ModuleInit());
}

void Test_CFE_PSP_Module_GetAPIEntry(void)
{
    /* Test Case for:
     * int32 CFE_PSP_Module_GetAPIEntry(uint32 PspModuleId, CFE_PSP_ModuleApi_t **API)
     */
    CFE_PSP_ModuleApi_t *API;

    CFE_PSP_MODULE_LIST_GLOBAL.Std =
        (CFE_PSP_ModuleListWrapper_t) {.BasePtr = UT_STATIC_MODULE_LIST1, .ListLen = 3, .BaseId = 0xAFF00};
    CFE_PSP_MODULE_LIST_GLOBAL.Ext =
        (CFE_PSP_ModuleListWrapper_t) {.BasePtr = UT_STATIC_MODULE_LIST2, .ListLen = 2, .BaseId = 0xA0000};

    UtAssert_INT32_EQ(CFE_PSP_Module_GetAPIEntry(0, &API), CFE_PSP_INVALID_MODULE_ID);
    UtAssert_NULL(API);

    UtAssert_INT32_EQ(CFE_PSP_Module_GetAPIEntry(0xA0001, &API), CFE_PSP_SUCCESS);
    UtAssert_NOT_NULL(API);
    UtAssert_INT32_EQ(CFE_PSP_Module_GetAPIEntry(0xA7FFF, &API), CFE_PSP_INVALID_MODULE_ID);
    UtAssert_NULL(API);

    UtAssert_INT32_EQ(CFE_PSP_Module_GetAPIEntry(0xAFF01, &API), CFE_PSP_SUCCESS);
    UtAssert_NOT_NULL(API);
    UtAssert_INT32_EQ(CFE_PSP_Module_GetAPIEntry(0xAFFFF, &API), CFE_PSP_INVALID_MODULE_ID);
    UtAssert_NULL(API);
}

/* CFE_PSP_ModuleApi_t *CFE_PSP_Module_LookupTableEntry(const CFE_PSP_ModuleListWrapper_t *WrapPtr, uint32 Index) */

void Test_CFE_PSP_Module_SearchNameInList(void)
{
    /* Test Case for:
     * uint32 CFE_PSP_Module_SearchNameInList(const CFE_PSP_ModuleListWrapper_t *WrapPtr, const char *ModuleName)
     * const char *ModuleName);
     */
    uint32                      Id;
    CFE_PSP_ModuleListWrapper_t ModList = {.BasePtr = UT_STATIC_MODULE_LIST1, .ListLen = 3, .BaseId = 0xC0000};

    UtAssert_ZERO(CFE_PSP_Module_SearchNameInList(&ModList, "DoesNotExist"));
    UtAssert_NONZERO(Id = CFE_PSP_Module_SearchNameInList(&ModList, "UT2"));
    UtAssert_UINT32_EQ(Id, 0xC0001);
    UtAssert_NONZERO(Id = CFE_PSP_Module_SearchNameInList(&ModList, "UT3"));
    UtAssert_UINT32_EQ(Id, 0xC0002);
}

void Test_CFE_PSP_Module_FindByName(void)
{
    /* Test Case for:
     * int32 CFE_PSP_Module_FindByName(const char *ModuleName, uint32 *PspModuleId)
     */
    uint32 ModuleId;

    CFE_PSP_MODULE_LIST_GLOBAL.Std =
        (CFE_PSP_ModuleListWrapper_t) {.BasePtr = UT_STATIC_MODULE_LIST1, .ListLen = 3, .BaseId = 0xDFF00};
    CFE_PSP_MODULE_LIST_GLOBAL.Ext =
        (CFE_PSP_ModuleListWrapper_t) {.BasePtr = UT_STATIC_MODULE_LIST2, .ListLen = 2, .BaseId = 0xD0000};

    UtAssert_INT32_EQ(CFE_PSP_Module_FindByName("NameDoesNotExist", &ModuleId), CFE_PSP_INVALID_MODULE_NAME);

    UtAssert_INT32_EQ(CFE_PSP_Module_FindByName("UT3", &ModuleId), CFE_PSP_SUCCESS);
    UtAssert_UINT32_EQ(ModuleId, 0xDFF02);
    UtAssert_INT32_EQ(CFE_PSP_Module_FindByName("UT4", &ModuleId), CFE_PSP_SUCCESS);
    UtAssert_UINT32_EQ(ModuleId, 0xD0000);
}
