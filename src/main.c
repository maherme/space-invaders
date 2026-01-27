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

bool gaming = true;
spaceship_t spaceship = NULL;
bullet_t bullet = NULL;

static void
bulletMove(void) {
    physicMoveSprite(graphGetSprite((base_t *)bullet), UP);
}

static void
bulletCheckCeiligCollision(void) {
    if(physicCheckCeillingCollision(graphGetSprite((base_t *)bullet))) {
        graphUnregisterPrint(graphGetSprite((base_t *)bullet));
        engineUnregister(bulletCheckCeiligCollision);
        engineUnregister(bulletMove);
        graphDestroyObject((base_t **)&bullet);
        bullet = NULL;
    }
}

static void
spaceshipFire(void) {
    if(!bullet) {
        sprite_t *spaceship_sprite = graphGetSprite((base_t *)spaceship);
        bullet = bulletCreate(spaceship_sprite->x + spaceship_sprite->scaled_width/2,
                              spaceship_sprite->y + spaceship_sprite->scaled_height);
        graphRegisterPrint(graphGetSprite((base_t *)bullet));
        engineRegister(bulletCheckCeiligCollision);
        engineRegister(bulletMove);
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

    graphInitGlut(&initGlutConfig);
    keyboardRegisterAction(spaceshipFire, ACTION_KEY_DOWN, ' ');
    keyboardInit();

    spaceship = spaceshipCreate(WINDOW_WIDTH/2, 0);
    graphRegisterPrint(graphGetSprite((base_t *)spaceship));
    engineRegister(keyboardUpdate);

    while(gaming) {
        engineRun(ENGINE_RATE);
        glutMainLoopEvent();
        graphGlutDisplay();
    }

    exit(EXIT_SUCCESS);
}
