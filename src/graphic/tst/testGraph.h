/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __TESTGRAPH_H__
#define __TESTGRAPH_H__

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "graph.h"

void
testGraphCreateImageFail(void **status);

void
testGraphCreateImageSuccess(void **status);

void
testGraphGetSpriteFail(void **status);

void
testGraphGetSpriteSuccess(void **status);

void
testGraphPrintImageFail(void **status);

void
testGraphPrintImageSuccess(void **status);

void
testGraphDestroyObjectNullParameter(void **status);

void
testGraphDestroyObjectSuccess(void **status);

#endif
