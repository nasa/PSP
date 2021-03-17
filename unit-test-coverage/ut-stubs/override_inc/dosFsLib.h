/*
 *      Copyright (c) 2019, United States government as represented by the
 *      administrator of the National Aeronautics Space Administration.
 *      All rights reserved. This software was created at NASA Goddard
 *      Space Flight Center pursuant to government contracts.
 *
 *      This is governed by the NASA Open Source Agreement and may be used,
 *      distributed and modified only according to the terms of that agreement.
 */

/* PSP coverage stub replacement for dosFsLib.h */
#ifndef _PSP_OVERRIDE_DOSFSLIB_H_
#define _PSP_OVERRIDE_DOSFSLIB_H_

#include "PCS_dosFsLib.h"
#include <vxWorks.h>

/* ----------------------------------------- */
/* mappings for declarations in dosFsLib.h */
/* ----------------------------------------- */
#define DOS_CHK_ONLY        PCS_DOS_CHK_ONLY
#define DOS_CHK_REPAIR      PCS_DOS_CHK_REPAIR
#define DOS_CHK_VERB_0      PCS_DOS_CHK_VERB_0
#define DOS_CHK_VERB_SILENT PCS_DOS_CHK_VERB_SILENT
#define DOS_OPT_BLANK       PCS_DOS_OPT_BLANK

#define dosFsVolFormat PCS_dosFsVolFormat

#endif /* _PSP_OVERRIDE_DOSFSLIB_H_ */
