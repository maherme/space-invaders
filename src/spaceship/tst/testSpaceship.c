/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testSpaceship.h"
#include "graph.h"
#include "spaceship.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

void
testSpaceshipCreate(void **status)
{
    (void)status;
    int x_pos = 10;
    int y_pos = 20;

    expect_function_call(__wrap_graphScaleImage);
    expect_function_call(__wrap_graphCreateImage);
    expect_function_call(__wrap_graphRegisterPrint);

    spaceship_t spaceship = spaceshipCreate(x_pos, y_pos);

    assert_true(spaceshipAlive(spaceship));
}

void
testSpaceshipDestroyNullParameter(void **status)
{
    (void)status;

    spaceshipDestroy(NULL);
}

void
testSpaceshipDestroy(void **status)
{
    (void)status;
    spaceship_t spaceship = helperUT_spaceshipGetInstance();

    expect_function_call(__wrap_graphGetSprite);
    expect_function_call(__wrap_graphUnregisterPrint);
    expect_function_call(__wrap_graphDestroyImage);

    spaceshipDestroy(spaceship);

    assert_false(spaceshipAlive(spaceship));
}

void
testSpaceshipAliveNullParameter(void **status)
{
    (void)status;

    assert_false(spaceshipAlive(NULL));
}

void
testSpaceshipAliveFalse(void **status)
{
    (void)status;
    spaceship_t spaceship = helperUT_spaceshipGetInstance();
    helperUT_spaceshipSetAlive(spaceship, false);

    assert_false(spaceshipAlive(spaceship));
}

void
testSpaceshipAliveTrue(void **status)
{
    (void)status;
    spaceship_t spaceship = helperUT_spaceshipGetInstance();

    assert_true(spaceshipAlive(spaceship));
}
