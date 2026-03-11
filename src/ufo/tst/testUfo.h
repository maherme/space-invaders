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

#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

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
