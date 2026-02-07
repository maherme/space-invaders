/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __TESTUFO_H__
#define __TESTUFO_H__

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdbool.h>

void
testUfoCreateLeftDirection(void **status);

void
testUfoCreateRightDirection(void **status);

void
testUfoGetDirectionNullParameter(void **status);

void
testUfoCheckForMovingNullParameter(void **status);

void
testUfoCheckForMovingFalse(void **status);

void
testUfoCheckForMovingTrue(void **status);

void
testUfoCheckForMovingTrueMoreCalls(void **status);

#endif /* __TESTUFO_H__ */
