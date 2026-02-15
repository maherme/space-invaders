/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include "graph.h"
#include "graphGlutCallbacks.h"
#include "utils.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    EXPLOSION_BULLET,
    EXPLOSION_UFO,
    MAX_EXPLOSION_TYPE
} explosion_type_t;

void
explosionCreate(int x, int y, explosion_type_t type);

void
explosionsDestroy(void);

#ifdef UNIT_TESTING
void
helperUT_explosionResetList(void);
#endif /* UNIT_TESTING */

#endif /* __EXPLOSION_H__ */
