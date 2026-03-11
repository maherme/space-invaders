/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "bullet.h"

#define BULLET_WIDTH 1
#define BULLET_HEIGHT 4

struct bullet_instance_t
{
    sprite_t sprite;
};

static const char bulletImage[BULLET_HEIGHT][BULLET_WIDTH][4] = {{W}, {W}, {W}, {W}};

bullet_t
bulletCreate(int x, int y)
{
    bullet_t inst = utilsCalloc(1, sizeof(struct bullet_instance_t));
    inst->sprite.x = x;
    inst->sprite.y = y;
    inst->sprite.width = BULLET_WIDTH;
    inst->sprite.height = BULLET_HEIGHT;
    inst->sprite.image = (const char *)bulletImage;
    inst->sprite.pixels_to_move = 1;
    inst->sprite.time_to_move = 2 * NS_PER_MS;
    graphCreateImage(&inst->sprite);
    inst->sprite.max_movement.up = WINDOW_HEIGHT - inst->sprite.scaled_height;

    return inst;
}
