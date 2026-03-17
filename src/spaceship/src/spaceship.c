/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "spaceship.h"
#include "graph.h"
#include "graphGlutCallbacks.h"
#include "utils.h"

#define SPACESHIP_WIDTH 13
#define SPACESHIP_HEIGHT 8

struct spaceship_instance_t
{
    sprite_t sprite;
};

static const char spaceshipImage[SPACESHIP_HEIGHT][SPACESHIP_WIDTH][NUM_RGBA_CHANNELS] = {
    {B, B, B, B, B, B, G, B, B, B, B, B, B},
    {B, B, B, B, B, G, G, G, B, B, B, B, B},
    {B, B, B, B, B, G, G, G, B, B, B, B, B},
    {B, G, G, G, G, G, G, G, G, G, G, G, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, G, G, B, B, B, B, B, G, G, B, B},
    {B, G, G, G, G, B, B, B, G, G, G, G, B},
};

spaceship_t
spaceshipCreate(int x, int y)
{
    spaceship_t inst = utilsCalloc(1, sizeof(struct spaceship_instance_t));
    inst->sprite.x = x;
    inst->sprite.y = y;
    inst->sprite.width = SPACESHIP_WIDTH;
    inst->sprite.height = SPACESHIP_HEIGHT;
    inst->sprite.image = (const char *)spaceshipImage;
    inst->sprite.pixels_to_move = SPACESHIP_WIDTH / 4;
    inst->sprite.time_to_move = 1000 / 60 * NS_PER_MS;
    graphScaleImage(&inst->sprite);
    graphCreateImage(&inst->sprite);
    inst->sprite.max_movement.right = WINDOW_WIDTH - inst->sprite.scaled_width;
    inst->sprite.max_movement.left = 0;
    graphRegisterPrint(&inst->sprite);

    return inst;
}
