/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "physic.h"
#include "graph.h"
#include "utils.h"
#include <stdbool.h>

void
physicMoveSprite(sprite_t *sprite, direction_t direction)
{
    if (!sprite)
    {
        return;
    }

    if (!utilsCheckTimeout(sprite->last_update, sprite->time_to_move))
    {
        return;
    }

    switch (direction)
    {
        case RIGHT:
            if (sprite->x + sprite->pixels_to_move >= sprite->max_movement.right)
            {
                sprite->x = sprite->max_movement.right;
                return;
            }
            sprite->x += sprite->pixels_to_move;
            break;
        case LEFT:
            if (sprite->x - sprite->pixels_to_move <= sprite->max_movement.left)
            {
                sprite->x = sprite->max_movement.left;
                return;
            }
            sprite->x -= sprite->pixels_to_move;
            break;
        case UP:
            if (sprite->y + sprite->pixels_to_move >= sprite->max_movement.up)
            {
                sprite->y = sprite->max_movement.up;
                return;
            }
            sprite->y += sprite->pixels_to_move;
            break;
        case INVALID_DIR:
        default:
            break;
    }

    graphUpdateTimeSprite(sprite);
}

bool
physicCheckBorderCollision(const sprite_t *const sprite)
{
    if (!sprite)
        return false;

    if ((sprite->y == sprite->max_movement.up) || (sprite->x == sprite->max_movement.right) ||
        (sprite->x == sprite->max_movement.left))
        return true;
    return false;
}

static bool
physicCheckBoxes(const sprite_coordinates_t *const coord1, const sprite_coordinates_t *const coord2)
{
    int dx = (coord1->x1 + coord1->x2) - (coord2->x1 + coord2->x2);
    int dy = (coord1->y1 + coord1->y2) - (coord2->y1 + coord2->y2);

    dx = dx < 0 ? -dx : dx;
    dy = dy < 0 ? -dy : dy;

    int sumx = (coord1->x2 - coord1->x1) + (coord2->x2 - coord2->x1);
    int sumy = (coord1->y2 - coord1->y1) + (coord2->y2 - coord2->y1);

    return (dx <= sumx) & (dy <= sumy);
}

bool
physicCheckSpritesBoxCollision(const sprite_t *const sprite1, const sprite_t *const sprite2)
{
    if (!sprite1 || !sprite2)
        return false;

    sprite_coordinates_t coord1, coord2;
    graphGetSpriteCoordinates(sprite1, &coord1);
    graphGetSpriteCoordinates(sprite2, &coord2);

    return physicCheckBoxes(&coord1, &coord2);
}
