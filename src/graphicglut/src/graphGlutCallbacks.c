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

static void *context[MAX_PRINT_CONTEXTS];

int
graphRegisterPrint(void *ctx)
{
    if (!ctx)
    {
        return -1;
    }

    for (int i = 0; i < MAX_PRINT_CONTEXTS; i++)
    {
        if (!context[i])
        {
            context[i] = ctx;
            return 0;
        }
    }

    return -1;
}

int
graphUnregisterPrint(void *ctx)
{
    if (!ctx)
    {
        return -1;
    }

    for (int i = 0; i < MAX_PRINT_CONTEXTS; i++)
    {
        if (context[i] == ctx)
        {
            context[i] = NULL;
            return 0;
        }
    }

    return -1;
}

void
graphGlutDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < MAX_PRINT_CONTEXTS; i++)
    {
        if (context[i] != NULL)
        {
            graphPrintImage(context[i]);
        }
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
    for (int i = 0; i < MAX_PRINT_CONTEXTS; i++)
    {
        context[i] = NULL;
    }
}
#endif
