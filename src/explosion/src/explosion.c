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

#define EXPLOSION_BULLET_SPACESHIP_WIDTH 8
#define EXPLOSION_BULLET_SPACESHIP_HEIGHT 8
#define EXPLOSION_BULLET_ALIEN_WIDTH 6
#define EXPLOSION_BULLET_ALIEN_HEIGHT 8
#define EXPLOSION_SPACESHIP_WIDTH 16
#define EXPLOSION_SPACESHIP_HEIGHT 8
#define EXPLOSION_SPACESHIP_NUM_FRAMES 2
#define EXPLOSION_UFO_WIDTH 24
#define EXPLOSION_UFO_HEIGHT 8
#define EXPLOSION_ALIEN_NUM_IMGS 4
#define EXPLOSION_ALIEN_WIDTH 14
#define EXPLOSION_ALIEN_HEIGHT 8

static const unsigned int explosion_heights[] = {
    [EXPLOSION_BULLET_SPACESHIP] = EXPLOSION_BULLET_SPACESHIP_HEIGHT,
    [EXPLOSION_BULLET_ALIEN] = EXPLOSION_BULLET_ALIEN_HEIGHT,
    [EXPLOSION_SPACESHIP] = EXPLOSION_SPACESHIP_HEIGHT,
    [EXPLOSION_UFO] = EXPLOSION_UFO_HEIGHT,
    [EXPLOSION_ALIEN] = EXPLOSION_ALIEN_HEIGHT,
};

typedef struct explosion
{
    sprite_t sprite;
    struct timespec creation_time;
    long long explosion_time;
    struct timespec update_frame_timer;
    long long update_frame_time;
    explosion_type_t type;
    void (*callback)(void);
} explosion_t;

typedef struct explosion_node
{
    explosion_t *explosion;
    struct list_head node;
} explosion_node_t;

static LIST_HEAD(explosions);

static const struct
{
    const char image[EXPLOSION_BULLET_SPACESHIP_HEIGHT][EXPLOSION_BULLET_SPACESHIP_WIDTH][NUM_RGBA_CHANNELS];
    const int image_width;
    const int image_height;
    const long long explosion_time;
} explosion_bullet_spaceship = {.image = {{B, B, R, B, R, B, B, B},
                                          {B, R, R, R, B, B, B, B},
                                          {B, B, R, R, R, B, R, B},
                                          {B, R, R, R, R, R, B, B},
                                          {B, B, R, R, R, B, B, B},
                                          {B, B, B, R, B, B, R, B},
                                          {B, B, R, B, B, R, B, B},
                                          {R, B, B, B, R, B, B, R}},
                                .image_width = EXPLOSION_BULLET_SPACESHIP_WIDTH,
                                .image_height = EXPLOSION_BULLET_SPACESHIP_HEIGHT,
                                .explosion_time = 500 * NS_PER_MS};

static const struct
{
    const char image[EXPLOSION_BULLET_ALIEN_HEIGHT][EXPLOSION_BULLET_ALIEN_WIDTH][NUM_RGBA_CHANNELS];
    const int image_width;
    const int image_height;
    const long long explosion_time;
} explosion_bullet_alien = {.image = {{B, B, G, B, B, G},
                                      {B, G, B, G, B, B},
                                      {B, B, G, G, G, G},
                                      {G, G, G, G, B, B},
                                      {B, G, G, G, G, B},
                                      {G, G, G, G, G, G},
                                      {B, B, G, G, B, G},
                                      {B, G, B, B, G, B}},
                            .image_width = EXPLOSION_BULLET_ALIEN_WIDTH,
                            .image_height = EXPLOSION_BULLET_ALIEN_HEIGHT,
                            .explosion_time = 500 * NS_PER_MS};

static const struct
{
    const char image[EXPLOSION_SPACESHIP_NUM_FRAMES][EXPLOSION_SPACESHIP_HEIGHT][EXPLOSION_SPACESHIP_WIDTH][NUM_RGBA_CHANNELS];
    const int image_width;
    const int image_height;
    const long long explosion_time;
    const long long update_frame_time;
} explosion_spaceship = {.image =
                             {/* frame 1 */
                              {{B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
                               {B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
                               {B, B, B, G, B, B, B, B, B, B, G, B, B, B, B, B},
                               {B, B, B, G, B, G, B, B, B, G, G, B, G, B, B, B},
                               {B, B, G, B, G, B, G, B, B, B, B, G, B, G, B, B},
                               {B, B, B, G, B, G, G, B, B, G, B, G, G, B, B, B},
                               {B, B, B, G, G, B, B, B, B, B, B, G, G, B, B, B},
                               {B, B, G, G, G, G, B, B, B, B, G, G, G, G, B, B}},
                              /* frame 2 */
                              {{G, B, B, G, B, B, G, B, B, G, B, B, G, B, B, G},
                               {B, B, G, B, G, B, B, B, B, G, B, G, B, B, G, B},
                               {B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
                               {B, B, B, B, B, B, G, B, B, G, B, B, G, B, B, B},
                               {B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B},
                               {B, B, B, G, B, B, B, B, B, B, B, G, B, B, B, B},
                               {B, B, B, G, G, B, B, B, B, B, B, G, G, B, B, B},
                               {B, B, G, G, G, G, B, B, B, B, G, G, G, G, B, B}}},
                         .image_width = EXPLOSION_SPACESHIP_WIDTH,
                         .image_height = EXPLOSION_SPACESHIP_HEIGHT,
                         .explosion_time = 2000 * NS_PER_MS,
                         .update_frame_time = 125 * NS_PER_MS};

static const struct
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

static const struct
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
        case EXPLOSION_BULLET_SPACESHIP:
            instance->sprite.width = explosion_bullet_spaceship.image_width;
            instance->sprite.height = explosion_bullet_spaceship.image_height;
            instance->sprite.image = (const char *)explosion_bullet_spaceship.image;
            instance->explosion_time = explosion_bullet_spaceship.explosion_time;
            break;
        case EXPLOSION_BULLET_ALIEN:
            instance->sprite.width = explosion_bullet_alien.image_width;
            instance->sprite.height = explosion_bullet_alien.image_height;
            instance->sprite.image = (const char *)explosion_bullet_alien.image;
            instance->explosion_time = explosion_bullet_alien.explosion_time;
            break;
        case EXPLOSION_UFO:
            instance->sprite.width = explosion_ufo.image_width;
            instance->sprite.height = explosion_ufo.image_height;
            instance->sprite.image = (const char *)explosion_ufo.image;
            instance->explosion_time = explosion_ufo.explosion_time;
            break;
        case EXPLOSION_SPACESHIP:
            instance->sprite.width = explosion_spaceship.image_width;
            instance->sprite.height = explosion_spaceship.image_height;
            instance->sprite.image_base = (const char *)explosion_spaceship.image;
            instance->sprite.image = instance->sprite.image_base;
            instance->sprite.num_frames = EXPLOSION_SPACESHIP_NUM_FRAMES;
            instance->explosion_time = explosion_spaceship.explosion_time;
            instance->update_frame_time = explosion_spaceship.update_frame_time;
            clock_gettime(CLOCK_MONOTONIC, &instance->update_frame_timer);
            break;
        case EXPLOSION_ALIEN:
            instance->sprite.width = explosion_alien.image_width;
            instance->sprite.height = explosion_alien.image_height;
            instance->sprite.image = (const char *)explosion_alien.image[explosion_alien_next];
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
explosionCreate(int x, int y, explosion_type_t type, void (*callback)(void))
{
    explosion_node_t *new_node = utilsCalloc(1, sizeof(explosion_node_t));
    explosion_t *new_explosion = utilsCalloc(1, sizeof(explosion_t));
    setExplosionType(new_explosion, type);
    new_explosion->sprite.x = x - new_explosion->sprite.width / 2;
    new_explosion->sprite.y = y;
    new_explosion->sprite.pixels_to_move = 0;
    new_explosion->sprite.time_to_move = 0;
    graphScaleImage(&new_explosion->sprite);
    graphCreateImage(&new_explosion->sprite);
    clock_gettime(CLOCK_MONOTONIC, &new_explosion->creation_time);
    graphRegisterPrint(graphGetSprite((base_t *)new_explosion));
    new_explosion->callback = callback;
    new_node->explosion = new_explosion;
    list_add(&new_node->node, &explosions);
}

static bool
explosionTimeout(explosion_t *explosion)
{
    assert(explosion); /* GCOVR_EXCL_LINE */

    if (utilsCheckTimeout(explosion->creation_time, explosion->explosion_time))
    {
        sprite_t *explosion_sprite = graphGetSprite((base_t *)explosion);
        graphUnregisterPrint(explosion_sprite);
        graphDestroyImage(explosion_sprite);
        if (explosion->callback)
        {
            explosion->callback();
        }
        utilsFree((void **)&explosion);
        return true;
    }

    return false;
}

static void
explosionUpdateImageToPrint(explosion_t *explosion)
{
    assert(explosion); /* GCOVR_EXCL_LINE */

    if (explosion->sprite.num_frames > 1 && utilsCheckTimeout(explosion->update_frame_timer, explosion->update_frame_time))
    {
        graphUpdateImageToPrint(&explosion->sprite);
        clock_gettime(CLOCK_MONOTONIC, &explosion->update_frame_timer);
    }
}

void
explosionsDestroy(void)
{
    explosion_node_t *n, *tmp;

    list_for_each_entry_safe(n, tmp, &explosions, node)
    {
        explosionUpdateImageToPrint(n->explosion);
        if (explosionTimeout(n->explosion))
        {
            list_del(&n->node);
            utilsFree((void **)&n);
        }
    }
}

bool
explosionsAllFinished(void)
{
    return list_empty(&explosions);
}

unsigned int
explosionsGetExplosionHeight(explosion_type_t type)
{
    return explosion_heights[type];
}

#ifdef UNIT_TESTING
void
helperUT_explosionResetList(void)
{
    explosion_node_t *n, *tmp;

    list_for_each_entry_safe(n, tmp, &explosions, node)
    {
        list_del(&n->node);
        free((void *)n->explosion);
        free((void *)n);
    }
}
#endif /* UNIT_TESTING */
