#include <stdlib.h>
#include <GL/glut.h>
#include "graphGlut.h"
#include "graphGlutCallbacks.h"

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
    };

    graphInitGlut(&initGlutConfig);

    glutMainLoop();

    exit(EXIT_SUCCESS);
}
