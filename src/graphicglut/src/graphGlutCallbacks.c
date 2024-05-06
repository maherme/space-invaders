#include "graphGlutCallbacks.h"
#include "graph.h"

static void *context = NULL;

void
graphRegisterPrint(void *ctx) {
    context = ctx;
}

void
graphGlutDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);
 
    if(context) {
        graphPrintImage(context);
    }

    glutSwapBuffers();
}

void
graphGlutReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
