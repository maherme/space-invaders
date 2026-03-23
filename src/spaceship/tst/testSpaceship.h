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

void
testSpaceshipCreate(void **status);

void
testSpaceshipDestroyNullParameter(void **status);

void
testSpaceshipDestroy(void **status);

void
testSpaceshipAliveNullParameter(void **status);

void
testSpaceshipAliveFalse(void **status);

void
testSpaceshipAliveTrue(void **status);

#endif
