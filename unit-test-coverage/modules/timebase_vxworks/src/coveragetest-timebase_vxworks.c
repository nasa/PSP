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
**  Function:  CFE_PSP_Get_Timebase()
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
