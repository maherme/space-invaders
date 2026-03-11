/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "ufo.h"

struct ufo_instance_t
{
    sprite_t sprite;
    direction_t direction;
    long long time_to_appear;
};

static const char ufoImage[UFO_HEIGHT][UFO_WIDTH][4] = {
    {B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B}, {B, B, B, B, R, R, R, R, R, R, R, R, B, B, B, B},
    {B, B, B, R, R, R, R, R, R, R, R, R, R, B, B, B}, {B, B, B, R, B, R, B, R, R, B, R, B, R, B, B, B},
    {B, R, R, R, R, R, R, R, R, R, R, R, R, R, R, B}, {R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R},
    {B, B, B, B, B, R, R, R, R, R, R, B, B, B, B, B}, {B, B, B, B, B, B, B, R, R, B, B, B, B, B, B, B},
};

static void
calculateDirection(ufo_t this)
{
    double random = (double)rand() / RAND_MAX;
    int random_direction = (random < 0.5) ? 0 : 1;
    if (random_direction)
    {
        this->direction = RIGHT;
    }
    else
    {
        this->direction = LEFT;
    }
}

static void
calculateStartingCoord(ufo_t this)
{
    if (this->direction == RIGHT)
    {
        this->sprite.x = -UFO_WIDTH * 2;
    }
    else
    {
        this->sprite.x = WINDOW_WIDTH;
    }

    this->sprite.y = WINDOW_HEIGHT - 32;
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
    graphCreateImage(&inst->sprite);
    inst->sprite.max_movement.right = WINDOW_WIDTH + 1;
    inst->sprite.max_movement.left = -(inst->sprite.scaled_width + 1);
    graphUpdateTimeSprite(&inst->sprite);

    return inst;
}

direction_t
ufoGetDirection(const ufo_t this)
{
    if (!this)
    {
        return INVALID_DIR;
    }
    return this->direction;
}

bool
ufoCheckForMoving(ufo_t this)
{
    if (!this)
    {
        return false;
    }

    if (this->time_to_appear == 0)
    {
        return true;
    }

    if (!utilsCheckTimeout(this->sprite.last_update, this->time_to_appear))
    {
        return false;
    }
    else
    {
        this->time_to_appear = 0;
    }

    return true;
}
