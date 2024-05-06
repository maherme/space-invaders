#include <stdlib.h>
#include <stdbool.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include "graphGlut.h"
#include "graphGlutCallbacks.h"
#include "graph.h"
#include "spaceship.h"

bool gaming = true;
spaceship_t spaceship = NULL;

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

    spaceship = spaceshipCreate(WINDOW_WIDTH/2, 0);
    graphRegisterPrint(spaceshipGetSprite(spaceship));

    while(gaming) {
        glutMainLoopEvent();
    }

    exit(EXIT_SUCCESS);
}
