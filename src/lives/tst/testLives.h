/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __TESTLIVES_H__
#define __TESTLIVES_H__

void
testLivesCreate(void **status);

void
testLivesRemoveLastLive(void **status);

void
testLivesRemovePenultimateLive(void **status);

void
testLivesRemoveMaxLivesPrinted(void **status);

void
testLivesRemoveZeroLives(void **status);

void
testLivesAdd(void **status);

void
testLivesAddMaxLivesPrinted(void **status);

void
testLivesAddZeroLives(void **status);

#endif /* __TESTLIVES_H__ */
