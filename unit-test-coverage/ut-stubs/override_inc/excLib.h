/*
 *      Copyright (c) 2019, United States government as represented by the
 *      administrator of the National Aeronautics Space Administration.
 *      All rights reserved. This software was created at NASA Goddard
 *      Space Flight Center pursuant to government contracts.
 *
 *      This is governed by the NASA Open Source Agreement and may be used,
 *      distributed and modified only according to the terms of that agreement.
 */

/* PSP coverage stub replacement for excLib.h */
#ifndef _PSP_OVERRIDE_EXCLIB_H_
#define _PSP_OVERRIDE_EXCLIB_H_

#include <vxWorks.h>
#include "PCS_excLib.h"

/* -----------------------------------------  */
/* mappings for declarations in excLib.h */
/* -----------------------------------------  */
#define excHookAdd PCS_excHookAdd

#endif /* _PSP_OVERRIDE_EXCLIB_H_ */
