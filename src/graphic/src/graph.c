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
    coordinates->x2 = sprite->x + sprite->width;
    coordinates->y1 = sprite->y;
    coordinates->y2 = sprite->y + sprite->height;

    return 0;
}

void
graphNextImageToPrint(sprite_t *sprite)
{
    if (sprite && sprite->num_frames > 1)
    {
        sprite->selected_image = (sprite->selected_image + 1) % sprite->num_frames;
        size_t image_offset = sprite->selected_image * sprite->height * sprite->width * NUM_RGBA_CHANNELS;
        sprite->image = sprite->image_base + image_offset;
        glBindTexture(GL_TEXTURE_2D, sprite->textureId);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, sprite->width, sprite->height, GL_RGBA, GL_UNSIGNED_BYTE, sprite->image);
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
    if (!sprite || !sprite->visible)
    {
        return;
    }

    glBindTexture(GL_TEXTURE_2D, sprite->textureId);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0);
    glVertex2i(sprite->x, sprite->y);
    glTexCoord2f(1.0, 1.0);
    glVertex2i(sprite->x + sprite->width, sprite->y);
    glTexCoord2f(1.0, 0.0);
    glVertex2i(sprite->x + sprite->width, sprite->y + sprite->height);
    glTexCoord2f(0.0, 0.0);
    glVertex2i(sprite->x, sprite->y + sprite->height);
    glEnd();
}

void
graphUpdateSprite(const sprite_t *const sprite)
{
    if (!sprite)
    {
        return;
    }

    glBindTexture(GL_TEXTURE_2D, sprite->textureId);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, sprite->width, sprite->height, GL_RGBA, GL_UNSIGNED_BYTE, sprite->image);
}

void
graphPrintBorder(int x, int y, int w, int h)
{
    GLubyte color[NUM_RGBA_CHANNELS] = W;

    glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);

    glDisable(GL_TEXTURE_2D);
    glColor4ubv(color);
    glLineWidth(2.0f);

    glBegin(GL_LINE_LOOP);
    glVertex2i(x, y);
    glVertex2i(x + w, y);
    glVertex2i(x + w, y + h);
    glVertex2i(x, y + h);
    glEnd();

    glPopAttrib(); // restaura todo
}
