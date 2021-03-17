/*
 *      Copyright (c) 2019, United States government as represented by the
 *      administrator of the National Aeronautics Space Administration.
 *      All rights reserved. This software was created at NASA Goddard
 *      Space Flight Center pursuant to government contracts.
 *
 *      This is governed by the NASA Open Source Agreement and may be used,
 *      distributed and modified only according to the terms of that agreement.
 */

/* PSP coverage stub replacement for stdlib.h */
#ifndef _PSP_OVERRIDE_STDLIB_H_
#define _PSP_OVERRIDE_STDLIB_H_

#include "PCS_stdlib.h"

/* ----------------------------------------- */
/* mappings for declarations in stdlib.h */
/* ----------------------------------------- */

#define EXIT_SUCCESS PCS_EXIT_SUCCESS
#define EXIT_FAILURE PCS_EXIT_FAILURE
#define exit         PCS_exit
#define strtoul      PCS_strtoul
#define system       PCS_system
#define malloc       PCS_malloc
#define free         PCS_free

#endif /* _PSP_OVERRIDE_STDLIB_H_ */
