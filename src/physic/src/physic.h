#ifndef __PHYSIC_H__
#define __PHYSIC_H__

#include "graph.h"
#include <sys/time.h>
#include <stdbool.h>

typedef enum {
    UP,
    DOWN,
    RIGHT,
    LEFT
} direction_t;

void
physicMoveSprite(sprite_t *sprite, direction_t direction);

bool
physicCheckCeillingCollision(const sprite_t *const sprite);

#endif
