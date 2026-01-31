/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __TESTSPACESHIP_H__
#define __TESTSPACESHIP_H__

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdbool.h>

void
testSpaceshipCreate(void **status);

void
testSpaceshipGetSpriteFail(void **status);

void
testSpaceshipGetSpriteSuccess(void **status);

#endif
