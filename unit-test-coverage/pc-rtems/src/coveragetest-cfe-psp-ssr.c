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

#include "coveragetest-psp-pc-rtems.h"

#include "cfe_psp.h"

void Test_CFE_PSP_InitSSR(void)
{
    uint32 bus          = 1;
    uint32 device       = 1;
    char   DeviceName[] = "TestDevice";

    /* Placeholder test to exercise function - amend tests if/when function is fully implemented */
    UtAssert_INT32_EQ(CFE_PSP_InitSSR(bus, device, DeviceName), CFE_PSP_SUCCESS);
}