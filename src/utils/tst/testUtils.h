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

#include "utils.h"
#include <cmocka.h>
#include <errno.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void
testUtilsCallocFail(void **status);

void
testUtilsCallocSuccess(void **status);

void
testUtilsFreeFail(void **status);

void
testUtilsFreeSuccess(void **status);

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
