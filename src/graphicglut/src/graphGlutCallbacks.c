/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "graphGlutCallbacks.h"
#include "graph.h"
#include "list.h"
#include "utils.h"
#include <GL/glut.h>

typedef struct ctx_node
{
    sprite_t *sprite;
    struct list_head node;
} ctx_node_t;

struct list_head render_layers[NUM_RENDER_LAYERS];

void
graphRegisterPrintInit(void)
{
    for (int i = 0; i < NUM_RENDER_LAYERS; i++)
    {
        init_list_head(&render_layers[i]);
    }
}

int
graphRegisterPrint(sprite_t *sprite)
{
    if (!sprite)
    {
        return -1;
    }

    ctx_node_t *n = utilsCalloc(1, sizeof(*n));
    n->sprite = sprite;
    list_add_tail(&n->node, &render_layers[sprite->layer]);
    graphCreateImage(sprite);

    return 0;
}

int
graphUnregisterPrint(sprite_t *sprite)
{
    if (!sprite)
    {
        return -1;
    }

    int removed = 0;

    for (int i = 0; i < NUM_RENDER_LAYERS; i++)
    {
        ctx_node_t *n, *tmp;

        list_for_each_entry_safe(n, tmp, &render_layers[i], node)
        {
            if (n->sprite == sprite)
            {
                graphDestroyImage(n->sprite);
                list_del(&n->node);
                utilsFree((void **)&n);
                removed++;
            }
        }
    }

    return removed;
}

void
graphGlutDisplay(void)
{

    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < NUM_RENDER_LAYERS; i++)
    {
        ctx_node_t *n;

        list_for_each_entry(n, &render_layers[i], node)
        {
            graphPrintImage(n->sprite);
        }
    }

    graphPrintGameBorder();

    glutSwapBuffers();
}

void
graphGlutReshape(int w, int h)
{
    const int game_w = WINDOW_WIDTH;
    const int game_h = WINDOW_HEIGHT;

    int scale_x = w / game_w;
    int scale_y = h / game_h;
    int scale = scale_x < scale_y ? scale_x : scale_y;
    if (scale < 1)
    {
        scale = 1;
    }

    int vp_w = game_w * scale;
    int vp_h = game_h * scale;

    int vp_x = (w - vp_w) / 2;
    int vp_y = (h - vp_h) / 2;

    glViewport(vp_x, vp_y, vp_w, vp_h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, game_w, 0, game_h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

#ifdef UNIT_TESTING
void
helperUT_graphGlutResetRegisteredSprites(void)
{
    for (int i = 0; i < NUM_RENDER_LAYERS; i++)
    {
        list_clear_with_free(&render_layers[i], ctx_node_t, node);
    }
}

bool
helperUT_graphGlutSpriteIsRegistered(sprite_t *sprite)
{
    for (int i = 0; i < NUM_RENDER_LAYERS; i++)
    {
        ctx_node_t *n;
        list_for_each_entry(n, &render_layers[i], node)
        {
            if (n->sprite == sprite)
            {
                return true;
            }
        }
    }

    return false;
}

void
helperUT_graphGlutInjectSprite(sprite_t *sprite)
{
    ctx_node_t *n = utilsCalloc(1, sizeof(*n));
    n->sprite = sprite;
    list_add(&n->node, &render_layers[sprite->layer]);
}
#endif
