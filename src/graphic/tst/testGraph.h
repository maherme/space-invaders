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

#include "graph.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

void
testGraphCreateImageFail(void **status);

void
testGraphCreateImageSuccess(void **status);

void
testGraphGetSpriteFail(void **status);

void
testGraphGetSpriteSuccess(void **status);

void
testGraphGetSpriteCoordinatesNullParameters(void **status);

void
testGraphGetSpriteCoordinates(void **status);

void
testGraphUpdateTimeSpriteNullParameter(void **status);

void
testGraphUpdateTimeSprite(void **status);

void
testGraphPrintImageFail(void **status);

void
testGraphPrintImageSuccess(void **status);

void
testGraphDestroyObjectNullParameter(void **status);

void
testGraphDestroyObjectSuccess(void **status);

#endif
