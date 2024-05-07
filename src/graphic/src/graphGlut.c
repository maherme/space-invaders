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
}
