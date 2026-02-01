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

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "explosion.h"

void
testExplosionCreate(void **status);

void
testExplosionTimeoutNullParameter(void **status);

void
testExplosionTimeoutTrue(void **status);

void
testExplosionTimeoutFalse(void **status);

#endif
