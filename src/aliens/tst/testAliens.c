/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testAliens.h"
#include "aliens.h"
#include "physic.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

int
setup(void **state)
{
    (void)state;
    helperUT_alienInitPool();
    return 0;
}

int
__wrap_rand(void)
{
    function_called();
    return (int)mock();
}

static void
foo_cb(void)
{
    function_called();
}

void
testAliensCreate(void **status)
{
    (void)status;

    for (int i = 0; i < ALIENS_INITIAL_NUMBER; i++)
    {
        expect_function_call(__wrap_graphScaleImage);
        expect_function_call(__wrap_graphCreateImage);
        expect_function_call(__wrap_graphUpdateTimeSprite);
        expect_function_call(__wrap_graphRegisterPrint);
    }

    aliensCreate(foo_cb);

    for (int i = 0; i < ALIENS_INITIAL_NUMBER; i++)
    {
        assert_non_null(aliensGetAlienInstance(i));
    }
}

void
testAlienAliveNullParameter(void **status)
{
    (void)status;

    assert_false(alienAlive(NULL));
}

void
testAlienAliveFalse(void **status)
{
    (void)status;
    alien_t alien = helperUT_alienInjectInPool(0, 0, NULL);
    helperUT_alienSetAlive(alien, false);

    assert_false(alienAlive(alien));
}

void
testAlienAliveTrue(void **status)
{
    (void)status;
    alien_t alien = helperUT_alienInjectInPool(0, 0, NULL);

    assert_true(alienAlive(alien));
}

void
testAlienDestroyNullParameter(void **status)
{
    (void)status;

    alienDestroy(NULL);
}

void
testAlienDestroy(void **status)
{
    (void)status;
    alien_t alien = helperUT_alienInjectInPool(0, 0, NULL);

    expect_function_call(__wrap_graphGetSprite);
    expect_function_call(__wrap_graphUnregisterPrint);
    expect_function_call(__wrap_graphDestroyImage);

    alienDestroy(alien);
}

void
testAliensGetAlienInstanceInvalidIndex(void **status)
{
    (void)status;

    assert_null(aliensGetAlienInstance(ALIENS_INITIAL_NUMBER + 1));
}

void
testAliensGetAlives(void **status)
{
    (void)status;
    int expected_num_aliens = 0;

    for (int col = 0; col < ALIENS_COLS; col++)
    {
        for (int row = 0; row < ALIENS_ROWS; row++)
        {
            helperUT_alienInjectInPool(row, col, NULL);
            expected_num_aliens++;
            assert_uint_equal(expected_num_aliens, aliensGetAlives());
        }
    }
}

void
testAliensGetShooterFormationEmpty(void **status)
{
    (void)status;

    will_return(__wrap_rand, 1);
    expect_function_call(__wrap_rand);

    assert_null(aliensGetShooter());
}

void
testAliensGetShooterFormationOneAlien(void **status)
{
    (void)status;

    alien_t alien = helperUT_alienInjectInPool(0, 0, NULL);

    will_return(__wrap_rand, 1);
    expect_function_call(__wrap_rand);

    assert_ptr_equal(alien, aliensGetShooter());
}

void
testAliensGetShooterFirstInColumn(void **status)
{
    (void)status;
    alien_t injected[ALIENS_ROWS];

    for (int i = 0; i < ALIENS_ROWS; i++)
    {
        injected[i] = helperUT_alienInjectInPool(i, 0, NULL);
    }

    alien_t expected = injected[0];

    will_return(__wrap_rand, 1);
    expect_function_call(__wrap_rand);
    assert_ptr_equal(expected, aliensGetShooter());
}

void
testAliensMoveRight(void **status)
{
    (void)status;
    sprite_t sprite_alien1 = {
        .x = 64,
        .y = 100,
        .scaled_width = 1,
    };

    sprite_t sprite_alien2 = {
        .x = 32,
        .y = 132,
        .scaled_width = 1,
    };

    helperUT_alienSetCurrentDirection(RIGHT);
    helperUT_alienInjectInPool(0, 1, &sprite_alien1);
    helperUT_alienInjectInPool(1, 0, &sprite_alien2);

    /* Each alien is moved */
    expect_uint_value(__wrap_physicMoveSprite, direction, RIGHT);
    expect_function_call(__wrap_physicMoveSprite);
    expect_uint_value(__wrap_physicMoveSprite, direction, RIGHT);
    expect_function_call(__wrap_physicMoveSprite);

    aliensMove();
}

void
testAliensMoveLeft(void **status)
{
    (void)status;
    sprite_t sprite = {
        .x = 100,
        .y = 100,
        .scaled_width = 1,
    };

    helperUT_alienSetCurrentDirection(LEFT);
    helperUT_alienInjectInPool(0, 0, &sprite);

    expect_uint_value(__wrap_physicMoveSprite, direction, LEFT);
    expect_function_call(__wrap_physicMoveSprite);

    aliensMove();
}

void
testAliensMoveMaxLeft(void **status)
{
    (void)status;
    sprite_t sprite = {
        .x = 0,
        .y = 100,
        .scaled_width = 1,
    };

    helperUT_alienSetCurrentDirection(LEFT);
    helperUT_alienInjectInPool(0, 0, &sprite);

    expect_uint_value(__wrap_physicMoveSprite, direction, DOWN);
    expect_function_call(__wrap_physicMoveSprite);

    aliensMove();
}

void
testAliensMoveMaxRight(void **status)
{
    (void)status;
    sprite_t sprite = {
        .x = WINDOW_WIDTH,
        .y = 100,
        .scaled_width = 1,
    };

    helperUT_alienSetCurrentDirection(RIGHT);
    helperUT_alienInjectInPool(0, 0, &sprite);

    expect_uint_value(__wrap_physicMoveSprite, direction, DOWN);
    expect_function_call(__wrap_physicMoveSprite);

    aliensMove();
}

void
testAliensMoveGameOver(void **status)
{
    (void)status;
    sprite_t sprite = {
        .x = 0,
        .scaled_width = 1,
        .y = 16,
    };

    helperUT_alienSetGameOverCallbck(foo_cb);
    helperUT_alienInjectInPool(0, 0, &sprite);

    expect_function_call(foo_cb);

    aliensMove();
}

void
testAliensMoveGameOverNull(void **status)
{
    (void)status;
    sprite_t sprite = {
        .x = 0,
        .scaled_width = 1,
        .y = 16,
    };

    helperUT_alienSetGameOverCallbck(NULL);
    helperUT_alienSetCurrentDirection(RIGHT);
    helperUT_alienInjectInPool(0, 0, &sprite);

    expect_uint_value(__wrap_physicMoveSprite, direction, RIGHT);
    expect_function_call(__wrap_physicMoveSprite);

    aliensMove();
}
