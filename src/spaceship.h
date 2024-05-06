#ifndef __SPACESHIP_H__
#define __SPACESHIP_H__

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include "utils.h"

#define SPACESHIP_WIDTH     13
#define SPACESHIP_HEIGHT    8

#define W {(char)255, (char)255, (char)255, (char)255}
#define R {(char)255, 0, 0, (char)255}
#define G {0, (char)255, 0, (char)255}
#define B {0, 0, 0, 0}

typedef struct spaceship_instance_t *spaceship_t;

typedef struct {
    int x;
    int y;
    int width;
    int height;
    const char *image;
    GLuint textureId;
} sprite_t;

spaceship_t
spaceshipCreate(int x, int y);

sprite_t *
spaceshipGetSprite(const spaceship_t this);

void
spaceshipPrint(void);

#endif
