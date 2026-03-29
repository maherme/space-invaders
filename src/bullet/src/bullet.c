/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "bullet.h"
#include "graph.h"
#include "graphGlutCallbacks.h"
#include "utils.h"
#include <assert.h>
#include <stdbool.h>

#define MAX_BULLETS 4
#define BULLET_SPACESHIP_WIDTH 1
#define BULLET_SPACESHIP_HEIGHT 4
#define BULLET_ALIEN_WIDTH 3
#define BULLET_ALIEN_HEIGHT 7
#define BULLET_ALIEN_NUM_FRAMES 4
#define BULLET_SPACESHIP_SLOT 0

typedef enum
{
    CRACKLE,
    PLASMA,
    COIL,
    BULLET_ALIEN_NUM_TYPES
} bullet_alien_type_t;

struct bullet_instance
{
    sprite_t sprite;
    bullet_type_t type;
    bool used;
};

typedef struct
{
    const char *image;
    long long time_to_move;
    int pixels_to_move;
} bullet_alien_t;

static struct
{
    struct bullet_instance bullets[MAX_BULLETS];
    bool inhibitBulletAlien;
} bulletPool;

static const char bulletSpaceshipImage[BULLET_SPACESHIP_HEIGHT][BULLET_SPACESHIP_WIDTH][NUM_RGBA_CHANNELS] = {
    {W}, {W}, {W}, {W}};
static const char bulletAlienImage[BULLET_ALIEN_NUM_TYPES][BULLET_ALIEN_NUM_FRAMES][BULLET_ALIEN_HEIGHT][BULLET_ALIEN_WIDTH]
                                  [NUM_RGBA_CHANNELS] = {
                                      /* crackle */
                                      /* frame 1 */
                                      {{{B, W, B}, {B, W, B}, {W, B, B}, {B, W, B}, {B, B, W}, {B, W, B}, {B, W, B}},
                                       /* frame 2 */
                                       {{B, W, B}, {B, W, B}, {B, W, B}, {B, W, B}, {B, W, B}, {B, W, B}, {B, W, B}},
                                       /* frame 3 */
                                       {{B, W, B}, {B, W, B}, {B, B, W}, {B, W, B}, {W, B, B}, {B, W, B}, {B, W, B}},
                                       /* frame 4 */
                                       {{B, W, B}, {B, W, B}, {B, W, B}, {B, W, B}, {B, W, B}, {B, W, B}, {B, W, B}}},
                                      /* plasma */
                                      /* frame 1 */
                                      {{{B, W, B}, {B, W, B}, {B, W, B}, {B, W, B}, {B, W, B}, {W, W, W}, {W, W, W}},
                                       /* frame 2 */
                                       {{B, W, B}, {B, W, B}, {B, W, B}, {W, W, W}, {B, W, B}, {B, W, B}, {W, W, W}},
                                       /* frame 3 */
                                       {{B, W, B}, {W, W, W}, {B, W, B}, {B, W, B}, {B, W, B}, {B, W, B}, {W, W, W}},
                                       /* frame 4 */
                                       {{B, W, B}, {B, W, B}, {B, W, B}, {W, W, W}, {B, W, B}, {B, W, B}, {W, W, W}}},
                                      /* coil */
                                      /* frame 1 */
                                      {{{B, W, W}, {B, W, B}, {W, W, B}, {B, W, B}, {B, W, W}, {B, W, B}, {W, W, B}},
                                       /* frame 2 */
                                       {{B, W, B}, {W, W, B}, {B, W, B}, {B, W, W}, {B, W, B}, {W, W, B}, {B, W, B}},
                                       /* frame 3 */
                                       {{W, W, B}, {B, W, B}, {B, W, W}, {B, W, B}, {W, W, B}, {B, W, B}, {B, W, W}},
                                       /* frame 4 */
                                       {{B, W, B}, {B, W, W}, {B, W, B}, {W, W, B}, {B, W, B}, {B, W, W}, {B, W, B}}}};

static bullet_alien_t bulletAlien[BULLET_ALIEN_NUM_TYPES] = {
    {.image = (const char *)&bulletAlienImage[CRACKLE], .time_to_move = 32 * NS_PER_MS, .pixels_to_move = 3},
    {.image = (const char *)&bulletAlienImage[PLASMA], .time_to_move = 64 * NS_PER_MS, .pixels_to_move = 3},
    {.image = (const char *)&bulletAlienImage[COIL], .time_to_move = 32 * NS_PER_MS, .pixels_to_move = 2}};

static bullet_alien_type_t
getBulletAlienType(void)
{
    bullet_alien_type_t result;
    int r = rand() % 100;

    if (r < 50)
    {
        result = CRACKLE;
    }
    else if (r < 80)
    {
        result = COIL;
    }
    else
    {
        result = PLASMA;
    }

    return result;
}

static void
setBulletType(bullet_t bullet, bullet_type_t type)
{
    switch (type)
    {
        case BULLET_SPACESHIP:
            bullet->sprite.width = BULLET_SPACESHIP_WIDTH;
            bullet->sprite.height = BULLET_SPACESHIP_HEIGHT;
            bullet->sprite.image = (const char *)bulletSpaceshipImage;
            bullet->sprite.pixels_to_move = 1;
            bullet->sprite.max_movement.up = WINDOW_HEIGHT;
            bullet->sprite.max_movement.down = 0;
            bullet->sprite.time_to_move = 2 * NS_PER_MS;
            break;
        case BULLET_ALIEN:
        {
            bullet_alien_type_t alien_bullet_type = getBulletAlienType();
            bullet->sprite.width = BULLET_ALIEN_WIDTH;
            bullet->sprite.height = BULLET_ALIEN_HEIGHT;
            bullet->sprite.image_base = bulletAlien[alien_bullet_type].image;
            bullet->sprite.image = bullet->sprite.image_base;
            bullet->sprite.num_frames = BULLET_ALIEN_NUM_FRAMES;
            bullet->sprite.pixels_to_move = bulletAlien[alien_bullet_type].pixels_to_move;
            bullet->sprite.max_movement.up = WINDOW_HEIGHT;
            bullet->sprite.max_movement.down = 0;
            bullet->sprite.time_to_move = bulletAlien[alien_bullet_type].time_to_move;
            break;
        }
            /* GCOVR_EXCL_START */
        default:
            assert(!"invalid bullet type");
            UNREACHABLE();
            break; /* GCOVR_EXCL_BR_SOURCE */
                   /* GCOVR_EXCL_STOP */
    }

    bullet->type = type;
}

void
bulletCreate(int x, int y, bullet_type_t type)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (type == BULLET_SPACESHIP && i != BULLET_SPACESHIP_SLOT)
        {
            continue;
        }

        if (type == BULLET_ALIEN && (i == BULLET_SPACESHIP_SLOT || bulletPool.inhibitBulletAlien))
        {
            continue;
        }

        if (!bulletPool.bullets[i].used)
        {
            struct bullet_instance *inst = &bulletPool.bullets[i];

            setBulletType(inst, type);
            inst->sprite.x = x;
            inst->sprite.y = y;
            inst->sprite.layer = LAYER_GAME_OBJECTS;
            graphCreateImage(&inst->sprite);
            graphRegisterPrint(&inst->sprite);

            inst->used = true;

            return;
        }
    }
}

void
bulletDestroy(bullet_t bullet)
{
    if (!bullet)
    {
        return;
    }

    sprite_t *bullet_sprite = graphGetSprite((base_t *)bullet);
    graphUnregisterPrint(bullet_sprite);
    graphDestroyImage(bullet_sprite);
    bullet->used = false;
}

bool
bulletUsed(bullet_t bullet)
{
    return bullet && bullet->used;
}

int
bulletGetType(const bullet_t bullet, bullet_type_t *type)
{
    if (!bullet || !type)
    {
        return -1;
    }

    *type = bullet->type;

    return 0;
}

void
bulletCallFunctionForEach(void (*fn)(bullet_t))
{
    if (!fn)
    {
        assert(!"pointer to fn must not be NULL");
        return;
    }

    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bulletPool.bullets[i].used)
        {
            fn(&bulletPool.bullets[i]);
        }
    }
}

void
bulletAlienInhibit(bool inhibit)
{
    bulletPool.inhibitBulletAlien = inhibit;
}

bool
bulletNoneUsed(void)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bulletPool.bullets[i].used)
        {
            return false;
        }
    }

    return true;
}

#ifdef UNIT_TESTING
void
helperUT_bulletInitPool(void)
{
    memset(bulletPool.bullets, 0, sizeof(bulletPool.bullets));
}

void
helperUT_bulletSetUsed(bullet_t bullet, bool used)
{
    bullet->used = used;
}

bullet_t
helperUT_bulletInjectInPool(int index, bullet_type_t type)
{
    bullet_t bullet = &bulletPool.bullets[index];
    memset(bullet, 0, sizeof(*bullet));

    bulletPool.bullets[index].used = true;
    bulletPool.bullets[index].type = type;

    return bullet;
}
#endif /* UNIT_TESTING */
