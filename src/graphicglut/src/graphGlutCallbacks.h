/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __GRAPHGLUTCALLBACKS_H__
#define __GRAPHGLUTCALLBACKS_H__

struct sprite;
typedef struct sprite sprite_t;

typedef enum
{
    LAYER_BACKGROUND = 0,
    LAYER_GAME_OBJECTS,
    LAYER_EFFECTS,
    NUM_RENDER_LAYERS,
} render_layer_t;

void
graphRegisterPrintInit(void);

int
graphRegisterPrint(sprite_t *sprite);

int
graphUnregisterPrint(sprite_t *sprite);

void
graphGlutDisplay(void);

void
graphGlutReshape(int w, int h);

#ifdef UNIT_TESTING
void
helperUT_graphGlutResetRegisteredSprites(void);

bool
helperUT_graphGlutSpriteIsRegistered(sprite_t *sprite);

void
helperUT_graphGlutInjectSprite(sprite_t *sprite);
#endif

#endif
