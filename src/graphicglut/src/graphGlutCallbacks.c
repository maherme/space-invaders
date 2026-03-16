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

    glutSwapBuffers();
}

void
graphGlutReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

#ifdef UNIT_TESTING
void
helperUT_graphGlutResetRegisteredContext(void)
{
    list_clear(&contexts, ctx_node_t, node);
}
#endif
