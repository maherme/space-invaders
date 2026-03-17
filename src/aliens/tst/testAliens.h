/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __TESTALIENS_H__
#define __TESTALIENS_H__

void
testAliensCreate(void **status);

void
testAlienDestroyNullParameter(void **status);

void
testAlienDestroy(void **status);

void
testAliensGetAlienInstanceInvalidIndex(void **status);

#endif /* __TESTALIENS_H__ */
