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

void
testGraphCreateImageNullParameter(void **status);

void
testGraphCreateImageSuccess(void **status);

void
testGraphDestroyImageNullParameter(void **status);

void
testGraphDestroyImage(void **status);

void
testGraphGetSpriteFail(void **status);

void
testGraphGetSpriteSuccess(void **status);

void
testGraphGetSpriteCoordinatesNullParameters(void **status);

void
testGraphGetSpriteCoordinates(void **status);

void
testGraphUpdateImageToPrintNullParameter(void **status);

void
testGraphUpdateImageToPrintOneFrame(void **status);

void
testGraphUpdateImageToPrintMoreOneFrame(void **status);

void
testGraphUpdateTimeSpriteNullParameter(void **status);

void
testGraphUpdateTimeSprite(void **status);

void
testGraphPrintImageNullParameter(void **status);

void
testGraphPrintImageVisibleFalse(void **status);

void
testGraphPrintImageSuccess(void **status);

void
testGraphUpdateSpriteNullParameter(void **status);

void
testGraphUpdateSprite(void **status);

void
testGraphPrintGameBorder(void **status);

#endif
