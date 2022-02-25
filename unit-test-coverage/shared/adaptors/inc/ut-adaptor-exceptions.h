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
 * \file
 * \ingroup  adaptors
 * \author   joseph.p.hickey@nasa.gov
 *
 */

#ifndef UT_ADAPTOR_EXCEPTIONS_H
#define UT_ADAPTOR_EXCEPTIONS_H

#include "common_types.h"
#include "cfe_psp_exceptionstorage_api.h"

uint32 UT_Get_Exception_MaxEntries(void);
size_t UT_Get_Exception_Size(void);
uint32 UT_Get_Exception_Id(struct CFE_PSP_Exception_LogData *Buffer);
void   UT_Generate_Exception_Context(struct CFE_PSP_Exception_LogData *Buffer, size_t Size);

#endif
