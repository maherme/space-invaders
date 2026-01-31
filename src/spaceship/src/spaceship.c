/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "spaceship.h"

struct spaceship_instance_t {
    sprite_t sprite;
};

static const char spaceshipImage[SPACESHIP_HEIGHT][SPACESHIP_WIDTH][4] = {
    {B, B, B, B, B, B, G, B, B, B, B, B, B},
    {B, B, B, B, B, G, G, G, B, B, B, B, B},
    {B, B, B, B, B, G, G, G, B, B, B, B, B},
    {B, G, G, G, G, G, G, G, G, G, G, G, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
};

spaceship_t
spaceshipCreate(int x, int y){
    spaceship_t inst = utilsCalloc(1, sizeof(struct spaceship_instance_t));
    inst->sprite.x = x;
    inst->sprite.y = y;
    inst->sprite.width = SPACESHIP_WIDTH;
    inst->sprite.height = SPACESHIP_HEIGHT;
    inst->sprite.image = (const char *)spaceshipImage;
    inst->sprite.pixels_to_move = SPACESHIP_WIDTH/4;
    inst->sprite.time_to_move = 1000/60;
    graphCreateImage(&inst->sprite);

    return inst;
}
