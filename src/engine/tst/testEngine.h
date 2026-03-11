/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __TESTENGINE_H__
#define __TESTENGINE_H__

#include "engine.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

int
setup(void **state);

void
testEngineRegisterFailNullParameter(void **status);

void
testEngineRegisterFailMaxCallbacks(void **status);

void
testEngineRegisterSuccess(void **status);

void
testEngineUnregisterFailNullParameter(void **status);

void
testEngineUnregisterNoCallbackFound(void **status);

void
testEngineUnregisterSuccess(void **status);

#endif
