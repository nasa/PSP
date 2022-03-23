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

/* PSP coverage stub replacement for dosFsLib.h */
#ifndef PCS_DOSFSLIB_H
#define PCS_DOSFSLIB_H

#include "PCS_basetypes.h"
#include "PCS_vxWorks.h"

/* ----------------------------------------- */
/* constants normally defined in dosFsLib.h */
/* ----------------------------------------- */
#define PCS_DOS_CHK_ONLY        0x00000001
#define PCS_DOS_CHK_REPAIR      0x00000002
#define PCS_DOS_CHK_VERB_0      0x0000ff00 /* verbosity level/flags */
#define PCS_DOS_CHK_VERB_SILENT PCS_DOS_CHK_VERB_0
#define PCS_DOS_OPT_BLANK       0x0002 /* create a clean boot block */

/* ----------------------------------------- */
/* types normally defined in dosFsLib.h */
/* ----------------------------------------- */

/* ----------------------------------------- */
/* prototypes normally declared in dosFsLib.h */
/* ----------------------------------------- */
extern PCS_STATUS PCS_dosFsVolFormat(char *path, int opt, PCS_FUNCPTR pPromptFunc);

#endif
