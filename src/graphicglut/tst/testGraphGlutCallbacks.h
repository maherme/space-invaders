/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __TESTGRAPHGLUTCALLBACKS_H__
#define __TESTGRAPHGLUTCALLBACKS_H__

#include "graphGlutCallbacks.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

int
setup(void **state);

void
testGraphRegisterPrintFailNullParameter(void **status);

void
testGraphRegisterPrintFailMaxCallbacks(void **status);

void
testGraphRegisterPrintSuccess(void **status);

void
testGraphUnregisterPrintFailNullParameter(void **status);

void
testGraphUnregisterPrintFailMaxCallbacks(void **status);

void
testGraphUnregisterPrintSuccess(void **status);

void
testGraphGlutReshape(void **status);

#endif
