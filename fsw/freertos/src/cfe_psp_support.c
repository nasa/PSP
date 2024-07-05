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

#include "target_config.h"

#define CFE_PSP_CPU_ID		(GLOBAL_CONFIGDATA.CpuId)
#define CFE_PSP_CPU_NAME	(GLOBAL_CONFIGDATA.CpuName)
#define CFE_PSP_SPACECRAFT_ID	(GLOBAL_CONFIGDATA.SpacecraftId)


// TODO
void CFE_PSP_FlushCaches(uint32 type, void *address, uint32 size)
{
	/* flush cache of size at address */
}


uint32 CFE_PSP_GetProcessorId(void)
{
	return CFE_PSP_CPU_ID;
}

uint32 CFE_PSP_GetSpacecraftId(void)
{
	return CFE_PSP_SPACECRAFT_ID;
}

const char *CFE_PSP_GetProcessorName(void)
{
	return CFE_PSP_CPU_NAME;
}

