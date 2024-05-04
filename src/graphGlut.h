#ifndef __GRAPHGLUT_H__
#define __GRAPHGLUT_H__

#include <GL/glut.h>

#define WINDOW_WIDTH    448
#define WINDOW_HEIGHT   512

typedef struct {
    int *main_argc;
    char **main_argv;
    unsigned int displayMode;
    int windowWidth;
    int windowHeight;
    int windowPositionX;
    int windowPositionY;
    char *windowName;
    void (*displayFunc)(void);
}graphInitGlutConfig_t;

void
graphInitGlut(graphInitGlutConfig_t *config);

#endif
