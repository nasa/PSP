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
 * Auto-Generated stub implementations for functions defined in PCS_netinet_in header
 */

#include "PCS_netinet_in.h"
#include "utgenstub.h"

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_htonl()
 * ----------------------------------------------------
 */
uint32_t PCS_htonl(uint32_t hostlong)
{
    UT_GenStub_SetupReturnBuffer(PCS_htonl, uint32_t);

    UT_GenStub_AddParam(PCS_htonl, uint32_t, hostlong);

    UT_GenStub_Execute(PCS_htonl, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_htonl, uint32_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_htons()
 * ----------------------------------------------------
 */
uint16_t PCS_htons(uint16_t hostshort)
{
    UT_GenStub_SetupReturnBuffer(PCS_htons, uint16_t);

    UT_GenStub_AddParam(PCS_htons, uint16_t, hostshort);

    UT_GenStub_Execute(PCS_htons, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_htons, uint16_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_ntohl()
 * ----------------------------------------------------
 */
uint32_t PCS_ntohl(uint32_t netlong)
{
    UT_GenStub_SetupReturnBuffer(PCS_ntohl, uint32_t);

    UT_GenStub_AddParam(PCS_ntohl, uint32_t, netlong);

    UT_GenStub_Execute(PCS_ntohl, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_ntohl, uint32_t);
}

/*
 * ----------------------------------------------------
 * Generated stub function for PCS_ntohs()
 * ----------------------------------------------------
 */
uint16_t PCS_ntohs(uint16_t netshort)
{
    UT_GenStub_SetupReturnBuffer(PCS_ntohs, uint16_t);

    UT_GenStub_AddParam(PCS_ntohs, uint16_t, netshort);

    UT_GenStub_Execute(PCS_ntohs, Basic, NULL);

    return UT_GenStub_GetReturnValue(PCS_ntohs, uint16_t);
}
