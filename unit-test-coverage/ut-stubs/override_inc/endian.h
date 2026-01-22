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

/* PSP coverage stub replacement for endian.h */
#ifndef OVERRIDE_ENDIAN_H
#define OVERRIDE_ENDIAN_H

#include "PCS_endian.h"

#define htobe16 PCS_htobe16
#define htole16 PCS_htole16
#define be16toh PCS_be16toh
#define le16toh PCS_le16toh

#define htobe32 PCS_htobe32
#define htole32 PCS_htole32
#define be32toh PCS_be32toh
#define le32toh PCS_le32toh

#define htobe64 PCS_htobe64
#define htole64 PCS_htole64
#define be64toh PCS_be64toh
#define le64toh PCS_le64toh

#endif /* OVERRIDE_ENDIAN_H */
