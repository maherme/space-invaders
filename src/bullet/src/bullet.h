/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __BULLET_H__
#define __BULLET_H__

#include "graph.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct bullet_instance_t *bullet_t;

bullet_t
bulletCreate(int x, int y);

#endif
