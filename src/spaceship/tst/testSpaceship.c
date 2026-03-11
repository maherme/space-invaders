/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testSpaceship.h"
#include "spaceship.h"

void
testSpaceshipCreate(void **status)
{
    (void)status;
    int x_pos = 10;
    int y_pos = 20;

    expect_function_call(__wrap_utilsCalloc);
    expect_function_call(__wrap_graphCreateImage);

    spaceship_t spaceship = spaceshipCreate(x_pos, y_pos);
    sprite_t *sprite = graphGetSprite((base_t *)spaceship);

    assert_int_equal(sprite->x, x_pos);
    assert_int_equal(sprite->y, y_pos);
}
