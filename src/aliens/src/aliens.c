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

#define ALIENS_ROWS 5
#define ALIENS_COLS 11
#define ALIENS_INITIAL_NUMBER (ALIENS_ROWS * ALIENS_COLS)
#define ALIEN_CELL_WIDTH 32
#define ALIEN_CELL_HEIGHT 32
#define ALIEN_NUM_FRAMES 2
#define SQUID_WIDTH 8
#define SQUID_HEIGHT 8
#define CRAB_WIDTH 11
#define CRAB_HEIGHT 8
#define OCTOPUS_WIDTH 12
#define OCTOPUS_HEIGHT 8

typedef enum
{
    SQUID,
    CRAB,
    OCTOPUS
} alien_type_t;

struct alien_instance_t
{
    sprite_t sprite;
};

static struct aliens_instance_t
{
    alien_t alien[ALIENS_INITIAL_NUMBER];
    int origin_x;
    int origin_y;
} aliens;

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

static alien_t
alienCreate(int x, int y, alien_type_t type)
{
    alien_t inst = utilsCalloc(1, sizeof(struct alien_instance_t));
    setAlienType(inst, type);
    inst->sprite.x = x;
    inst->sprite.y = y;
    inst->sprite.pixels_to_move = 0;
    inst->sprite.time_to_move = 0;
    graphCreateImage(&inst->sprite);
    inst->sprite.max_movement.right = 0;
    inst->sprite.max_movement.left = 0;
    graphUpdateTimeSprite(&inst->sprite);
    graphRegisterPrint(graphGetSprite((base_t *)inst));

    return inst;
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
    aliens.origin_x = (WINDOW_WIDTH - formation_width) / 2;
    aliens.origin_y = WINDOW_HEIGHT / 2;

    for (int i = 0; i < ALIENS_INITIAL_NUMBER; i++)
    {
        int row = i / ALIENS_COLS;
        int col = i % ALIENS_COLS;

        alien_type_t type = alienTypeByRow[row];
        int rel_x = col * ALIEN_CELL_WIDTH + (ALIEN_CELL_WIDTH - alienWidth(type)) / 2;
        int rel_y = row * ALIEN_CELL_HEIGHT;

        aliens.alien[i] = alienCreate(aliens.origin_x + rel_x, aliens.origin_y + rel_y, type);
    }
}

int
aliensGetNumberInitialAliens(void)
{
    return ALIENS_INITIAL_NUMBER;
}

alien_t *
aliensGetAlienInstance(int alien_index)
{
    if (ALIENS_INITIAL_NUMBER <= alien_index)
        return NULL;

    return (alien_t *)&aliens.alien[alien_index];
}
