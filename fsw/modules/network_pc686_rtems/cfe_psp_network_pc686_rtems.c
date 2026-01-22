/************************************************************************
 * NASA Docket No. GSC-19,200-1, and identified as "cFS Draco"
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
 ************************************************************************/

/**
 * \file
 *
 * A PSP module for network initialization for pc686 RTEMS
 *
 */
#include <errno.h>
#include <rtems.h>
#include <rtems/rtems_bsdnet.h>
#include <rtems/rtems_dhcp_failsafe.h>
#include <bsp.h>

#include "cfe_psp.h"
#include "cfe_psp_module.h"
#include "cfe_psp_network_pc686_rtems.h"

extern int rtems_fxp_attach(struct rtems_bsdnet_ifconfig *config, int attaching);

static struct rtems_bsdnet_ifconfig netdriver_config = {
    .name             = net_name_str,
    .attach           = rtems_fxp_attach,
    .next             = NULL,
    .ip_address       = ip_addr_str,
    .ip_netmask       = ip_netmask_str,
    .hardware_address = ethernet_address
    /* more options can follow */
};

struct rtems_bsdnet_config rtems_bsdnet_config = {
    .ifconfig = &netdriver_config, .bootp = rtems_bsdnet_do_dhcp_failsafe, /* fill if DHCP is used*/
};


CFE_PSP_MODULE_DECLARE_SIMPLE(network_pc686_rtems);

/* Module initialization function */
void network_pc686_rtems_Init(uint32 PspModuleId)
{
    rtems_status_code status;

    /* Inform the user that this module is in use */
    printf("CFE_PSP: Using pc686 RTEMS network implementation\n");

    /*
     * Initialize the network.  This is also optional and only
     * works if an appropriate network device is present.
     */
    status = rtems_bsdnet_initialize_network();
    if (status != RTEMS_SUCCESSFUL)
    {
        printf("Network init not successful: %s / %s (continuing)\n", rtems_status_text(status), strerror(errno));
    }

}