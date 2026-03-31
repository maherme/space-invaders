/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "lives.h"
#include "graph.h"
#include "graphGlutCallbacks.h"
#include <stdbool.h>

#define LIVE_WIDTH 13
#define LIVE_HEIGHT 8
#define MAX_LIVES_TO_PRINT 4
#define LIVE_START_COORD_Y 4
#define LIVE_START_COORD_X 10
#define LIVE_PIXELS_SPACE 4
#define LIVE_INITIAL_NUM 3

struct live_instance_t
{
    sprite_t sprite;
};

static struct
{
    struct live_instance_t lives[MAX_LIVES_TO_PRINT];
    int num_lives;
    void (*livesDepletedCallback)(void);
} livePool;

static const char liveImage[LIVE_HEIGHT][LIVE_WIDTH][NUM_RGBA_CHANNELS] = {
    {B, B, B, B, B, B, G, B, B, B, B, B, B},
    {B, B, B, B, B, G, G, G, B, B, B, B, B},
    {B, B, B, B, B, G, G, G, B, B, B, B, B},
    {B, G, G, G, G, G, G, G, G, G, G, G, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G},
    {B, B, G, G, B, B, B, B, B, G, G, B, B},
    {B, G, G, G, G, B, B, B, G, G, G, G, B},
};

void
livesCreate(void (*livesDepletedCallback)(void))
{
    for (int i = 0; i < MAX_LIVES_TO_PRINT; i++)
    {
        struct live_instance_t *live = &livePool.lives[i];
        live->sprite.x = LIVE_START_COORD_X + i * (LIVE_WIDTH + LIVE_PIXELS_SPACE);
        live->sprite.y = LIVE_START_COORD_Y;
        live->sprite.width = LIVE_WIDTH;
        live->sprite.height = LIVE_HEIGHT;
        live->sprite.image = (const char *)liveImage;
        live->sprite.layer = LAYER_HUD;

        if (i < LIVE_INITIAL_NUM - 1)
        {
            graphRegisterPrint(&live->sprite);
        }

        livePool.num_lives = LIVE_INITIAL_NUM;
        livePool.livesDepletedCallback = livesDepletedCallback;
    }
}

void
livesRemove(void)
{
    livePool.num_lives--;

    if (livePool.num_lives < 1)
    {
        livePool.livesDepletedCallback();
    }
    else if (livePool.num_lives <= MAX_LIVES_TO_PRINT)
    {
        graphUnregisterPrint(&livePool.lives[livePool.num_lives - 1].sprite);
    }
}

void
livesAdd(void)
{
    if (livePool.num_lives <= MAX_LIVES_TO_PRINT)
    {
        graphRegisterPrint(&livePool.lives[livePool.num_lives - 1].sprite);
    }

    livePool.num_lives++;
}

#ifdef UNIT_TESTING
int
helperUT_livesGetNumLives(void)
{
    return livePool.num_lives;
}

void
helperUT_livesSetNumLives(int n)
{
    livePool.num_lives = n;
}

sprite_t *
helperUT_livesGetSpriteByInstanceIndex(int idx)
{
    return &livePool.lives[idx].sprite;
}

void
helperUT_livesInjectLivesDepletedCb(void (*cb)(void))
{
    livePool.livesDepletedCallback = cb;
}

#endif /* UNIT_TESTING */
