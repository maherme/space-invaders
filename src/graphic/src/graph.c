/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "graph.h"
#include <GL/glut.h>
#include <time.h>

#define SCALE_IMAGE 2

void
graphCreateImage(sprite_t *sprite)
{
    if (!sprite)
    {
        return;
    }

    glGenTextures(1, &sprite->textureId);
    glBindTexture(GL_TEXTURE_2D, sprite->textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sprite->width, sprite->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sprite->image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void
graphScaleImage(sprite_t *sprite)
{
    if (!sprite)
    {
        return;
    }

    sprite->scale = SCALE_IMAGE;
    sprite->scaled_height = sprite->height * SCALE_IMAGE;
    sprite->scaled_width = sprite->width * SCALE_IMAGE;
    sprite->pixels_to_move = sprite->pixels_to_move * SCALE_IMAGE;
}

void
graphDestroyImage(sprite_t *sprite)
{
    if (!sprite)
    {
        return;
    }

    glDeleteTextures(1, &(sprite->textureId));
}

sprite_t *
graphGetSprite(base_t *b)
{
    if (!b)
    {
        return NULL;
    }
    return &b->sprite;
}

int
graphGetSpriteCoordinates(const sprite_t *const sprite, sprite_coordinates_t *coordinates)
{
    if (!sprite || !coordinates)
    {
        return 1;
    }

    coordinates->x1 = sprite->x;
    coordinates->x2 = sprite->x + sprite->scaled_width;
    coordinates->y1 = sprite->y;
    coordinates->y2 = sprite->y + sprite->scaled_height;

    return 0;
}

void
graphUpdateImageToPrint(sprite_t *sprite)
{
    if (sprite && sprite->num_frames > 1)
    {
        sprite->selected_image = (sprite->selected_image + 1) % sprite->num_frames;
        size_t image_offset = sprite->selected_image * sprite->height * sprite->width * NUM_RGBA_CHANNELS;
        sprite->image = sprite->image_base + image_offset;
    }
}

void
graphUpdateTimeSprite(sprite_t *sprite)
{
    if (!sprite)
    {
        return;
    }

    struct timespec current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    sprite->last_update = current_time;
}

void
graphPrintImage(const sprite_t *const sprite)
{
    if (!sprite)
    {
        return;
    }

    glBindTexture(GL_TEXTURE_2D, sprite->textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sprite->width, sprite->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, sprite->image);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0);
    glVertex2i(sprite->x, sprite->y);
    glTexCoord2f(1.0, 1.0);
    glVertex2i(sprite->x + sprite->scaled_width, sprite->y);
    glTexCoord2f(1.0, 0.0);
    glVertex2i(sprite->x + sprite->scaled_width, sprite->y + sprite->scaled_height);
    glTexCoord2f(0.0, 0.0);
    glVertex2i(sprite->x, sprite->y + sprite->scaled_height);
    glEnd();
}
