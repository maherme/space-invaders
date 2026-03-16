/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "explosion.h"
#include "graph.h"
#include "graphGlutCallbacks.h"
#include "list.h"
#include "utils.h"
#include <assert.h>
#include <stdbool.h>

#define EXPLOSION_BULLET_WIDTH 8
#define EXPLOSION_BULLET_HEIGHT 8
#define EXPLOSION_UFO_WIDTH 24
#define EXPLOSION_UFO_HEIGHT 8
#define EXPLOSION_ALIEN_NUM_IMGS 4
#define EXPLOSION_ALIEN_WIDTH 14
#define EXPLOSION_ALIEN_HEIGHT 8

typedef struct explosion
{
    sprite_t sprite;
    struct timespec creation_time;
    long long explosion_time;
    explosion_type_t type;
} explosion_t;

typedef struct explosion_node
{
    explosion_t *explosion;
    struct list_head node;
} explosion_node_t;

static LIST_HEAD(explosions);

static const struct explosion_bullet
{
    const char image[EXPLOSION_BULLET_HEIGHT][EXPLOSION_BULLET_WIDTH][NUM_RGBA_CHANNELS];
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
    const char image[EXPLOSION_UFO_HEIGHT][EXPLOSION_UFO_WIDTH][NUM_RGBA_CHANNELS];
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

static const struct explosion_alien
{
    const char image[EXPLOSION_ALIEN_NUM_IMGS][EXPLOSION_ALIEN_HEIGHT][EXPLOSION_ALIEN_WIDTH][NUM_RGBA_CHANNELS];
    const int image_width;
    const int image_height;
    const long long explosion_time;
} explosion_alien = {.image =
                         {/* image 1 */
                          {{B, B, B, B, B, B, B, B, B, B, W, B, B, B},
                           {B, W, B, B, W, B, B, B, B, B, B, B, W, B},
                           {B, B, B, B, B, W, B, B, W, B, B, B, B, B},
                           {B, B, B, B, B, B, W, W, B, B, B, B, B, W},
                           {B, B, W, B, B, B, W, W, B, W, B, B, B, B},
                           {B, B, B, B, W, W, B, B, W, B, B, W, B, B},
                           {W, B, B, B, B, B, B, B, B, B, B, B, B, B},
                           {B, B, W, B, B, B, W, B, B, B, W, B, B, W}},
                          /* image 2 */
                          {{B, B, B, B, B, B, B, B, B, B, W, B, B, B},
                           {B, B, B, B, W, B, B, W, B, B, B, B, B, B},
                           {B, B, B, B, B, W, B, B, B, B, B, B, B, B},
                           {B, B, B, B, B, B, W, W, B, B, W, B, B, B},
                           {B, B, B, B, B, B, W, W, B, B, B, B, B, B},
                           {B, B, B, B, W, W, B, B, W, B, B, W, B, B},
                           {B, B, B, B, B, B, B, B, B, B, B, B, B, B},
                           {B, B, B, W, B, B, W, B, B, B, W, B, B, B}},
                          /* image 3 */
                          {{B, B, B, B, B, B, B, B, B, B, B, B, B, B},
                           {B, W, B, W, B, B, B, B, B, B, B, B, B, B},
                           {B, B, B, B, B, W, B, B, W, B, B, B, B, B},
                           {B, B, B, B, W, B, W, W, B, B, B, B, B, B},
                           {B, B, W, B, B, B, W, W, B, B, B, B, B, B},
                           {B, B, B, B, B, W, B, B, W, B, B, W, B, B},
                           {B, B, B, B, B, B, B, B, B, B, B, B, B, B},
                           {B, B, B, W, B, B, W, B, B, B, B, B, B, B}},
                          /* image 4 */
                          {{B, B, B, B, B, B, B, B, B, B, B, B, W, B},
                           {B, B, B, B, B, B, W, B, B, B, W, B, B, B},
                           {W, B, B, W, B, W, B, B, W, B, B, B, B, B},
                           {B, B, B, B, B, B, W, W, B, B, B, B, B, B},
                           {B, B, B, B, B, B, W, W, B, W, B, W, B, B},
                           {B, B, B, B, W, W, B, B, W, B, B, B, B, B},
                           {B, W, B, B, B, B, B, B, B, B, B, B, B, B},
                           {B, B, B, B, B, B, B, W, B, B, B, W, B, B}}},
                     .image_width = EXPLOSION_ALIEN_WIDTH,
                     .image_height = EXPLOSION_ALIEN_HEIGHT,
                     .explosion_time = 500 * NS_PER_MS};

static void
setExplosionType(explosion_t *instance, explosion_type_t type)
{
    static int explosion_alien_next = 0;

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
        case EXPLOSION_ALIEN:
            instance->sprite.width = explosion_alien.image_width;
            instance->sprite.height = explosion_alien.image_height;
            instance->sprite.image = (char *)explosion_alien.image[explosion_alien_next];
            explosion_alien_next = (explosion_alien_next + 1) % EXPLOSION_ALIEN_NUM_IMGS;
            instance->explosion_time = explosion_alien.explosion_time;
            break;
            /* GCOVR_EXCL_START */
        default:
            assert(!"invalid explosion type");
            UNREACHABLE();
            break; /* GCOVR_EXCL_BR_SOURCE */
                   /* GCOVR_EXCL_STOP */
    }
}

void
explosionCreate(int x, int y, explosion_type_t type)
{
    explosion_node_t *new_node = utilsCalloc(1, sizeof(explosion_node_t));
    explosion_t *new_explosion = utilsCalloc(1, sizeof(explosion_t));
    setExplosionType(new_explosion, type);
    new_explosion->sprite.x = x;
    new_explosion->sprite.y = y;
    new_explosion->sprite.pixels_to_move = 0;
    new_explosion->sprite.time_to_move = 0;
    graphCreateImage(&new_explosion->sprite);
    clock_gettime(CLOCK_MONOTONIC, &new_explosion->creation_time);
    graphRegisterPrint(graphGetSprite((base_t *)new_explosion));
    new_node->explosion = new_explosion;
    list_add(&new_node->node, &explosions);
}

static bool
explosionTimeout(explosion_t *this)
{
    assert(this); /* GCOVR_EXCL_LINE */

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
    explosion_node_t *n, *tmp;

    list_for_each_entry_safe(n, tmp, &explosions, node)
    {
        if (explosionTimeout(n->explosion))
        {
            list_del(&n->node);
            utilsFree((void **)&n);
        }
    }
}

#ifdef UNIT_TESTING
void
helperUT_explosionResetList(void)
{
    list_clear(&explosions, explosion_node_t, node);
}
#endif /* UNIT_TESTING */
