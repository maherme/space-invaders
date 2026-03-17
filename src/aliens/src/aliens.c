/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "aliens.h"
#include "graph.h"
#include "graphGlutCallbacks.h"
#include "utils.h"
#include <assert.h>
#include <stdbool.h>

#define ALIEN_CELL_WIDTH 32
#define ALIEN_CELL_HEIGHT 32
#define ALIEN_NUM_FRAMES 2
#define SQUID_WIDTH 8
#define SQUID_HEIGHT 8
#define CRAB_WIDTH 11
#define CRAB_HEIGHT 8
#define OCTOPUS_WIDTH 12
#define OCTOPUS_HEIGHT 8

#define INDEX_ALIENS(row, col) ((row) * ALIENS_COLS + (col))

struct alien_instance
{
    sprite_t sprite;
    bool alive;
};

static struct
{
    struct alien_instance aliens[ALIENS_INITIAL_NUMBER];
    int origin_x;
    int origin_y;
} alienPool;

static alien_type_t alienTypeByRow[ALIENS_ROWS] = {
    OCTOPUS,
    OCTOPUS,
    CRAB,
    CRAB,
    SQUID,
};

static const char squidImage[ALIEN_NUM_FRAMES][SQUID_HEIGHT][SQUID_WIDTH][NUM_RGBA_CHANNELS] = {
    /* frame 1 */
    {{B, B, W, W, W, W, B, B},
     {B, W, W, W, W, W, W, B},
     {W, W, B, W, W, B, W, W},
     {W, W, W, W, W, W, W, W},
     {B, W, W, W, W, W, W, B},
     {B, B, W, B, B, W, B, B},
     {B, W, B, B, B, B, W, B},
     {W, B, B, B, B, B, B, W}},
    /* frame 2 */
    {{B, B, W, W, W, W, B, B},
     {B, W, W, W, W, W, W, B},
     {W, W, B, W, W, B, W, W},
     {W, W, W, W, W, W, W, W},
     {B, W, W, B, B, W, W, B},
     {B, B, W, W, W, W, B, B},
     {B, B, W, B, B, W, B, B},
     {B, W, W, B, B, W, W, B}}};

static const char crabImage[ALIEN_NUM_FRAMES][CRAB_HEIGHT][CRAB_WIDTH][NUM_RGBA_CHANNELS] = {
    /* frame 1 */
    {{B, B, B, W, B, B, B, W, B, B, B},
     {B, B, B, B, W, B, W, B, B, B, B},
     {B, B, B, W, W, W, W, W, B, B, B},
     {W, B, W, W, B, W, B, W, W, B, W},
     {B, W, W, W, W, W, W, W, W, W, B},
     {W, B, W, W, W, W, W, W, W, B, W},
     {B, B, B, W, B, B, B, W, B, B, B},
     {B, W, W, B, B, B, B, B, W, W, B}},
    /* frame 2 */
    {{B, B, B, W, B, B, B, W, B, B, B},
     {B, B, B, B, W, B, W, B, B, B, B},
     {B, B, B, W, W, W, W, W, B, B, B},
     {W, B, W, W, B, W, B, W, W, B, W},
     {W, W, W, W, W, W, W, W, W, W, B},
     {B, B, W, W, W, W, W, W, W, B, B},
     {B, B, B, W, B, B, B, W, B, B, B},
     {B, B, W, W, B, B, B, W, W, B, B}}};

static const char octopusImage[ALIEN_NUM_FRAMES][OCTOPUS_HEIGHT][OCTOPUS_WIDTH][NUM_RGBA_CHANNELS] = {
    /* frame 1 */
    {{B, B, W, W, W, W, W, W, W, W, B, B},
     {B, W, W, W, W, W, W, W, W, W, W, B},
     {W, W, W, B, W, W, W, W, B, W, W, W},
     {B, W, W, W, W, B, B, W, W, W, W, B},
     {B, B, W, W, W, W, W, W, W, W, B, B},
     {B, B, W, B, W, B, B, W, B, W, B, B},
     {B, B, W, B, W, B, B, W, B, W, B, B},
     {W, W, W, B, W, B, B, W, B, W, W, W}},
    /* frame 2 */
    {{B, B, W, W, W, W, W, W, W, W, B, B},
     {B, W, W, W, W, W, W, W, W, W, W, B},
     {W, W, W, B, W, W, W, W, B, W, W, W},
     {B, W, W, W, W, W, W, W, W, W, W, B},
     {B, B, W, W, W, W, W, W, W, W, B, B},
     {B, B, W, B, W, B, B, W, B, W, B, B},
     {B, B, W, B, B, B, B, B, B, W, B, B},
     {B, B, W, W, W, B, B, W, W, W, B, B}}};

static void
setAlienType(alien_t inst, alien_type_t type)
{
    switch (type)
    {
        case SQUID:
            inst->sprite.width = SQUID_WIDTH;
            inst->sprite.height = SQUID_HEIGHT;
            inst->sprite.image = (const char *)squidImage;
            break;
        case CRAB:
            inst->sprite.width = CRAB_WIDTH;
            inst->sprite.height = CRAB_HEIGHT;
            inst->sprite.image = (const char *)crabImage;
            break;
        case OCTOPUS:
            inst->sprite.width = OCTOPUS_WIDTH;
            inst->sprite.height = OCTOPUS_HEIGHT;
            inst->sprite.image = (const char *)octopusImage;
            break;
            /* GCOVR_EXCL_START */
        default:
            assert(!"invalid alien type");
            UNREACHABLE();
            break; /* GCOVR_EXCL_BR_SOURCE */
                   /* GCOVR_EXCL_STOP */
    }
}

static void
alienCreate(int x, int y, alien_type_t type, int index)
{
    struct alien_instance *inst = &alienPool.aliens[index];
    setAlienType(inst, type);
    inst->sprite.x = x;
    inst->sprite.y = y;
    inst->sprite.pixels_to_move = 0;
    inst->sprite.time_to_move = 0;
    graphScaleImage(&inst->sprite);
    graphCreateImage(&inst->sprite);
    inst->sprite.max_movement.right = 0;
    inst->sprite.max_movement.left = 0;
    graphUpdateTimeSprite(&inst->sprite);
    graphRegisterPrint(&inst->sprite);
    inst->alive = true;
}

void
alienDestroy(alien_t alien)
{
    if (!alien)
    {
        return;
    }

    sprite_t *alien_sprite = graphGetSprite((base_t *)alien);
    graphUnregisterPrint(alien_sprite);
    graphDestroyImage(alien_sprite);
    alien->alive = false;
}

static int
alienWidth(alien_type_t type)
{
    switch (type)
    {
        case OCTOPUS:
            return OCTOPUS_WIDTH;
        case CRAB:
            return CRAB_WIDTH;
        case SQUID:
            return SQUID_WIDTH;
            /* GCOVR_EXCL_START */
        default:
            break; /* GCOVR_EXCL_BR_SOURCE */
                   /* GCOVR_EXCL_STOP */
    }

    /* GCOVR_EXCL_START */
    assert(!"invalid alien type");
    UNREACHABLE();
    return 0;
    /* GCOVR_EXCL_STOP */
}

void
aliensCreate(void)
{
    int formation_width = ALIENS_COLS * ALIEN_CELL_WIDTH;
    alienPool.origin_x = (WINDOW_WIDTH - formation_width) / 2;
    alienPool.origin_y = WINDOW_HEIGHT / 2;

    for (int i = 0; i < ALIENS_INITIAL_NUMBER; i++)
    {
        int row = i / ALIENS_COLS;
        int col = i % ALIENS_COLS;

        alien_type_t type = alienTypeByRow[row];
        int rel_x = col * ALIEN_CELL_WIDTH + (ALIEN_CELL_WIDTH - alienWidth(type)) / 2;
        int rel_y = row * ALIEN_CELL_HEIGHT;

        alienCreate(alienPool.origin_x + rel_x, alienPool.origin_y + rel_y, type, i);
    }
}

bool
alienAlive(alien_t alien)
{

    return alien && alien->alive;
}

alien_t
aliensGetAlienInstance(int alien_index)
{
    if (ALIENS_INITIAL_NUMBER <= alien_index)
        return NULL;

    return &alienPool.aliens[alien_index];
}

alien_t
aliensGetShooter(void)
{
    int start_col = rand() % ALIENS_COLS;

    for (int i = 0; i < ALIENS_COLS; i++)
    {
        int col = (start_col + i) % ALIENS_COLS;

        for (int row = 0; row < ALIENS_ROWS; row++)
        {
            alien_t a = &alienPool.aliens[row * ALIENS_COLS + col];
            if (a->alive)
            {
                return a;
            }
        }
    }

    return NULL;
}

#ifdef UNIT_TESTING
#include <string.h>

void
helperUT_alienInitPool(void)
{
    memset(alienPool.aliens, 0, sizeof(alienPool.aliens));
}

void
helperUT_alienSetAlive(alien_t alien, bool alive)
{
    alien->alive = alive;
}

alien_t
helperUT_alienInjectInPool(int row, int col)
{
    int index = INDEX_ALIENS(row, col);
    alien_t alien = &alienPool.aliens[index];

    memset(alien, 0, sizeof(*alien));

    alien->alive = true;

    return alien;
}

#endif /* UNIT_TESTING */
