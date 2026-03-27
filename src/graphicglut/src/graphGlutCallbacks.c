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
    void *context;
    struct list_head node;
} ctx_node_t;

static LIST_HEAD(contexts);

int
graphRegisterPrint(void *ctx)
{
    if (!ctx)
    {
        return -1;
    }

    ctx_node_t *n = utilsCalloc(1, sizeof(*n));
    n->context = ctx;
    list_add(&n->node, &contexts);

    return 0;
}

int
graphUnregisterPrint(void *ctx)
{
    if (!ctx)
    {
        return -1;
    }

    ctx_node_t *n, *tmp;
    int removed = 0;

    list_for_each_entry_safe(n, tmp, &contexts, node)
    {
        if (n->context == ctx)
        {
            list_del(&n->node);
            utilsFree((void **)&n);
            removed++;
        }
    }

    return removed;
}

void
graphGlutDisplay(void)
{

    glClear(GL_COLOR_BUFFER_BIT);

    ctx_node_t *n;

    list_for_each_entry(n, &contexts, node)
    {
        graphPrintImage(n->context);
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
helperUT_graphGlutResetRegisteredContext(void)
{
    list_clear_with_free(&contexts, ctx_node_t, node);
}

bool
helperUT_graphGlutContextIsRegistered(void *ctx)
{
    ctx_node_t *n;

    list_for_each_entry(n, &contexts, node)
    {
        if (n->context == ctx)
        {
            return true;
        }
    }

    return false;
}

void
helperUT_graphGlutInjectContext(void *ctx)
{
    ctx_node_t *n = utilsCalloc(1, sizeof(*n));
    n->context = ctx;
    list_add(&n->node, &contexts);
}
#endif
