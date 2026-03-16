/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "aliens.h"
#include "bullet.h"
#include "engine.h"
#include "explosion.h"
#include "graph.h"
#include "graphGlut.h"
#include "graphGlutCallbacks.h"
#include "keyboard.h"
#include "physic.h"
#include "spaceship.h"
#include "ufo.h"
#include <GL/freeglut_ext.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

bool gaming = true;
spaceship_t spaceship = NULL;
bullet_t bullet = NULL;
ufo_t ufo = NULL;

static void
bulletDestroy(void)
{
    sprite_t *bullet_sprite = graphGetSprite((base_t *)bullet);
    graphUnregisterPrint(bullet_sprite);
    graphDestroyObject((base_t **)&bullet);
}

static void
bulletActions(void)
{
    if (!bullet)
    {
        return;
    }

    sprite_t *bullet_sprite = graphGetSprite((base_t *)bullet);
    if (physicCheckBorderCollision(bullet_sprite))
    {
        explosionCreate(bullet_sprite->x, bullet_sprite->y - bullet_sprite->scaled_height, EXPLOSION_BULLET);
        bulletDestroy();
    }
    else
    {
        physicMoveSprite(bullet_sprite, UP);
    }
}

static void
spaceshipFire(void)
{
    if (!bullet)
    {
        sprite_t *spaceship_sprite = graphGetSprite((base_t *)spaceship);
        bullet = bulletCreate(spaceship_sprite->x + spaceship_sprite->scaled_width / 2,
                              spaceship_sprite->y + spaceship_sprite->scaled_height);
    }
}

static void
alienDestroy(alien_t *alien)
{
    sprite_t *alien_sprite = graphGetSprite((base_t *)*alien);
    graphUnregisterPrint(alien_sprite);
    graphDestroyObject((base_t **)alien);
}

static void
checkCollisionsAliensBullet(void)
{
    if (!bullet)
        return;

    int num_alien = aliensGetNumberInitialAliens();
    for (int i = 0; i < num_alien; i++)
    {
        alien_t *alien = aliensGetAlienInstance(i);
        if (physicCheckSpritesBoxCollision(graphGetSprite((base_t *)*alien), graphGetSprite((base_t *)bullet)))
        {
            bulletDestroy();
            sprite_t *alien_sprite = graphGetSprite((base_t *)*alien);
            explosionCreate(alien_sprite->x + alien_sprite->width / 2, alien_sprite->y, EXPLOSION_ALIEN);
            alienDestroy(alien);
            return;
        }
    }
}

static void
ufoActions(void)
{
    if (!ufo)
    {
        ufo = ufoCreate();
        return;
    }
    else
    {
        sprite_t *ufo_sprite = graphGetSprite((base_t *)ufo);
        if (ufoCheckForMoving(ufo))
        {
            physicMoveSprite(ufo_sprite, ufoGetDirection(ufo));
        }
        if (physicCheckBorderCollision(ufo_sprite))
        {
            graphUnregisterPrint(ufo_sprite);
            graphDestroyObject((base_t **)&ufo);
        }
        if (bullet)
        {
            if (physicCheckSpritesBoxCollision(ufo_sprite, graphGetSprite((base_t *)bullet)))
            {
                explosionCreate(ufo_sprite->x + ufo_sprite->width / 2, ufo_sprite->y, EXPLOSION_UFO);
                graphUnregisterPrint(ufo_sprite);
                graphDestroyObject((base_t **)&ufo);
                bulletDestroy();
            }
        }
    }
}

static void
keyboardUpdate(void)
{
    if (keyboardGetSpecialKeyState(SPECIAL_KEY_LEFT))
    {
        physicMoveSprite(graphGetSprite((base_t *)spaceship), LEFT);
    }
    if (keyboardGetSpecialKeyState(SPECIAL_KEY_RIGHT))
    {
        physicMoveSprite(graphGetSprite((base_t *)spaceship), RIGHT);
    }
}

int
main(int argc, char **argv)
{
    graphInitGlutConfig_t initGlutConfig = {
        .main_argc = &argc,
        .main_argv = argv,
        .displayMode = GLUT_DOUBLE | GLUT_RGB,
        .windowWidth = WINDOW_WIDTH,
        .windowHeight = WINDOW_HEIGHT,
        .windowPositionX = 0,
        .windowPositionY = 0,
        .windowName = "Space Invaders",
        .displayFunc = graphGlutDisplay,
        .reshapeFunc = graphGlutReshape,
    };

    srand(time(NULL));

    graphInitGlut(&initGlutConfig);
    keyboardRegisterAction(spaceshipFire, ACTION_KEY_DOWN, ' ');
    keyboardInit();

    spaceship = spaceshipCreate(WINDOW_WIDTH / 2, 0);
    aliensCreate();
    engineRegister(keyboardUpdate);
    engineRegister(explosionsDestroy);
    engineRegister(ufoActions);
    engineRegister(checkCollisionsAliensBullet);
    engineRegister(bulletActions);

    while (gaming)
    {
        engineRun(ENGINE_RATE);
        glutMainLoopEvent();
        graphGlutDisplay();
    }

    exit(EXIT_SUCCESS);
}
