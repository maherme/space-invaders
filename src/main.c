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
#include "bunkers.h"
#include "engine.h"
#include "events.h"
#include "explosion.h"
#include "graph.h"
#include "graphGlut.h"
#include "graphGlutCallbacks.h"
#include "hud.h"
#include "keyboard.h"
#include "lives.h"
#include "physic.h"
#include "score.h"
#include "spaceship.h"
#include "ufo.h"
#include "utils.h"
#include <GL/freeglut_ext.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define ALIEN_HEIGHT_FOR_GAME_OVER 16
#define ALIEN_HEIGHT_FOR_DANGER_MID 90
#define ALIEN_HEIGHT_FOR_DANGER_HIGHT 52

static struct
{
    bool gaming;
    spaceship_t spaceship;
    ufo_t ufo;
    struct timespec timer_get_shooter;
    struct timespec timer_alien_move;
    unsigned int alien_move_delay;
} gameContext = {
    .gaming = true,
    .spaceship = NULL,
    .ufo = NULL,
    .timer_alien_move = {0},
    .timer_get_shooter = {0},
    .alien_move_delay = 0,
};

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
    if (physicCheckBorderCollision(bullet_sprite, UP) || physicCheckBorderCollision(bullet_sprite, DOWN))
    {
        if (type == BULLET_SPACESHIP)
        {
            explosionCreate(bullet_sprite->x,
                            GAME_HEIGHT - explosionsGetExplosionHeight(EXPLOSION_BULLET_SPACESHIP),
                            EXPLOSION_BULLET_SPACESHIP,
                            NULL);
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
        gameContext.spaceship = spaceshipCreate(GAME_WIDTH / 2, 0);
        bulletAlienInhibit(false);
        engineUnregister(spaceshipCreateAfterDie);
    }
}

static void
spaceshipExplosionCallback(void)
{
    eventEmit(EVENT_REMOVE_LIFE, NULL);
    engineRegister(spaceshipCreateAfterDie);
}

static void
checkCollisionBulletSpaceship(bullet_t bullet)
{
    bullet_type_t type;
    bulletGetType(bullet, &type);

    if (!bulletUsed(bullet) || !spaceshipAlive(gameContext.spaceship) || type != BULLET_ALIEN)
    {
        return;
    }

    sprite_t *spaceship_sprite = graphGetSprite((base_t *)gameContext.spaceship);
    sprite_t *bullet_sprite = graphGetSprite((base_t *)bullet);

    if (physicCheckSpritesPixelCollision(spaceship_sprite, bullet_sprite))
    {
        bulletAlienInhibit(true);
        bulletDestroy(bullet);
        explosionCreate(spaceship_sprite->x + spaceship_sprite->width / 2,
                        spaceship_sprite->y,
                        EXPLOSION_SPACESHIP,
                        spaceshipExplosionCallback);
        spaceshipDestroy(gameContext.spaceship);
    }
}

static void
checkCollisionBulletSpaceshipBulletAliens(bullet_t bullet)
{
    bullet_type_t type;
    bulletGetType(bullet, &type);

    if (!bulletUsed(bullet) || type != BULLET_SPACESHIP)
    {
        return;
    }

    if (bulletSpaceshipHitBulletAliens(physicCheckSpritesPixelCollision))
    {
        sprite_t *bullet_sprite = graphGetSprite((base_t *)bullet);
        explosionCreate(bullet_sprite->x, bullet_sprite->y, EXPLOSION_BULLET_SPACESHIP, NULL);
        explosionCreate(bullet_sprite->x, bullet_sprite->y, EXPLOSION_BULLET_ALIEN, NULL);
        bulletDestroy(bullet);
        return;
    }
}

static void
bulletActions(void)
{
    bulletCallFunctionForEach(bulletActionsSingle);
    bulletCallFunctionForEach(checkCollisionBulletSpaceship);
    bulletCallFunctionForEach(checkCollisionBulletSpaceshipBulletAliens);
}

static void
spaceshipFire(void)
{
    if (!spaceshipAlive(gameContext.spaceship))
    {
        return;
    }

    sprite_t *spaceship_sprite = graphGetSprite((base_t *)gameContext.spaceship);
    bulletCreate(spaceship_sprite->x + spaceship_sprite->width / 2,
                 spaceship_sprite->y + spaceship_sprite->height,
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
            int points = aliensGetPoints(alien);
            scoreAddPoints(points);
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
    unsigned int num_alive = aliensGetAlives();
    gameContext.alien_move_delay = ALIENS_BASE_MOVE_DELAY - (ALIENS_INITIAL_NUMBER - num_alive) * 8;
    if (gameContext.alien_move_delay < ALIENS_MIN_MOVE_DELAY)
    {
        gameContext.alien_move_delay = ALIENS_MIN_MOVE_DELAY;
    }

    if (utilsCheckTimeout(gameContext.timer_get_shooter, ALIENS_SHOOT_DELAY * NS_PER_MS))
    {
        alien_t alien = aliensGetShooter();
        if (alien)
        {
            sprite_t *alien_sprite = graphGetSprite((base_t *)alien);
            bulletCreate(alien_sprite->x + alien_sprite->width / 2, alien_sprite->y, BULLET_ALIEN);
            clock_gettime(CLOCK_MONOTONIC, &gameContext.timer_get_shooter);
        }
    }

    if (utilsCheckTimeout(gameContext.timer_alien_move, gameContext.alien_move_delay * NS_PER_MS))
    {
        aliensMove();
        clock_gettime(CLOCK_MONOTONIC, &gameContext.timer_alien_move);
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

    sprite_t *ufo_sprite = graphGetSprite((base_t *)gameContext.ufo);
    sprite_t *bullet_sprite = graphGetSprite((base_t *)bullet);

    if (physicCheckSpritesPixelCollision(ufo_sprite, bullet_sprite))
    {
        bulletDestroy(bullet);
        explosionCreate(ufo_sprite->x + ufo_sprite->width / 2, ufo_sprite->y, EXPLOSION_UFO, NULL);
        int points = ufoGetPoints();
        scoreAddPoints(points);
        ufoDestroy(gameContext.ufo);
    }
}

static void
ufoActions(void)
{
    if (!ufoAlive(gameContext.ufo))
    {
        gameContext.ufo = ufoCreate();
        return;
    }
    else
    {
        sprite_t *ufo_sprite = graphGetSprite((base_t *)gameContext.ufo);
        if (ufoCheckForMoving(gameContext.ufo))
        {
            physicMoveSprite(ufo_sprite, ufoGetDirection(gameContext.ufo));
        }
        if (physicCheckBorderCollision(ufo_sprite, RIGHT) || physicCheckBorderCollision(ufo_sprite, LEFT))
        {
            ufoDestroy(gameContext.ufo);
        }

        bulletCallFunctionForEach(checkCollisionBulletUfoSingle);
    }
}

static void
checkCollisionsBulletSingleBunkerSingle(bunker_t bunker, void *ctx)
{
    sprite_t *bunker_sprite = graphGetSprite((base_t *)bunker);
    bullet_t bullet = (bullet_t)ctx;
    sprite_t *bullet_sprite = graphGetSprite((base_t *)bullet);

    if (physicCheckSpritesPixelCollision(bunker_sprite, bullet_sprite))
    {
        bullet_type_t type;
        bulletGetType(bullet, &type);
        explosion_t explosion;

        if (!bulletUsed(bullet) || type == BULLET_SPACESHIP)
        {
            explosion = explosionCreate(bullet_sprite->x, bullet_sprite->y, EXPLOSION_BULLET_SPACESHIP, NULL);
        }
        else
        {
            explosion =
                explosionCreate(bullet_sprite->x, bullet_sprite->y - bullet_sprite->height / 2, EXPLOSION_BULLET_ALIEN, NULL);
        }

        physicMakeFootprintSprite(bunker_sprite, graphGetSprite((base_t *)explosion));
        graphUpdateSprite(bunker_sprite);
        bulletDestroy(bullet);
    }
}

static void
checkCollisionsBulletSingleBunkers(bullet_t bullet)
{
    bullet_type_t type;
    bulletGetType(bullet, &type);

    if (!bulletUsed(bullet))
    {
        return;
    }

    bunkersCallFunctionForEach(checkCollisionsBulletSingleBunkerSingle, bullet);
}

static void
checkCollisionsBulletsBunkers(void)
{
    bulletCallFunctionForEach(checkCollisionsBulletSingleBunkers);
}

static void
keyboardUpdate(void)
{
    if (keyboardGetSpecialKeyState(SPECIAL_KEY_LEFT))
    {
        physicMoveSprite(graphGetSprite((base_t *)gameContext.spaceship), LEFT);
    }
    if (keyboardGetSpecialKeyState(SPECIAL_KEY_RIGHT))
    {
        physicMoveSprite(graphGetSprite((base_t *)gameContext.spaceship), RIGHT);
    }
}

static void
gameOver(void *data)
{
    (void)data;
    /* NOTE: TBD */
}

static void
onLivesRemove(void *data)
{
    (void)data;
    livesRemove();
}

static void
deriveGameStateFromAliensHeight(void *data)
{
    int height = *(int *)data;
    danger_level_t danger_lv = DANGER_LOW;

    if (height <= ALIEN_HEIGHT_FOR_GAME_OVER)
    {
        eventEmit(EVENT_GAME_OVER, NULL);
    }
    else if (height <= ALIEN_HEIGHT_FOR_DANGER_HIGHT)
    {
        danger_lv = DANGER_HIGH;
        eventEmit(EVENT_DANGER_LEVEL_CHANGED, &danger_lv);
    }
    else if (height <= ALIEN_HEIGHT_FOR_DANGER_MID)
    {
        danger_lv = DANGER_MID;
        eventEmit(EVENT_DANGER_LEVEL_CHANGED, &danger_lv);
    }
}

int
main(int argc, char **argv)
{
    graphInitGlutConfig_t initGlutConfig = {
        .main_argc = &argc,
        .main_argv = argv,
        .displayMode = GLUT_DOUBLE | GLUT_RGB,
        .scale = 2,
        .windowPositionX = 0,
        .windowPositionY = 0,
        .windowName = "Space Invaders",
        .displayFunc = graphGlutDisplay,
        .reshapeFunc = graphGlutReshape,
    };

    srand(time(NULL));

    graphRegisterPrintInit();
    graphInitGlut(&initGlutConfig);
    keyboardRegisterAction(spaceshipFire, ACTION_KEY_DOWN, ' ');
    keyboardInit();

    eventRegister(EVENT_GAME_OVER, gameOver);
    eventRegister(EVENT_LIVES_DEPLETED, gameOver);
    eventRegister(EVENT_ALIENS_HEIGHT, deriveGameStateFromAliensHeight);
    eventRegister(EVENT_REMOVE_LIFE, onLivesRemove);
    eventRegister(EVENT_LIVES_CHANGED, onLivesChanged);
    eventRegister(EVENT_SCORE_CHANGED, onScoreChanged);
    eventRegister(EVENT_DANGER_LEVEL_CHANGED, ufoOnDangerLevelChanged);

    gameContext.spaceship = spaceshipCreate(GAME_WIDTH / 2, 0);
    aliensCreate();
    bunkersCreate();
    hudInit();
    engineRegister(keyboardUpdate);
    engineRegister(explosionsDestroy);
    engineRegister(ufoActions);
    engineRegister(checkCollisionsAliensBullet);
    engineRegister(aliensActions);
    engineRegister(bulletActions);
    engineRegister(checkCollisionsBulletsBunkers);

    clock_gettime(CLOCK_MONOTONIC, &gameContext.timer_get_shooter);
    clock_gettime(CLOCK_MONOTONIC, &gameContext.timer_alien_move);

    while (gameContext.gaming)
    {
        engineRun(ENGINE_RATE);
        glutMainLoopEvent();
        graphGlutDisplay();
    }

    exit(EXIT_SUCCESS);
}
