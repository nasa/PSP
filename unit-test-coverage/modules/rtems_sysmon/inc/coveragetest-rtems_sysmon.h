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
 * \ingroup  coveragetest-rtems_sysmon
 * \author   anh.d.van@nasa.gov
 *
 */

#ifndef COVERAGETEST_RTEMS_SYSMON_H
#define COVERAGETEST_RTEMS_SYSMON_H

#include "utassert.h"
#include "uttest.h"
#include "utstubs.h"

#include "iodriver_analog_io.h"
#include "iodriver_base.h"
#include "iodriver_impl.h"

#include "../../../ut-stubs/override_inc/rtems.h"
#include "../../../ut-stubs/override_inc/rtems/score/threadimpl.h"
#include "rtems_sysmon.h"

/*
 * Macro to add a test case to the list of tests to execute
 */
#define ADD_TEST(test) UtTest_Add(test, ModuleTest_ResetState, NULL, #test)


#endif
