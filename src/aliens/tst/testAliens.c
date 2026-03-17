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

    aliensCreate();

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
    alien_t alien = helperUT_alienInjectInPool(0, 0);
    helperUT_alienSetAlive(alien, false);

    assert_false(alienAlive(alien));
}

void
testAlienAliveTrue(void **status)
{
    (void)status;
    alien_t alien = helperUT_alienInjectInPool(0, 0);

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
    alien_t alien = helperUT_alienInjectInPool(0, 0);

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

    alien_t alien = helperUT_alienInjectInPool(0, 0);

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
        injected[i] = helperUT_alienInjectInPool(i, 0);
    }

    alien_t expected = injected[0];

    will_return(__wrap_rand, 1);
    expect_function_call(__wrap_rand);
    assert_ptr_equal(expected, aliensGetShooter());
}
