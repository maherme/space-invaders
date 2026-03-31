/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "graphGlut.h"
#include "graph.h"
#include <GL/glut.h>

void
graphInitGlut(graphInitGlutConfig_t *config)
{
    glutInit(config->main_argc, config->main_argv);
    glutInitDisplayMode(config->displayMode);
    glutInitWindowSize(GAME_WIDTH * config->scale, GAME_HEIGHT * config->scale);
    glutInitWindowPosition(config->windowPositionX, config->windowPositionY);
    (void)glutCreateWindow(config->windowName);
    glutDisplayFunc(config->displayFunc);
    glutReshapeFunc(config->reshapeFunc);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}
