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

/* PSP coverage stub replacement for bsdnet.h */
#ifndef PCS_BSDNET_H
#define PCS_BSDNET_H

#include "PCS_basetypes.h"
#include "PCS_rtems.h"

extern int         PCS_rtems_fxp_attach(struct PCS_rtems_bsdnet_ifconfig *, int);
extern void        PCS_rtems_bsdnet_do_dhcp_failsafe(void);
extern int         PCS_rtems_bsdnet_initialize_network(void);
extern const char *PCS_rtems_status_text(PCS_rtems_status_code);

#endif
