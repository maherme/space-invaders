/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include <stdlib.h>
#include <stdbool.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include "graphGlut.h"
#include "graphGlutCallbacks.h"
#include "graph.h"
#include "keyboard.h"
#include "engine.h"
#include "physic.h"
#include "spaceship.h"
#include "bullet.h"
#include "explosion.h"
#include "ufo.h"

bool gaming = true;
spaceship_t spaceship = NULL;
bullet_t bullet = NULL;
explosion_t explosion = NULL;
ufo_t ufo = NULL;

static void
bulletMove(void) {
    physicMoveSprite(graphGetSprite((base_t *)bullet), UP);
}

static void
bulletCheckCeilingCollision(void) {
    sprite_t *bullet_sprite = graphGetSprite((base_t *)bullet);
    if(physicCheckBorderCollision(bullet_sprite)) {
        graphUnregisterPrint(bullet_sprite);
        engineUnregister(bulletCheckCeilingCollision);
        engineUnregister(bulletMove);
        explosion = explosionCreate(bullet_sprite->x - 8,
                                    bullet_sprite->y - bullet_sprite->scaled_height);
        graphDestroyObject((base_t **)&bullet);
        graphRegisterPrint(graphGetSprite((base_t *)explosion));
    }
}

static void
explosionCheckTimeout(void) {
    if(explosionTimeout(explosion)) {
        graphUnregisterPrint(graphGetSprite((base_t *)explosion));
        graphDestroyObject((base_t **)&explosion);
    }
}

static void
spaceshipFire(void) {
    if(!bullet) {
        sprite_t *spaceship_sprite = graphGetSprite((base_t *)spaceship);
        bullet = bulletCreate(spaceship_sprite->x + spaceship_sprite->scaled_width/2,
                              spaceship_sprite->y + spaceship_sprite->scaled_height);
        graphRegisterPrint(graphGetSprite((base_t *)bullet));
        engineRegister(bulletCheckCeilingCollision);
        engineRegister(bulletMove);
    }
}

static void
ufoActions(void) {
    if(!ufo) {
        ufo = ufoCreate();
        graphRegisterPrint(graphGetSprite((base_t *)ufo));
        return;
    }
    else {
        if(ufoCheckForMoving(ufo)) {
            physicMoveSprite(graphGetSprite((base_t *)ufo), ufoGetDirection(ufo)); 
        }
        if(physicCheckBorderCollision(graphGetSprite((base_t *)ufo))) {
            graphUnregisterPrint(graphGetSprite((base_t *)ufo));
            graphDestroyObject((base_t **)&ufo);
        }
    }
}

static void
keyboardUpdate(void) {
    if(keyboardGetSpecialKeyState(SPECIAL_KEY_LEFT)) {
        physicMoveSprite(graphGetSprite((base_t *)spaceship), LEFT);
    }
    if(keyboardGetSpecialKeyState(SPECIAL_KEY_RIGHT)) {
        physicMoveSprite(graphGetSprite((base_t *)spaceship), RIGHT);
    }
}

int
main(int argc, char **argv) {
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

    spaceship = spaceshipCreate(WINDOW_WIDTH/2, 0);
    graphRegisterPrint(graphGetSprite((base_t *)spaceship));
    engineRegister(keyboardUpdate);
    engineRegister(explosionCheckTimeout);
    engineRegister(ufoActions);

    while(gaming) {
        engineRun(ENGINE_RATE);
        glutMainLoopEvent();
        graphGlutDisplay();
    }

    exit(EXIT_SUCCESS);
}
