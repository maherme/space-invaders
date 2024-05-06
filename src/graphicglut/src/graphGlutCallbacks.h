#ifndef __GRAPHGLUTCALLBACKS_H__
#define __GRAPHGLUTCALLBACKS_H__

#include <GL/glut.h>

void
graphRegisterPrint(void *ctx);

void
graphGlutDisplay(void);

void
graphGlutReshape(int w, int h);

#endif
