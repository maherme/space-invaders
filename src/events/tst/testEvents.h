/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __TESTEVENTS_H__
#define __TESTEVENTS_H__

int
setup(void **state);

void
testEventRegister(void **status);

void
testEventAlreadyRegistered(void **status);

void
testEventRegisterInvalidType(void **status);

void
testEventEmit(void **status);

void
testEventEmitNotRegistered(void **status);

void
testEventEmitInvalidType(void **status);

#endif /* __TESTEVENTS_H__ */
