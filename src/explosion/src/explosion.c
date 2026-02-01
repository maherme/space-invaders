/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "explosion.h"

#define EXPLOSION_WIDTH     8
#define EXPLOSION_HEIGHT    8

struct explosion_instance_t {
    sprite_t sprite;
    struct timespec creation_time;
    long long explosion_time;
};

static const char explosionImage[EXPLOSION_HEIGHT][EXPLOSION_WIDTH][4] = {
    {B, B, R, B, R, B, B, B},
    {B, R, R, R, B, B, B, B},
    {B, B, R, R, R, B, R, B},
    {B, R, R, R, R, R, B, B},
    {B, B, R, R, R, B, B, B},
    {B, B, B, R, B, B, R, B},
    {B, B, R, B, B, R, B, B},
    {R, B, B, B, R, B, B, R}
};

explosion_t
explosionCreate(int x, int y){
    explosion_t inst = utilsCalloc(1, sizeof(struct explosion_instance_t));
    inst->sprite.x = x;
    inst->sprite.y = y;
    inst->sprite.width = EXPLOSION_WIDTH;
    inst->sprite.height = EXPLOSION_HEIGHT;
    inst->sprite.image = (const char *)explosionImage;
    inst->sprite.pixels_to_move = 0;
    inst->sprite.time_to_move = 0;
    graphCreateImage(&inst->sprite);
    inst->explosion_time = 500000000LL;
    clock_gettime(CLOCK_MONOTONIC, &inst->creation_time);

    return inst;
}

bool
explosionTimeout(explosion_t this) {
    if(!this) {
        return false;
    }

    struct timespec current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    long long delta_time = (current_time.tv_sec - this->creation_time.tv_sec) * 1000000000LL +
                           (current_time.tv_nsec - this->creation_time.tv_nsec);
    if(delta_time >= this->explosion_time) {
        return true;
    }

    return false;
}
