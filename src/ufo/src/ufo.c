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

#define UFO_WIDTH 16
#define UFO_HEIGHT 8

struct ufo_instance_t
{
    sprite_t sprite;
    direction_t direction;
    long long time_to_appear;
};

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
        ufo->sprite.x = -UFO_WIDTH * 2;
    }
    else
    {
        ufo->sprite.x = WINDOW_WIDTH;
    }

    ufo->sprite.y = WINDOW_HEIGHT - 32;
}

ufo_t
ufoCreate(void)
{
    ufo_t inst = utilsCalloc(1, sizeof(struct ufo_instance_t));
    calculateDirection(inst);
    calculateStartingCoord(inst);
    inst->sprite.width = UFO_WIDTH;
    inst->sprite.height = UFO_HEIGHT;
    inst->sprite.image = (const char *)ufoImage;
    inst->sprite.pixels_to_move = 1;
    inst->sprite.time_to_move = 20 * NS_PER_MS;
    inst->time_to_appear = 5 * NS_PER_S;
    graphScaleImage(&inst->sprite);
    graphCreateImage(&inst->sprite);
    inst->sprite.max_movement.right = WINDOW_WIDTH + 1;
    inst->sprite.max_movement.left = -(inst->sprite.scaled_width + 1);
    graphUpdateTimeSprite(&inst->sprite);
    graphRegisterPrint(&inst->sprite);

    return inst;
}

void
ufoDestroy(ufo_t *ufo)
{
    if (!ufo || !*ufo)
    {
        return;
    }

    sprite_t *ufo_sprite = graphGetSprite((base_t *)*ufo);
    graphUnregisterPrint(ufo_sprite);
    graphDestroyImage(ufo_sprite);
    utilsFree((void **)ufo);
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
    if (!ufo)
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
