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

/**
 * @file
 *
 * Auto-Generated stub implementations for functions defined in cfe_psp_eepromaccess_api header
 */

#include "cfe_psp_eepromaccess_api.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_EepromPowerDown()
 * ----------------------------------------------------
 */
int32 CFE_PSP_EepromPowerDown(uint32 Bank)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_EepromPowerDown, int32);

    UT_GenStub_AddParam(CFE_PSP_EepromPowerDown, uint32, Bank);

    UT_GenStub_Execute(CFE_PSP_EepromPowerDown, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_EepromPowerDown, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_EepromPowerUp()
 * ----------------------------------------------------
 */
int32 CFE_PSP_EepromPowerUp(uint32 Bank)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_EepromPowerUp, int32);

    UT_GenStub_AddParam(CFE_PSP_EepromPowerUp, uint32, Bank);

    UT_GenStub_Execute(CFE_PSP_EepromPowerUp, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_EepromPowerUp, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_EepromWrite16()
 * ----------------------------------------------------
 */
int32 CFE_PSP_EepromWrite16(cpuaddr MemoryAddress, uint16 uint16Value)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_EepromWrite16, int32);

    UT_GenStub_AddParam(CFE_PSP_EepromWrite16, cpuaddr, MemoryAddress);
    UT_GenStub_AddParam(CFE_PSP_EepromWrite16, uint16, uint16Value);

    UT_GenStub_Execute(CFE_PSP_EepromWrite16, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_EepromWrite16, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_EepromWrite32()
 * ----------------------------------------------------
 */
int32 CFE_PSP_EepromWrite32(cpuaddr MemoryAddress, uint32 uint32Value)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_EepromWrite32, int32);

    UT_GenStub_AddParam(CFE_PSP_EepromWrite32, cpuaddr, MemoryAddress);
    UT_GenStub_AddParam(CFE_PSP_EepromWrite32, uint32, uint32Value);

    UT_GenStub_Execute(CFE_PSP_EepromWrite32, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_EepromWrite32, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_EepromWrite8()
 * ----------------------------------------------------
 */
int32 CFE_PSP_EepromWrite8(cpuaddr MemoryAddress, uint8 ByteValue)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_EepromWrite8, int32);

    UT_GenStub_AddParam(CFE_PSP_EepromWrite8, cpuaddr, MemoryAddress);
    UT_GenStub_AddParam(CFE_PSP_EepromWrite8, uint8, ByteValue);

    UT_GenStub_Execute(CFE_PSP_EepromWrite8, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_EepromWrite8, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_EepromWriteDisable()
 * ----------------------------------------------------
 */
int32 CFE_PSP_EepromWriteDisable(uint32 Bank)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_EepromWriteDisable, int32);

    UT_GenStub_AddParam(CFE_PSP_EepromWriteDisable, uint32, Bank);

    UT_GenStub_Execute(CFE_PSP_EepromWriteDisable, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_EepromWriteDisable, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_EepromWriteEnable()
 * ----------------------------------------------------
 */
int32 CFE_PSP_EepromWriteEnable(uint32 Bank)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_EepromWriteEnable, int32);

    UT_GenStub_AddParam(CFE_PSP_EepromWriteEnable, uint32, Bank);

    UT_GenStub_Execute(CFE_PSP_EepromWriteEnable, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_EepromWriteEnable, int32);
}
