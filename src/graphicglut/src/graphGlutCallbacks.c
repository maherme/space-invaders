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
#include "utils.h"
#include <GL/glut.h>

typedef struct context
{
    void *context;
    struct context *next;
} context_t;

static context_t *head = NULL;

int
graphRegisterPrint(void *ctx)
{
    if (!ctx)
    {
        return -1;
    }

    context_t *new_node = utilsCalloc(1, sizeof(context_t));
    new_node->context = ctx;
    new_node->next = head;
    head = new_node;

    return 0;
}

int
graphUnregisterPrint(void *ctx)
{
    context_t *current = head;
    context_t *prev = NULL;
    int unregister_contexts = 0;

    if (!ctx)
    {
        return -1;
    }

    while (current)
    {
        if (ctx == current->context)
        {
            if (!prev)
            {
                head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            context_t *tmp = current;
            current = current->next;
            utilsFree((void **)&tmp);
            unregister_contexts++;
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }

    return unregister_contexts;
}

void
graphGlutDisplay(void)
{
    context_t *tmp = head;

    glClear(GL_COLOR_BUFFER_BIT);

    while (tmp)
    {
        graphPrintImage(tmp->context);
        tmp = tmp->next;
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
    while (head)
    {
        context_t *tmp = head;
        head = head->next;
        free(tmp);
    }
}
#endif
