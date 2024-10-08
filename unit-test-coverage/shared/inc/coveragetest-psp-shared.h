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
 *
 *    Copyright (c) 2020, United States government as represented by the
 *    administrator of the National Aeronautics Space Administration.
 *    All rights reserved. This software was created at NASA Goddard
 *    Space Flight Center pursuant to government contracts.
 *
 *    This is governed by the NASA Open Source Agreement and may be used,
 *    distributed and modified only according to the terms of that agreement.
 *
 */

/**
 * \file
 * \ingroup  vxworks
 * \author   joseph.p.hickey@nasa.gov
 *
 */

#ifndef COVERAGETEST_PSP_SHARED_H
#define COVERAGETEST_PSP_SHARED_H

#include "utassert.h"
#include "uttest.h"
#include "utstubs.h"

void Test_CFE_PSP_StatusToString(void);

void Test_CFE_PSP_GetVersionString(void);
void Test_CFE_PSP_GetVersionCodeName(void);
void Test_CFE_PSP_GetVersionNumber(void);
void Test_CFE_PSP_GetBuildNumber(void);

void Test_CFE_PSP_Exception_GetBuffer(void);
void Test_CFE_PSP_Exception_GetNextContextBuffer(void);
void Test_CFE_PSP_Exception_GetSummary(void);
void Test_CFE_PSP_Exception_CopyContext(void);

void Test_CFE_PSP_ModuleInitList(void);
void Test_CFE_PSP_ModuleInit(void);
void Test_CFE_PSP_Module_GetAPIEntry(void);
void Test_CFE_PSP_Module_SearchNameInList(void);
void Test_CFE_PSP_Module_FindByName(void);

void Test_CFE_PSP_MemCpy(void);
void Test_CFE_PSP_MemSet(void);

void Test_CFE_PSP_MemValidateRange(void);
void Test_CFE_PSP_MemRanges(void);
void Test_CFE_PSP_MemRangeSet(void);
void Test_CFE_PSP_MemRangeGet(void);

#endif
