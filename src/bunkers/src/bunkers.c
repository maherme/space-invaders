/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "bunkers.h"
#include "graph.h"
#include "graphGlutCallbacks.h"
#include <assert.h>
#include <string.h>

#define BUNKER_WIDTH 22
#define BUNKER_HEIGHT 16
#define NUM_BUNKERS 4
#define BUNKER_SPACING ((GAME_WIDTH - BUNKER_WIDTH * NUM_BUNKERS) / (NUM_BUNKERS + 1))

static const char bunker_image[BUNKER_HEIGHT][BUNKER_WIDTH][NUM_RGBA_CHANNELS] = {
    {B, B, B, B, G, G, G, G, G, G, G, G, G, G, G, G, G, G, B, B, B, B},
    {B, B, B, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, B, B, B},
    {B, B, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, B, B},
    {B, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, B},
    {G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, G, B, B, B, B, B, B, B, B, G, G, G, G, G, G, G},
    {G, G, G, G, G, G, B, B, B, B, B, B, B, B, B, B, G, G, G, G, G, G},
    {G, G, G, G, G, B, B, B, B, B, B, B, B, B, B, B, B, G, G, G, G, G},
    {G, G, G, G, G, B, B, B, B, B, B, B, B, B, B, B, B, G, G, G, G, G}};

struct bunker_instance_t
{
    sprite_t sprite;
    char image[BUNKER_HEIGHT][BUNKER_WIDTH][NUM_RGBA_CHANNELS];
};

static struct bunker_instance_t bunkerPool[NUM_BUNKERS];

void
bunkersCreate(void)
{
    for (int i = 0; i < NUM_BUNKERS; i++)
    {
        bunker_t bunker = &bunkerPool[i];
        bunker->sprite.x = BUNKER_SPACING * (i + 1) + BUNKER_WIDTH * i;
        bunker->sprite.y = GAME_HEIGHT / 16;
        bunker->sprite.width = BUNKER_WIDTH;
        bunker->sprite.height = BUNKER_HEIGHT;
        memcpy(bunker->image, bunker_image, sizeof(bunker_image));
        bunker->sprite.image = (char *)bunker->image;
        bunker->sprite.layer = LAYER_BACKGROUND;
        bunker->sprite.visible = true;
        graphRegisterPrint(&bunker->sprite);
    }
}

void
bunkersCallFunctionForEach(void (*fn)(bunker_t, void *ctx), void *ctx)
{
    if (!fn)
    {
        assert(!"pointer to fn must not be NULL");
        return;
    }

    for (int i = 0; i < NUM_BUNKERS; i++)
    {
        fn(&bunkerPool[i], ctx);
    }
}
