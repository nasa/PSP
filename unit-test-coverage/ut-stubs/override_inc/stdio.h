/*
 *      Copyright (c) 2019, United States government as represented by the
 *      administrator of the National Aeronautics Space Administration.
 *      All rights reserved. This software was created at NASA Goddard
 *      Space Flight Center pursuant to government contracts.
 *
 *      This is governed by the NASA Open Source Agreement and may be used,
 *      distributed and modified only according to the terms of that agreement.
 */

/* PSP coverage stub replacement for stdio.h */
#ifndef _PSP_OVERRIDE_STDIO_H_
#define _PSP_OVERRIDE_STDIO_H_

#include "PCS_stdio.h"

/* ----------------------------------------- */
/* mappings for declarations in stdio.h */
/* ----------------------------------------- */

#define FILE        PCS_FILE
#define fclose      PCS_fclose
#define fgets       PCS_fgets
#define fopen       PCS_fopen
#define fputs       PCS_fputs
#define remove      PCS_remove
#define rename      PCS_rename
#define snprintf    PCS_snprintf
#define vsnprintf   PCS_vsnprintf
#define printf(...) PCS_printf(__VA_ARGS__)
#define putchar     PCS_putchar

#define stdin  PCS_stdin
#define stdout PCS_stdout
#define stderr PCS_stderr

#endif /* _PSP_OVERRIDE_STDIO_H_ */
