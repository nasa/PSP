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
 * \file
 *
 * A PSP module to satisfy the "Port" API on systems which
 * do not have or otherwise cannot access I/O ports.
 *
 * All functions return CFE_PSP_ERR_NOT_IMPLEMENTED
 */

#include "cfe_psp.h"
#include "cfe_psp_module.h"

CFE_PSP_MODULE_DECLARE_SIMPLE(port_notimpl);

void port_notimpl_Init(uint32 PspModuleId)
{
    /* Inform the user that this module is in use */
    printf("CFE_PSP: I/O Port access not implemented\n");
}

int32 CFE_PSP_PortRead8(cpuaddr PortAddress, uint8 *ByteValue)
{
    return (CFE_PSP_ERROR_NOT_IMPLEMENTED);
}

int32 CFE_PSP_PortWrite8(cpuaddr PortAddress, uint8 ByteValue)
{
    return (CFE_PSP_ERROR_NOT_IMPLEMENTED);
}

int32 CFE_PSP_PortRead16(cpuaddr PortAddress, uint16 *uint16Value)
{
    return (CFE_PSP_ERROR_NOT_IMPLEMENTED);
}

int32 CFE_PSP_PortWrite16(cpuaddr PortAddress, uint16 uint16Value)
{
    return (CFE_PSP_ERROR_NOT_IMPLEMENTED);
}

int32 CFE_PSP_PortRead32(cpuaddr PortAddress, uint32 *uint32Value)
{
    return (CFE_PSP_ERROR_NOT_IMPLEMENTED);
}

int32 CFE_PSP_PortWrite32(cpuaddr PortAddress, uint32 uint32Value)
{
    return (CFE_PSP_ERROR_NOT_IMPLEMENTED);
}
