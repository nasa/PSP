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
 * \file     ut-adaptor-bootrec.h
 * \ingroup  adaptors
 * \author   joseph.p.hickey@nasa.gov
 *
 */

#ifndef INCLUDE_UT_ADAPTOR_BOOTREC_H_
#define INCLUDE_UT_ADAPTOR_BOOTREC_H_

#include "common_types.h"

void   UT_Setup_ReservedMem_BootRec(void);
uint32 UT_Get_ReservedMem_BootType(void);
void   UT_Set_ReservedMem_BootType(uint32 reset_type);

#endif /* INCLUDE_UT_ADAPTOR_BOOTREC_H_ */
