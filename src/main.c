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
#include "utils.h"
#include <GL/freeglut_ext.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

bool gaming = true;
spaceship_t spaceship = NULL;
ufo_t ufo = NULL;
struct timespec timer = {0};

static void
bulletActionsSingle(bullet_t bullet)
{
    if (!bulletUsed(bullet))
    {
        return;
    }

    bullet_type_t type;
    bulletGetType(bullet, &type);
    sprite_t *bullet_sprite = graphGetSprite((base_t *)bullet);
    if (physicCheckBorderCollision(bullet_sprite))
    {
        if (type == BULLET_SPACESHIP)
        {
            explosionCreate(bullet_sprite->x, bullet_sprite->y - bullet_sprite->scaled_height, EXPLOSION_BULLET_SPACESHIP, NULL);
        }
        else
        {
            explosionCreate(bullet_sprite->x, bullet_sprite->y, EXPLOSION_BULLET_ALIEN, NULL);
        }
        bulletDestroy(bullet);
    }
    else
    {
        if (type == BULLET_SPACESHIP)
        {
            physicMoveSprite(bullet_sprite, UP);
        }
        else
        {
            physicMoveSprite(bullet_sprite, DOWN);
        }
    }
}

static void
spaceshipCreateAfterDie(void)
{
    if (bulletNoneUsed() && explosionsAllFinished())
    {
        spaceship = spaceshipCreate(WINDOW_WIDTH / 2, 0);
        bulletAlienInhibit(false);
        engineUnregister(spaceshipCreateAfterDie);
    }
}

static void
spaceshipExplosionCallback(void)
{
    engineRegister(spaceshipCreateAfterDie);
}

static void
checkCollisionBulletSpaceship(bullet_t bullet)
{
    bullet_type_t type;
    bulletGetType(bullet, &type);

    if (!bulletUsed(bullet) || !spaceshipAlive(spaceship) || type != BULLET_ALIEN)
    {
        return;
    }

    sprite_t *spaceship_sprite = graphGetSprite((base_t *)spaceship);
    sprite_t *bullet_sprite = graphGetSprite((base_t *)bullet);

    if (physicCheckSpritesPixelCollision(spaceship_sprite, bullet_sprite))
    {
        bulletAlienInhibit(true);
        bulletDestroy(bullet);
        explosionCreate(spaceship_sprite->x + spaceship_sprite->width / 2,
                        spaceship_sprite->y,
                        EXPLOSION_SPACESHIP,
                        spaceshipExplosionCallback);
        spaceshipDestroy(spaceship);
    }
}

static void
bulletActions(void)
{
    bulletCallFunctionForEach(bulletActionsSingle);
    bulletCallFunctionForEach(checkCollisionBulletSpaceship);
}

static void
spaceshipFire(void)
{
    if (!spaceshipAlive(spaceship))
    {
        return;
    }

    sprite_t *spaceship_sprite = graphGetSprite((base_t *)spaceship);
    bulletCreate(spaceship_sprite->x + spaceship_sprite->scaled_width / 2,
                 spaceship_sprite->y + spaceship_sprite->scaled_height,
                 BULLET_SPACESHIP);
}

static void
checkCollisionsBulletAlienSingle(bullet_t bullet)
{
    bullet_type_t type;
    bulletGetType(bullet, &type);

    if (!bulletUsed(bullet) || type != BULLET_SPACESHIP)
    {
        return;
    }

    sprite_t *bullet_sprite = graphGetSprite((base_t *)bullet);

    for (int i = 0; i < ALIENS_INITIAL_NUMBER; i++)
    {
        alien_t alien = aliensGetAlienInstance(i);

        if (!alienAlive(alien))
        {
            continue;
        }

        sprite_t *alien_sprite = graphGetSprite((base_t *)alien);

        if (physicCheckSpritesPixelCollision(alien_sprite, bullet_sprite))
        {
            bulletDestroy(bullet);
            explosionCreate(alien_sprite->x + alien_sprite->width / 2, alien_sprite->y, EXPLOSION_ALIEN, NULL);
            alienDestroy(alien);
            return;
        }
    }
}

static void
checkCollisionsAliensBullet(void)
{
    bulletCallFunctionForEach(checkCollisionsBulletAlienSingle);
}

static void
aliensActions(void)
{
    if (utilsCheckTimeout(timer, 500 * NS_PER_MS))
    {
        alien_t alien = aliensGetShooter();
        if (alien)
        {
            sprite_t *alien_sprite = graphGetSprite((base_t *)alien);
            bulletCreate(alien_sprite->x + alien_sprite->scaled_width / 2, alien_sprite->y, BULLET_ALIEN);
            clock_gettime(CLOCK_MONOTONIC, &timer);
        }
    }
}

static void
checkCollisionBulletUfoSingle(bullet_t bullet)
{
    bullet_type_t type;
    bulletGetType(bullet, &type);

    if (!bulletUsed(bullet) || type != BULLET_SPACESHIP)
    {
        return;
    }

    sprite_t *ufo_sprite = graphGetSprite((base_t *)ufo);
    sprite_t *bullet_sprite = graphGetSprite((base_t *)bullet);

    if (physicCheckSpritesPixelCollision(ufo_sprite, bullet_sprite))
    {
        bulletDestroy(bullet);
        explosionCreate(ufo_sprite->x + ufo_sprite->width / 2, ufo_sprite->y, EXPLOSION_UFO, NULL);
        ufoDestroy(ufo);
    }
}

static void
ufoActions(void)
{
    if (!ufoAlive(ufo))
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
            ufoDestroy(ufo);
        }

        bulletCallFunctionForEach(checkCollisionBulletUfoSingle);
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
    engineRegister(aliensActions);
    engineRegister(bulletActions);

    clock_gettime(CLOCK_MONOTONIC, &timer);

    while (gaming)
    {
        engineRun(ENGINE_RATE);
        glutMainLoopEvent();
        graphGlutDisplay();
    }

    exit(EXIT_SUCCESS);
}
