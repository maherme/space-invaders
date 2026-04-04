/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __TESTUTILS_H__
#define __TESTUTILS_H__

void
testUtilsCallocFail(void **status);

void
testUtilsCallocSuccess(void **status);

void
testUtilsCheckTimeoutNegativeTimeoutParameter(void **status);

void
testUtilsCheckTimeoutExact(void **status);

void
testUtilsCheckTimeoutBefore(void **status);

void
testUtilsCheckTimeoutZero(void **status);

void
testUtilsCheckTimeoutFuture(void **status);

#endif
