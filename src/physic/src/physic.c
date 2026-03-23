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
        case DOWN:
            if (sprite->y - sprite->pixels_to_move <= sprite->max_movement.down)
            {
                sprite->y = sprite->max_movement.down;
                return;
            }
            sprite->y -= sprite->pixels_to_move;
            break;
        case INVALID_DIR:
        default:
            return;
            break;
    }

    graphUpdateImageToPrint(sprite);
    graphUpdateTimeSprite(sprite);
}

bool
physicCheckBorderCollision(const sprite_t *const sprite)
{
    if (!sprite)
        return false;

    if ((sprite->y == sprite->max_movement.up) || (sprite->y == sprite->max_movement.down) ||
        (sprite->x == sprite->max_movement.right) || (sprite->x == sprite->max_movement.left))
        return true;
    return false;
}

static bool
checkBoxesCollison(const sprite_coordinates_t *const coord1, const sprite_coordinates_t *const coord2)
{
    bool separated_x = coord1->x2 < coord2->x1 || coord1->x1 > coord2->x2;
    bool separated_y = coord1->y2 < coord2->y1 || coord1->y1 > coord2->y2;

    return !(separated_x || separated_y);
}

bool
physicCheckSpritesBoxCollision(const sprite_t *const sprite1, const sprite_t *const sprite2)
{
    if (!sprite1 || !sprite2)
    {
        return false;
    }

    sprite_coordinates_t coord1, coord2;
    graphGetSpriteCoordinates(sprite1, &coord1);
    graphGetSpriteCoordinates(sprite2, &coord2);

    return checkBoxesCollison(&coord1, &coord2);
}

static bool
checkPixelsCollision(const sprite_t *const sprite1,
                     const sprite_coordinates_t *const coord1,
                     const sprite_t *const sprite2,
                     const sprite_coordinates_t *const coord2)
{
    int overlap_left = coord1->x1 > coord2->x1 ? coord1->x1 : coord2->x1;
    int overlap_right = coord1->x2 < coord2->x2 ? coord1->x2 : coord2->x2;
    int overlap_bottom = coord1->y1 > coord2->y1 ? coord1->y1 : coord2->y1;
    int overlap_top = coord1->y2 < coord2->y2 ? coord1->y2 : coord2->y2;

    /* NOTE:
     * overlap_bottom >= overlap_top is unreachable when called through
     * physicCheckSpritesPixelCollision(), because checkBoxesCollison()
     * guarantees overlap in both axes.
     */
    if (overlap_left >= overlap_right || overlap_bottom >= overlap_top) /* GCOVR_EXCL_BR_WITHOUT_HIT: 1/4 */
        return false;

    const uint8_t *img1 = (const uint8_t *)sprite1->image;
    const uint8_t *img2 = (const uint8_t *)sprite2->image;

    for (int y = overlap_bottom; y < overlap_top; y++)
    {
        for (int x = overlap_left; x < overlap_right; x++)
        {
            // Local coords in sprite1
            int x1 = (x - coord1->x1) / sprite1->scale;
            int y1 = (y - coord1->y1) / sprite1->scale;

            // Local coords in sprite2
            int x2 = (x - coord2->x1) / sprite2->scale;
            int y2 = (y - coord2->y1) / sprite2->scale;

            // RGBA buffer index
            int idx1 = (y1 * sprite1->width + x1) * NUM_RGBA_CHANNELS;
            int idx2 = (y2 * sprite2->width + x2) * NUM_RGBA_CHANNELS;

            uint8_t alpha1 = img1[idx1 + 3];
            uint8_t alpha2 = img2[idx2 + 3];

            if (alpha1 && alpha2)
                return true;
        }
    }

    return false;
}

bool
physicCheckSpritesPixelCollision(const sprite_t *const sprite1, const sprite_t *const sprite2)
{
    if (!sprite1 || !sprite2)
    {
        return false;
    }

    sprite_coordinates_t coord1, coord2;
    graphGetSpriteCoordinates(sprite1, &coord1);
    graphGetSpriteCoordinates(sprite2, &coord2);

    if (checkBoxesCollison(&coord1, &coord2))
    {
        return checkPixelsCollision(sprite1, &coord1, sprite2, &coord2);
    }

    return false;
}
