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
#ifndef CFE_PSP_ERROR_H
#define CFE_PSP_ERROR_H

/**
 * \file
 * \brief cFE PSP Error header
 */

#include "common_types.h"

/**
 * \brief PSP Status type for readability and potentially type safety
 */
typedef int32 CFE_PSP_Status_t;

/**
 * \brief PSP Status macro for literal
 */
#define CFE_PSP_STATUS_C(X) ((CFE_PSP_Status_t)(X))

/**
 * \brief PSP Status converted to string length limit
 *
 * Used for sizing CFE_PSP_StatusString_t intended for use in printing CFE_PSP_Status_t values
 * Sized for %ld (LONG_MIN) including NULL
 */
#define CFE_PSP_STATUS_STRING_LENGTH 12

/**
 * @brief For the @ref CFE_PSP_StatusToString() function, to ensure
 * everyone is making an array of the same length.
 */
typedef char CFE_PSP_StatusString_t[CFE_PSP_STATUS_STRING_LENGTH];

/**
 * @brief Convert status to a string
 *
 * @param[in] status Status value to convert
 * @param[out] status_string Buffer to store status converted to string
 *
 * @return Passed in string pointer
 */
char *CFE_PSP_StatusToString(CFE_PSP_Status_t status, CFE_PSP_StatusString_t *status_string);

/*
 * Error and return codes
 */
#define CFE_PSP_SUCCESS                  (CFE_PSP_STATUS_C(0))
#define CFE_PSP_ERROR                    (CFE_PSP_STATUS_C(-1))
#define CFE_PSP_INVALID_POINTER          (CFE_PSP_STATUS_C(-2))
#define CFE_PSP_ERROR_ADDRESS_MISALIGNED (CFE_PSP_STATUS_C(-3))
#define CFE_PSP_ERROR_TIMEOUT            (CFE_PSP_STATUS_C(-4))
#define CFE_PSP_INVALID_INT_NUM          (CFE_PSP_STATUS_C(-5))
#define CFE_PSP_INVALID_MEM_ADDR         (CFE_PSP_STATUS_C(-21))
#define CFE_PSP_INVALID_MEM_TYPE         (CFE_PSP_STATUS_C(-22))
#define CFE_PSP_INVALID_MEM_RANGE        (CFE_PSP_STATUS_C(-23))
#define CFE_PSP_INVALID_MEM_WORDSIZE     (CFE_PSP_STATUS_C(-24))
#define CFE_PSP_INVALID_MEM_SIZE         (CFE_PSP_STATUS_C(-25))
#define CFE_PSP_INVALID_MEM_ATTR         (CFE_PSP_STATUS_C(-26))
#define CFE_PSP_ERROR_NOT_IMPLEMENTED    (CFE_PSP_STATUS_C(-27))
#define CFE_PSP_INVALID_MODULE_NAME      (CFE_PSP_STATUS_C(-28))
#define CFE_PSP_INVALID_MODULE_ID        (CFE_PSP_STATUS_C(-29))
#define CFE_PSP_NO_EXCEPTION_DATA        (CFE_PSP_STATUS_C(-30))

#endif /* CFE_PSP_ERROR_H */
