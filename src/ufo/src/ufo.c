/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "ufo.h"
#include "graph.h"
#include "graphGlutCallbacks.h"
#include "physic.h"
#include "utils.h"
#include <stdbool.h>
#include <stdlib.h>

#define UFO_WIDTH 16
#define UFO_HEIGHT 8

struct ufo_instance_t
{
    sprite_t sprite;
    direction_t direction;
    long long time_to_appear;
    bool alive;
};

static struct ufo_instance_t ufo;

static const char ufoImage[UFO_HEIGHT][UFO_WIDTH][NUM_RGBA_CHANNELS] = {
    {B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
    {B, B, B, B, R, R, R, R, R, R, R, R, B, B, B, B},
    {B, B, B, R, R, R, R, R, R, R, R, R, R, B, B, B},
    {B, B, B, R, B, R, B, R, R, B, R, B, R, B, B, B},
    {B, R, R, R, R, R, R, R, R, R, R, R, R, R, R, B},
    {R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R},
    {B, B, B, B, B, R, R, R, R, R, R, B, B, B, B, B},
    {B, B, B, B, B, B, B, R, R, B, B, B, B, B, B, B},
};

static void
calculateDirection(ufo_t ufo)
{
    double random = (double)rand() / RAND_MAX;
    int random_direction = (random < 0.5) ? 0 : 1;
    if (random_direction)
    {
        ufo->direction = RIGHT;
    }
    else
    {
        ufo->direction = LEFT;
    }
}

static void
calculateStartingCoord(ufo_t ufo)
{
    if (ufo->direction == RIGHT)
    {
        ufo->sprite.x = -ufo->sprite.width;
    }
    else
    {
        ufo->sprite.x = WINDOW_WIDTH;
    }

    ufo->sprite.y = WINDOW_HEIGHT - 16;
}

ufo_t
ufoCreate(void)
{
    ufo_t inst = &ufo;
    calculateDirection(inst);
    inst->sprite.width = UFO_WIDTH;
    inst->sprite.height = UFO_HEIGHT;
    inst->sprite.image = (const char *)ufoImage;
    inst->sprite.pixels_to_move = 1;
    inst->sprite.time_to_move = 1000 / 60 * NS_PER_MS;
    inst->time_to_appear = 5 * NS_PER_S;
    calculateStartingCoord(inst);
    inst->sprite.max_movement.right = WINDOW_WIDTH + inst->sprite.width + 1;
    inst->sprite.max_movement.left = -(inst->sprite.width + 1);
    inst->sprite.layer = LAYER_GAME_OBJECTS;
    graphUpdateTimeSprite(&inst->sprite);
    graphRegisterPrint(&inst->sprite);
    inst->alive = true;

    return inst;
}

void
ufoDestroy(ufo_t ufo)
{
    if (!ufo)
    {
        return;
    }

    sprite_t *ufo_sprite = graphGetSprite((base_t *)ufo);
    graphUnregisterPrint(ufo_sprite);
    ufo->alive = false;
}

bool
ufoAlive(ufo_t ufo)
{
    return ufo && ufo->alive;
}

direction_t
ufoGetDirection(const ufo_t ufo)
{
    if (!ufo)
    {
        return INVALID_DIR;
    }
    return ufo->direction;
}

bool
ufoCheckForMoving(ufo_t ufo)
{
    if (!ufo || !ufo->alive)
    {
        return false;
    }

    if (ufo->time_to_appear == 0)
    {
        return true;
    }

    if (!utilsCheckTimeout(ufo->sprite.last_update, ufo->time_to_appear))
    {
        return false;
    }
    else
    {
        ufo->time_to_appear = 0;
    }

    return true;
}

#ifdef UNIT_TESTING
#include <string.h>

ufo_t
helperUT_ufoGetInstance(void)
{
    ufo_t inst = &ufo;
    memset(inst, 0, sizeof(*inst));

    inst->alive = true;

    return inst;
}

void
helperUT_ufoSetAlive(ufo_t ufo, bool alive)
{
    ufo->alive = alive;
}

void
helperUT_ufoSetTimeToAppear(ufo_t ufo, long long time)
{
    ufo->time_to_appear = time;
}
#endif /* UNIT_TESTING */
