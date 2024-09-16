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
 * Auto-Generated stub implementations for functions defined in cfe_psp_module header
 */

#include "cfe_psp_module.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_ModuleInit()
 * ----------------------------------------------------
 */
void CFE_PSP_ModuleInit(void)
{

    UT_GenStub_Execute(CFE_PSP_ModuleInit, Basic, NULL);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_Module_FindByName()
 * ----------------------------------------------------
 */
int32 CFE_PSP_Module_FindByName(const char *ModuleName, uint32 *PspModuleId)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_Module_FindByName, int32);

    UT_GenStub_AddParam(CFE_PSP_Module_FindByName, const char *, ModuleName);
    UT_GenStub_AddParam(CFE_PSP_Module_FindByName, uint32 *, PspModuleId);

    UT_GenStub_Execute(CFE_PSP_Module_FindByName, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_Module_FindByName, int32);
}

/*
 * ----------------------------------------------------
 * Generated stub function for CFE_PSP_Module_GetAPIEntry()
 * ----------------------------------------------------
 */
int32 CFE_PSP_Module_GetAPIEntry(uint32 PspModuleId, CFE_PSP_ModuleApi_t **API)
{
    UT_GenStub_SetupReturnBuffer(CFE_PSP_Module_GetAPIEntry, int32);

    UT_GenStub_AddParam(CFE_PSP_Module_GetAPIEntry, uint32, PspModuleId);
    UT_GenStub_AddParam(CFE_PSP_Module_GetAPIEntry, CFE_PSP_ModuleApi_t **, API);

    UT_GenStub_Execute(CFE_PSP_Module_GetAPIEntry, Basic, NULL);

    return UT_GenStub_GetReturnValue(CFE_PSP_Module_GetAPIEntry, int32);
}
