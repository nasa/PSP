/*
 *      Copyright (c) 2019, United States government as represented by the
 *      administrator of the National Aeronautics Space Administration.
 *      All rights reserved. This software was created at NASA Goddard
 *      Space Flight Center pursuant to government contracts.
 *
 *      This is governed by the NASA Open Source Agreement and may be used,
 *      distributed and modified only according to the terms of that agreement.
 */

/* PSP coverage stub replacement for string.h */
#ifndef _PSP_OVERRIDE_STRING_H_
#define _PSP_OVERRIDE_STRING_H_

#include "PCS_string.h"

/* ----------------------------------------- */
/* mappings for declarations in string.h */
/* ----------------------------------------- */
#define memcpy   PCS_memcpy
#define memset   PCS_memset
#define strcmp   PCS_strcmp
#define strcpy   PCS_strcpy
#define strlen   PCS_strlen
#define strncmp  PCS_strncmp
#define strncpy  PCS_strncpy
#define strchr   PCS_strchr
#define strrchr  PCS_strrchr
#define strcat   PCS_strcat
#define strncat  PCS_strncat
#define strerror PCS_strerror

#endif /* _PSP_OVERRIDE_STRING_H_ */
