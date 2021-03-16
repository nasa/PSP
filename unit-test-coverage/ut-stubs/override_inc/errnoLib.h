/*
 *      Copyright (c) 2019, United States government as represented by the
 *      administrator of the National Aeronautics Space Administration.
 *      All rights reserved. This software was created at NASA Goddard
 *      Space Flight Center pursuant to government contracts.
 *
 *      This is governed by the NASA Open Source Agreement and may be used,
 *      distributed and modified only according to the terms of that agreement.
 */

/* PSP coverage stub replacement for errnoLib.h */
#ifndef _PSP_OVERRIDE_ERRNOLIB_H_
#define _PSP_OVERRIDE_ERRNOLIB_H_

#include "PCS_errnoLib.h"
#include <vxWorks.h>

/* -----------------------------------------  */
/* mappings for declarations in errnoLib.h */
/* -----------------------------------------  */
#define errnoGet PCS_errnoGet

#endif /* _PSP_OVERRIDE_ERRNOLIB_H_ */
