/*
 *      Copyright (c) 2019, United States government as represented by the
 *      administrator of the National Aeronautics Space Administration.
 *      All rights reserved. This software was created at NASA Goddard
 *      Space Flight Center pursuant to government contracts.
 *
 *      This is governed by the NASA Open Source Agreement and may be used,
 *      distributed and modified only according to the terms of that agreement.
 */

/* PSP coverage stub replacement for sys/types.h */
#ifndef _PSP_OVERRIDE_SYS_TYPES_H_
#define _PSP_OVERRIDE_SYS_TYPES_H_

#include "PCS_sys_types.h"

/* ----------------------------------------- */
/* mappings for declarations in sys/types.h */
/* ----------------------------------------- */
#define ssize_t PCS_ssize_t
#define off_t   PCS_off_t
#define mode_t  PCS_mode_t
#define pid_t   PCS_pid_t
#define gid_t   PCS_gid_t
#define uid_t   PCS_uid_t

#endif /* _PSP_OVERRIDE_SYS_TYPES_H_ */
