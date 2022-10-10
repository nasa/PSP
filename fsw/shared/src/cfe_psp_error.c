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
 * Implements error APIs
 */
#include <stdio.h>

#include "cfe_psp_error.h"

/*----------------------------------------------------------------
 *
 *  Purpose: Implemented per public PSP API
 *           See description in API and header file for detail
 *
 *-----------------------------------------------------------------*/
char *CFE_PSP_StatusToString(CFE_PSP_Status_t status, CFE_PSP_StatusString_t *status_string)
{
    char *string = NULL;

    if (status_string != NULL)
    {
        snprintf(*status_string, sizeof(*status_string), "%ld", (long)status);
        string = *status_string;
    }
    return string;
}
