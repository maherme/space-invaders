#ifndef __BULLET_H__
#define __BULLET_H__

#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "graph.h"

#define BULLET_WIDTH                1
#define BULLET_HEIGHT               4

typedef struct bullet_instance_t *bullet_t;

bullet_t
bulletCreate(int x, int y);

#endif
