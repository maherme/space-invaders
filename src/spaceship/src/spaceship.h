#ifndef __SPACESHIP_H__
#define __SPACESHIP_H__

#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "graph.h"

#define SPACESHIP_WIDTH     13
#define SPACESHIP_HEIGHT    8

typedef struct spaceship_instance_t *spaceship_t;

spaceship_t
spaceshipCreate(int x, int y);

#endif
