/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "graphGlut.h"
#include "graphGlutCallbacks.h"

void
graphInitGlut(graphInitGlutConfig_t *config) {
    glutInit(config->main_argc, config->main_argv);
    glutInitDisplayMode(config->displayMode);
    glutInitWindowSize(config->windowWidth, config->windowHeight);
    glutInitWindowPosition(config->windowPositionX, config->windowPositionY);
    (void)glutCreateWindow(config->windowName);
    glutDisplayFunc(config->displayFunc);
    glutReshapeFunc(config->reshapeFunc);
    glEnable(GL_TEXTURE_2D);
}
