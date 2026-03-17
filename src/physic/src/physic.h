/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __PHYSIC_H__
#define __PHYSIC_H__

#include "graph.h"
#include <stdbool.h>

typedef enum
{
    UP,
    DOWN,
    RIGHT,
    LEFT,
    INVALID_DIR
} direction_t;

void
physicMoveSprite(sprite_t *sprite, direction_t direction);

bool
physicCheckBorderCollision(const sprite_t *const sprite);

bool
physicCheckSpritesBoxCollision(const sprite_t *const sprite1, const sprite_t *const sprite2);

#endif
