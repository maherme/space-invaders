#ifndef __GRAPHGLUT_H__
#define __GRAPHGLUT_H__

#include <GL/glut.h>

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
    void (*reshapeFunc)(int w, int h);
}graphInitGlutConfig_t;

void
graphInitGlut(graphInitGlutConfig_t *config);

#endif
