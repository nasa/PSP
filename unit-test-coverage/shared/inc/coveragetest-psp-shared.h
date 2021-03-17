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
 * \file     psp-shared-coveragetest.h
 * \ingroup  vxworks
 * \author   joseph.p.hickey@nasa.gov
 *
 */

#ifndef INCLUDE_PSP_SHARED_COVERAGETEST_H_
#define INCLUDE_PSP_SHARED_COVERAGETEST_H_

#include "utassert.h"
#include "uttest.h"
#include "utstubs.h"

void Test_CFE_PSP_Exception_GetBuffer(void);
void Test_CFE_PSP_Exception_GetNextContextBuffer(void);
void Test_CFE_PSP_Exception_GetSummary(void);
void Test_CFE_PSP_Exception_CopyContext(void);

#endif /* INCLUDE_PSP_SHARED_COVERAGETEST_H_ */
