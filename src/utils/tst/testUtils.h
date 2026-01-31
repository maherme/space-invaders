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

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <errno.h>
#include <stdbool.h>
#include "utils.h"

void
testUtilsCallocFail(void **status);

void
testUtilsCallocSuccess(void **status);

void
testUtilsFreeFail(void **status);

void
testUtilsFreeSuccess(void **status);

#endif
