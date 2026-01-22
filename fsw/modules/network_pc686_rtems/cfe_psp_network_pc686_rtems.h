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

 #ifndef CFE_PSP_NETWORK_PC686_RTEMS_H
 #define CFE_PSP_NETWORK_PC686_RTEMS_H

/* Parameters needed for network initialization */
static unsigned char ethernet_address[6] = {0x00, 0x04, 0x9F, 0x00, 0x27, 0x61};
static char          net_name_str[]      = "fxp1";
static char          ip_addr_str[]       = "10.0.2.15";
static char          ip_netmask_str[]    = "255.255.255.0";

#endif /* CFE_PSP_NETWORK_PC686_RTEMS_H */