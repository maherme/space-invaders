/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __TESTBULLET_H__
#define __TESTBULLET_H__

int
setup(void **state);

void
testBulletCreate(void **status);

void
testBulletCreateAllTypeBulletAlien(void **status);

void
testBulletCreateTwoBulletSpaceship(void **status);

void
testBulletDestroyNullParameter(void **status);

void
testBulletDestroy(void **status);

void
testBulletUsedNullParameter(void **status);

void
testBulletUsedFalse(void **status);

void
testBulletUsedTrue(void **status);

void
testBulletGetTypeNullParameters(void **status);

void
testBulletGetType(void **status);

void
testBulletCallFunctionForEachNullParameter(void **status);

void
testBulletCallFunctionForEachBulletPoolEmpty(void **status);

void
testBulletCallFunctionForEach(void **status);

void
testBulletAlienInhibit(void **status);

void
testBulletNoneUsedTrue(void **status);

void
testBulletNoneUsedFalse(void **status);

#endif
