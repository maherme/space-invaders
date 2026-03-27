/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __GRAPHGLUT_H__
#define __GRAPHGLUT_H__

typedef struct
{
    int *main_argc;
    char **main_argv;
    unsigned int displayMode;
    unsigned int scale;
    int windowPositionX;
    int windowPositionY;
    char *windowName;
    void (*displayFunc)(void);
    void (*reshapeFunc)(int w, int h);
} graphInitGlutConfig_t;

void
graphInitGlut(graphInitGlutConfig_t *config);

#endif
