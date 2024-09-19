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
**  Author:  A. Cudmore
**
**  Purpose:  This file contains the cFE Platform Support Package(PSP)
**            prototypes.
**            The PSP routines serve as the "glue" between the RTOS and
**            the cFE Flight Software. The routines fill gaps that are not
**            really considered part of the OS Abstraction, but are required
**            for the cFE flight software implementation. It is possible that
**            some of these routines could migrate into the OS AL.
**
*/

#ifndef CFE_PSP_H
#define CFE_PSP_H

/******************************************************************************
 INCLUDE FILES
 ******************************************************************************/

#include "common_types.h"
#include "osapi.h"

/*
 * All PSP API sub-components
 *
 * Historically these were all declared as part of a monolithic cfe_psp.h header file
 * Breaking them up aids in unit testability, allowing each sub-component to be tested
 * individually - particulary important for items where the implementation was moved to
 * a module.  The whole API is included here for backward compatibilty.
 */
#include "cfe_psp_cache_api.h"
#include "cfe_psp_cds_api.h"
#include "cfe_psp_eepromaccess_api.h"
#include "cfe_psp_error.h"
#include "cfe_psp_exception_api.h"
#include "cfe_psp_id_api.h"
#include "cfe_psp_memaccess_api.h"
#include "cfe_psp_memrange_api.h"
#include "cfe_psp_port_api.h"
#include "cfe_psp_ssr_api.h"
#include "cfe_psp_timertick_api.h"
#include "cfe_psp_version_api.h"
#include "cfe_psp_watchdog_api.h"

/******************************************************************************
 FUNCTION PROTOTYPES
 ******************************************************************************/

/*
** PSP entry point
*/
/*--------------------------------------------------------------------------------------*/
/**
 * @brief PSP Entry Point to initialize the OSAL and start up the cFE
 *
 * This is the entry point that the real-time OS calls to start our software.
 * This routine will do any BSP/OS-specific setup, then call the entry point of
 * the flight software (i.e. the cFE main entry point).
 *
 * @note The flight software (i.e. cFE) should not call this routine.
 */
void CFE_PSP_Main(void);

#endif
