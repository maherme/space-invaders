#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <GL/glut.h>

#define WINDOW_WIDTH    448
#define WINDOW_HEIGHT   512

#define W {(char)255, (char)255, (char)255, (char)255}
#define R {(char)255, 0, 0, (char)255}
#define G {0, (char)255, 0, (char)255}
#define B {0, 0, 0, 0}

typedef struct {
    int x;
    int y;
    int width;
    int height;
    int scale;
    const char *image;
    GLuint textureId;
} sprite_t;

void
graphCreateImage(sprite_t *sprite);

void
graphPrintImage(const sprite_t * const sprite);

#endif
