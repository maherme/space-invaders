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

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "graphGlutCallbacks.h"

int
setup(void ** state);

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
