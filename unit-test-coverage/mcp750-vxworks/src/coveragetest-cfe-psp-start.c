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
 * \file     coveragetest-binsem.c
 * \ingroup  vxworks
 * \author   joseph.p.hickey@nasa.gov
 *
 */

#include "coveragetest-psp-mcp750-vxworks.h"
#include "ut-adaptor-bootrec.h"

#include "cfe_psp.h"

#include "PCS_sysLib.h"
#include "PCS_mcpx750.h"
#include "PCS_stdlib.h"
#include "PCS_cfe_configdata.h"

extern void UT_OS_Application_Startup(void);
extern void UT_OS_Application_Run(void);

uint32 UT_ReservedMemBuffer[256];

typedef struct
{
    uint32 StartType;
    uint32 StartSubtype;
} PSP_UT_StartType_t;

/*
 * A hook function that can check/verify the  reset sub type
 */
static int32 Test_Hook_ResetSubType(void *UserObj, int32 StubRetcode, uint32 CallCount, const UT_StubContext_t *Context)
{
    PSP_UT_StartType_t *UserBuffer = UserObj;
    UserBuffer->StartType          = UT_Hook_GetArgValueByName(Context, "StartType", uint32);
    UserBuffer->StartSubtype       = UT_Hook_GetArgValueByName(Context, "StartSubtype", uint32);
    return StubRetcode;
}

void Test_OS_Application_Startup(void)
{
    /*
     * Test Case For:
     * void OS_Application_Startup(void)
     *
     * NOTE: The UT assert library itself defines OS_Application_Startup
     * To avoid conflict with the UT assert, the unit under test is renamed
     * to "UT_OS_Application_Startup" using a preprocessor definition
     */
    PSP_UT_StartType_t StartType;

    /* Install a hook function to grab the start type parameters from the system main call */
    UT_SetHookFunction(UT_KEY(PCS_SystemMain), Test_Hook_ResetSubType, &StartType);
    UT_Setup_ReservedMem_BootRec();

    /* nominal */
    UT_SetDataBuffer(UT_KEY(PCS_sysMemTop), UT_ReservedMemBuffer, sizeof(UT_ReservedMemBuffer), false);
    UT_OS_Application_Startup();
    UtAssert_INT32_EQ(UT_GetStubCount(UT_KEY(OS_printf)), 4);
    UtAssert_INT32_EQ(UT_GetStubCount(UT_KEY(PCS_SystemMain)), 1);
    UtAssert_INT32_EQ(StartType.StartType, CFE_PSP_RST_TYPE_POWERON);
    UtAssert_INT32_EQ(StartType.StartSubtype, CFE_PSP_RST_SUBTYPE_UNDEFINED_RESET);

    /* failure of OS_API_Init */
    UT_SetDefaultReturnValue(UT_KEY(OS_API_Init), OS_ERROR);
    UT_OS_Application_Startup();
    UtAssert_INT32_EQ(UT_GetStubCount(UT_KEY(PCS_exit)), 1);
    UT_ClearDefaultReturnValue(UT_KEY(OS_API_Init));

    /* failure of OS_FileSysAddFixedMap - an extra OS_printf */
    UT_SetDefaultReturnValue(UT_KEY(OS_FileSysAddFixedMap), OS_ERROR);
    UT_OS_Application_Startup();
    UtAssert_INT32_EQ(UT_GetStubCount(UT_KEY(OS_printf)), 9);
    UtAssert_INT32_EQ(UT_GetStubCount(UT_KEY(PCS_SystemMain)), 2);
    UT_ClearDefaultReturnValue(UT_KEY(OS_FileSysAddFixedMap));

    /* coverage for each of the reset types */
    *PCS_SYS_REG_BLRR = PCS_SYS_REG_BLRR_PWRON;
    UT_OS_Application_Startup();
    UtAssert_INT32_EQ(UT_GetStubCount(UT_KEY(PCS_SystemMain)), 3);
    UtAssert_INT32_EQ(StartType.StartType, CFE_PSP_RST_TYPE_POWERON);
    UtAssert_INT32_EQ(StartType.StartSubtype, CFE_PSP_RST_SUBTYPE_POWER_CYCLE);

    *PCS_SYS_REG_BLRR = PCS_SYS_REG_BLRR_PBRST;
    UT_OS_Application_Startup();
    UtAssert_INT32_EQ(UT_GetStubCount(UT_KEY(PCS_SystemMain)), 4);
    UtAssert_INT32_EQ(StartType.StartType, CFE_PSP_RST_TYPE_POWERON);
    UtAssert_INT32_EQ(StartType.StartSubtype, CFE_PSP_RST_SUBTYPE_PUSH_BUTTON);

    *PCS_SYS_REG_BLRR = PCS_SYS_REG_BLRR_FBTN;
    UT_OS_Application_Startup();
    UtAssert_INT32_EQ(UT_GetStubCount(UT_KEY(PCS_SystemMain)), 5);
    UtAssert_INT32_EQ(StartType.StartType, CFE_PSP_RST_SUBTYPE_PUSH_BUTTON);
    UtAssert_INT32_EQ(StartType.StartSubtype, 3);

    *PCS_SYS_REG_BLRR = PCS_SYS_REG_BLRR_WDT2;
    UT_OS_Application_Startup();
    UtAssert_INT32_EQ(UT_GetStubCount(UT_KEY(PCS_SystemMain)), 6);
    UtAssert_INT32_EQ(StartType.StartType, CFE_PSP_RST_TYPE_PROCESSOR);
    UtAssert_INT32_EQ(StartType.StartSubtype, CFE_PSP_RST_SUBTYPE_HW_WATCHDOG);

    *PCS_SYS_REG_BLRR = PCS_SYS_REG_BLRR_SWSRST;
    UT_OS_Application_Startup();
    UtAssert_INT32_EQ(UT_GetStubCount(UT_KEY(PCS_SystemMain)), 7);
    UtAssert_INT32_EQ(StartType.StartType, CFE_PSP_RST_TYPE_PROCESSOR);
    UtAssert_INT32_EQ(StartType.StartSubtype, CFE_PSP_RST_SUBTYPE_RESET_COMMAND);

    *PCS_SYS_REG_BLRR = PCS_SYS_REG_BLRR_SWHRST;
    UT_Set_ReservedMem_BootType(CFE_PSP_RST_TYPE_POWERON);
    UT_OS_Application_Startup();
    UtAssert_INT32_EQ(UT_GetStubCount(UT_KEY(PCS_SystemMain)), 8);
    UtAssert_INT32_EQ(StartType.StartType, CFE_PSP_RST_TYPE_POWERON);
    UtAssert_INT32_EQ(StartType.StartSubtype, CFE_PSP_RST_SUBTYPE_RESET_COMMAND);

    UT_Set_ReservedMem_BootType(CFE_PSP_RST_TYPE_PROCESSOR);
    UT_OS_Application_Startup();
    UtAssert_INT32_EQ(UT_GetStubCount(UT_KEY(PCS_SystemMain)), 9);
    UtAssert_INT32_EQ(StartType.StartType, CFE_PSP_RST_TYPE_PROCESSOR);
    UtAssert_INT32_EQ(StartType.StartSubtype, CFE_PSP_RST_SUBTYPE_RESET_COMMAND);
}

void Test_OS_Application_Run(void)
{
    /*
     * Test Case For:
     * void OS_Application_Run(void)
     *
     * NOTE: The UT assert library itself defines OS_Application_Run
     * To avoid conflict with the UT assert, the unit under test is renamed
     * to "UT_OS_Application_Run" using a preprocessor definition
     */

    /* The function currently contains an infinite loop so cannot be tested now */
}
