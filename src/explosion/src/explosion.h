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

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "utils.h"
#include "graph.h"

typedef struct explosion_instance_t *explosion_t;

explosion_t
explosionCreate(int x, int y);

bool
explosionTimeout(explosion_t this);

#ifdef UNIT_TESTING
struct timespec
helperUT_explosionGetCreationTime(explosion_t this);

long long
helperUT_explosionGetExplosionTime(explosion_t this);
#endif /* UNIT_TESTING */

#endif /* __EXPLOSION_H__ */
