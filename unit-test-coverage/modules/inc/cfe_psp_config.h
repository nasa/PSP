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
 * Stub for "cfe_psp_config.h" to use with coverage testing
 */

#ifndef COVERAGETEST_CFE_PSP_CONFIG_H
#define COVERAGETEST_CFE_PSP_CONFIG_H

#define CFE_PSP_VX_TIMEBASE_PERIOD_NUMERATOR   (UT_PSP_TIMEBASE_VXWORKS_TESTCONFIG.PeriodNumerator)
#define CFE_PSP_VX_TIMEBASE_PERIOD_DENOMINATOR (UT_PSP_TIMEBASE_VXWORKS_TESTCONFIG.PeriodDenominator)

typedef struct
{
    unsigned long PeriodNumerator;
    unsigned long PeriodDenominator;

} UT_PSP_TimeBase_VxWorks_TestConfig_t;

extern UT_PSP_TimeBase_VxWorks_TestConfig_t UT_PSP_TIMEBASE_VXWORKS_TESTCONFIG;

#endif /* COVERAGETEST_CFE_PSP_CONFIG_H */
