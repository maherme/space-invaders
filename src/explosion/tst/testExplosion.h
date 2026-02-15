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

#include "explosion.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

int
setup(void **state);

void
testExplosionCreateInvalidType(void **status);

void
testExplosionCreateBullet(void **status);

void
testExplosionCreateUfo(void **status);

void
testExplosionsDestroyListEmpty(void **status);

void
testExplosionsDestroyTimeoutFalse(void **status);

void
testExplosionsDestroyTimeoutTrue(void **status);

void
testExplosionsDestroyTwoExplosions(void **status);

#endif
