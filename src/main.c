#include <stdlib.h>
#include <stdbool.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include "graphGlut.h"
#include "graphGlutCallbacks.h"
#include "graph.h"
#include "keyboard.h"
#include "engine.h"
#include "spaceship.h"

bool gaming = true;
spaceship_t spaceship = NULL;

void
keyboardUpdate(void) {
    if(keyboardGetSpecialKeyState(KEY_LEFT)) {
        graphMoveImage(spaceshipGetSprite(spaceship), LEFT);
    }
    if(keyboardGetSpecialKeyState(KEY_RIGHT)) {
        graphMoveImage(spaceshipGetSprite(spaceship), RIGHT);
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
    keyboardInit();

    spaceship = spaceshipCreate(WINDOW_WIDTH/2, 0);
    graphRegisterPrint(spaceshipGetSprite(spaceship));
    engineRegister(keyboardUpdate);

    while(gaming) {
        engineRun();
        glutMainLoopEvent();
        graphGlutDisplay();
    }

    exit(EXIT_SUCCESS);
}
