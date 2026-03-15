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

int
setup(void **state);

void
testGraphRegisterPrintFailNullParameter(void **status);

void
testGraphRegisterPrintSuccess(void **status);

void
testGraphUnregisterPrintFailNullParameter(void **status);

void
testGraphUnregisterPrintNoCallbacksFound(void **status);

void
testGraphUnregisterPrintSuccessOneCallback(void **status);

void
testGraphUnregisterPrintSuccessLastCallback(void **status);

void
testGraphUnregisterPrintSuccessMiddleCallback(void **status);

void
testGraphGlutReshape(void **status);

#endif
