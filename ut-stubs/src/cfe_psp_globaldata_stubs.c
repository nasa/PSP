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
** Purpose:
** Unit test stubs for BSP routines
**
** Notes:
** Minimal work is done, only what is required for unit testing
**
*/

/*
** Includes
*/

#include "cfe_psp.h"
#include "utstubs.h"
#include <string.h>

#include "target_config.h"

Target_CfeConfigData GLOBAL_CFE_CONFIGDATA = {0};

/**
 * Instantiation of global system-wide configuration struct
 * This contains build info plus pointers to the PSP and CFE
 * configuration structures.  Everything will be linked together
 * in the final executable.
 */
Target_ConfigData GLOBAL_CONFIGDATA = {.MissionVersion       = "MissionUnitTest",
                                       .CfeVersion           = "CfeUnitTest",
                                       .OsalVersion          = "OsalUnitTest",
                                       .Config               = "MissionConfig",
                                       .Date                 = "MissionBuildDate",
                                       .User                 = "MissionBuildUser",
                                       .Default_CpuName      = "UnitTestCpu",
                                       .Default_CpuId        = 1,
                                       .Default_SpacecraftId = 0x42,
                                       .CfeConfig            = &GLOBAL_CFE_CONFIGDATA};
