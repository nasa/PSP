/*
 *
 *    Copyright (c) 2020, United States government as represented by the
 *    administrator of the National Aeronautics Space Administration.
 *    All rights reserved. This software was created at NASA Goddard
 *    Space Flight Center pursuant to government contracts.
 *
 *    This is governed by the NASA Open Source Agreement and may be used,
 *    distributed and modified only according to the terms of that agreement.
 *
 */

/**
 * \file     vxWorks.h
 * \ingroup  ut-stubs
 * \author   joseph.p.hickey@nasa.gov
 *
 */

#ifndef INCLUDE_VXWORKS_H_
#define INCLUDE_VXWORKS_H_

#include "PCS_vxWorks.h"

#define IMPORT

/* ----------------------------------------- */
/* mappings for declarations in vxWorks.h */
/* ----------------------------------------- */
#define ERROR        PCS_ERROR
#define OK           PCS_OK
#define WAIT_FOREVER PCS_WAIT_FOREVER
#define NO_WAIT      PCS_NO_WAIT

#define STATUS      PCS_STATUS
#define BOOL        PCS_BOOL
#define FUNCPTR     PCS_FUNCPTR
#define VOIDFUNCPTR PCS_VOIDFUNCPTR

#define UINT   PCS_UINT
#define INT8   PCS_INT8
#define UINT8  PCS_UINT8
#define INT16  PCS_INT16
#define UINT16 PCS_UINT16
#define INT32  PCS_INT32
#define UINT32 PCS_UINT32

#define _Vx_usr_arg_t PCS_Vx_usr_arg_t

#endif /* INCLUDE_VXWORKS_H_ */
