#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <sys/time.h>
#include <GL/glut.h>

#define WINDOW_WIDTH    448
#define WINDOW_HEIGHT   512

#define W {(char)255, (char)255, (char)255, (char)255}
#define R {(char)255, 0, 0, (char)255}
#define G {0, (char)255, 0, (char)255}
#define B {0, 0, 0, 0}

typedef enum {
    UP,
    DOWN,
    RIGHT,
    LEFT
} direction_t;

typedef struct {
    int x;
    int y;
    int width;
    int height;
    int scale;
    int scaled_width;
    int scaled_height;
    const char *image;
    GLuint textureId;
    struct timeval last_update;
    float time_to_move;
    int pixels_to_move;
} sprite_t;

void
graphCreateImage(sprite_t *sprite);

void
graphPrintImage(const sprite_t * const sprite);

void
graphMoveImage(sprite_t *sprite, direction_t direction);

#endif
