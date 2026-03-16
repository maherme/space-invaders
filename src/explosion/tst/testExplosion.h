/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __TESTEXPLOSION_H__
#define __TESTEXPLOSION_H__

int
setup(void **state);

void
testExplosionCreate(void **status);

void
testExplosionsDestroyListEmpty(void **status);

void
testExplosionsDestroyTimeoutFalse(void **status);

void
testExplosionsDestroyTimeoutTrue(void **status);

void
testExplosionsDestroyTwoExplosions(void **status);

#endif
