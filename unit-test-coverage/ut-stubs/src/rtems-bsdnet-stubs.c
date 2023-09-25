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

/* PSP coverage stub replacement for rtems_bsdnet.h */
#include <stdlib.h>
#include "utstubs.h"

#include "PCS_bsdnet.h"
#include "PCS_rtems.h"

void PCS_rtems_bsdnet_do_dhcp_failsafe(void)
{
    UT_DEFAULT_IMPL(PCS_rtems_bsdnet_do_dhcp_failsafe);
}

const char *PCS_rtems_status_text(PCS_rtems_status_code code)
{
    const char *ReturnCode = NULL;
    int32       Status;

    Status = UT_DEFAULT_IMPL(PCS_rtems_status_text);
    if (Status == 0)
    {
        UT_Stub_CopyToLocal(UT_KEY(PCS_rtems_status_text), &ReturnCode, sizeof(ReturnCode));
    }

    return ReturnCode;
}

int PCS_rtems_bsdnet_initialize_network(void)
{
    return UT_DEFAULT_IMPL(PCS_rtems_bsdnet_initialize_network);
}

int PCS_rtems_fxp_attach(struct PCS_rtems_bsdnet_ifconfig *config, int attaching)
{
    return UT_DEFAULT_IMPL(PCS_rtems_fxp_attach);
}