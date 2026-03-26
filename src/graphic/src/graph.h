/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <GL/glut.h>

#define WINDOW_WIDTH 448
#define WINDOW_HEIGHT 512
#define SCALE_IMAGE 2

#define NUM_RGBA_CHANNELS 4
#define W {(char)255, (char)255, (char)255, (char)255}
#define R {(char)255, 0, 0, (char)255}
#define G {0, (char)255, 0, (char)255}
#define B {0, 0, 0, 0}

typedef struct
{
    int up;
    int down;
    int right;
    int left;
} max_movement_t;

typedef struct
{
    int x1;
    int x2;
    int y1;
    int y2;
} sprite_coordinates_t;

typedef struct
{
    int x;
    int y;
    int width;
    int height;
    int scale;
    int scaled_width;
    int scaled_height;
    const char *image_base;
    const char *image;
    int selected_image;
    int num_frames;
    GLuint textureId;
    struct timespec last_update;
    long long time_to_move;
    int pixels_to_move;
    max_movement_t max_movement;
} sprite_t;

typedef struct
{
    sprite_t sprite;
} base_t;

void
graphCreateImage(sprite_t *sprite);

void
graphScaleImage(sprite_t *sprite);

void
graphDestroyImage(sprite_t *sprite);

sprite_t *
graphGetSprite(base_t *b);

int
graphGetSpriteCoordinates(const sprite_t *const sprite, sprite_coordinates_t *coordinates);

void
graphUpdateImageToPrint(sprite_t *sprite);

void
graphUpdateTimeSprite(sprite_t *sprite);

void
graphPrintImage(const sprite_t *const sprite);

#endif
