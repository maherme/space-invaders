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
#include <stdbool.h>

#define SPACESHIP_WIDTH 13
#define SPACESHIP_HEIGHT 8

struct spaceship_instance_t
{
    sprite_t sprite;
    bool alive;
};

static struct spaceship_instance_t spaceship;

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
    spaceship_t inst = &spaceship;
    inst->sprite.x = x;
    inst->sprite.y = y;
    inst->sprite.width = SPACESHIP_WIDTH;
    inst->sprite.height = SPACESHIP_HEIGHT;
    inst->sprite.image = (const char *)spaceshipImage;
    inst->sprite.pixels_to_move = 1;
    inst->sprite.time_to_move = 1000 / 60 * NS_PER_MS;
    inst->sprite.max_movement.right = GAME_WIDTH;
    inst->sprite.max_movement.left = 0;
    inst->sprite.layer = LAYER_GAME_OBJECTS;
    inst->sprite.visible = true;
    graphRegisterPrint(&inst->sprite);
    inst->alive = true;

    return inst;
}

void
spaceshipDestroy(spaceship_t spaceship)
{
    if (!spaceship)
    {
        return;
    }

    sprite_t *spaceship_sprite = graphGetSprite((base_t *)spaceship);
    graphUnregisterPrint(spaceship_sprite);
    spaceship->alive = false;
}

bool
spaceshipAlive(spaceship_t spaceship)
{
    return (spaceship && spaceship->alive);
}

#ifdef UNIT_TESTING
#include <string.h>

spaceship_t
helperUT_spaceshipGetInstance(void)
{
    spaceship_t inst = &spaceship;
    memset(inst, 0, sizeof(*inst));

    inst->alive = true;

    return inst;
}

void
helperUT_spaceshipSetAlive(spaceship_t spaceship, bool alive)
{
    spaceship->alive = alive;
}
#endif /* UNIT_TESTING */
