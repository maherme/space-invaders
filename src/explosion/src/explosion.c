/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "explosion.h"

#define EXPLOSION_BULLET_WIDTH 8
#define EXPLOSION_BULLET_HEIGHT 8
#define EXPLOSION_UFO_WIDTH 24
#define EXPLOSION_UFO_HEIGHT 8

struct explosion_instance_t
{
    sprite_t sprite;
    struct timespec creation_time;
    long long explosion_time;
    explosion_type_t type;
};

struct explosion
{
    struct explosion_instance_t *explosion;
    struct explosion *next;
};

static struct explosion *head = NULL;

static const struct explosion_bullet
{
    const char image[EXPLOSION_BULLET_HEIGHT][EXPLOSION_BULLET_WIDTH][4];
    const int image_width;
    const int image_height;
    const long long explosion_time;
} explosion_bullet = {.image = {{B, B, R, B, R, B, B, B},
                                {B, R, R, R, B, B, B, B},
                                {B, B, R, R, R, B, R, B},
                                {B, R, R, R, R, R, B, B},
                                {B, B, R, R, R, B, B, B},
                                {B, B, B, R, B, B, R, B},
                                {B, B, R, B, B, R, B, B},
                                {R, B, B, B, R, B, B, R}},
                      .image_width = EXPLOSION_BULLET_WIDTH,
                      .image_height = EXPLOSION_BULLET_HEIGHT,
                      .explosion_time = 500 * NS_PER_MS};

static const struct explosion_ufo
{
    const char image[EXPLOSION_UFO_HEIGHT][EXPLOSION_UFO_WIDTH][4];
    const int image_width;
    const int image_height;
    const long long explosion_time;
} explosion_ufo = {.image = {{B, B, B, B, B, B, B, B, B, B, B, R, B, R, B, B, B, B, B, B, B, B, B, B},
                             {B, B, B, R, R, R, R, R, B, B, B, B, B, B, B, B, R, R, R, R, R, B, B, B},
                             {B, B, R, R, R, R, R, R, R, B, B, B, R, B, B, R, R, R, R, R, R, R, B, B},
                             {B, B, R, B, R, B, R, R, B, B, R, B, B, R, B, B, R, R, B, R, B, R, B, B},
                             {B, R, R, R, R, R, R, R, B, R, B, B, B, B, R, B, R, R, R, R, R, R, R, B},
                             {R, R, R, R, R, R, R, B, B, R, B, B, B, B, B, B, R, R, R, R, R, R, R, R},
                             {B, B, B, B, R, R, R, R, B, B, B, R, R, B, B, B, R, R, R, R, B, B, B, B},
                             {B, B, B, B, B, B, R, B, B, B, B, B, B, B, R, B, B, R, B, B, B, B, B, B}},
                   .image_width = EXPLOSION_UFO_WIDTH,
                   .image_height = EXPLOSION_UFO_HEIGHT,
                   .explosion_time = 500 * NS_PER_MS};

static int
setExplosionType(struct explosion_instance_t *instance, explosion_type_t type)
{
    instance->type = type;
    switch (type)
    {
        case EXPLOSION_BULLET:
            instance->sprite.width = explosion_bullet.image_width;
            instance->sprite.height = explosion_bullet.image_height;
            instance->sprite.image = (char *)explosion_bullet.image;
            instance->explosion_time = explosion_bullet.explosion_time;
            break;
        case EXPLOSION_UFO:
            instance->sprite.width = explosion_ufo.image_width;
            instance->sprite.height = explosion_ufo.image_height;
            instance->sprite.image = (char *)explosion_ufo.image;
            instance->explosion_time = explosion_ufo.explosion_time;
            break;
        default:
            return 1;
            break;
    }

    return 0;
}

void
explosionCreate(int x, int y, explosion_type_t type)
{
    struct explosion *new_explosion = utilsCalloc(1, sizeof(struct explosion));
    struct explosion_instance_t *inst = utilsCalloc(1, sizeof(struct explosion_instance_t));
    if (setExplosionType(inst, type))
    {
        utilsFree((void **)&new_explosion);
        utilsFree((void **)&inst);
        return;
    }
    inst->sprite.x = x;
    inst->sprite.y = y;
    inst->sprite.pixels_to_move = 0;
    inst->sprite.time_to_move = 0;
    graphCreateImage(&inst->sprite);
    clock_gettime(CLOCK_MONOTONIC, &inst->creation_time);
    graphRegisterPrint(graphGetSprite((base_t *)inst));
    new_explosion->explosion = inst;
    new_explosion->next = head;
    head = new_explosion;
}

static bool
explosionTimeout(struct explosion_instance_t *this)
{
    assert(this); // GCOV_EXCL_LINE

    if (utilsCheckTimeout(this->creation_time, this->explosion_time))
    {
        graphUnregisterPrint(graphGetSprite((base_t *)this));
        graphDestroyObject((base_t **)&this);
        return true;
    }

    return false;
}

void
explosionsDestroy(void)
{
    struct explosion *current = head;
    struct explosion *prev = NULL;

    while (current)
    {
        if (explosionTimeout(current->explosion))
        {
            if (!prev)
            {
                head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            struct explosion *tmp = current;
            current = current->next;
            utilsFree((void **)&tmp);
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
}

#ifdef UNIT_TESTING
void
helperUT_explosionResetList(void)
{
    while (head)
    {
        struct explosion *tmp = head;
        head = head->next;

        free(tmp->explosion);
        free(tmp);
    }
}
#endif /* UNIT_TESTING */
