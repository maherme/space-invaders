/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testExplosion.h"
#include "explosion.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <time.h>

int
teardown(void **state)
{
    (void)state;
    helperUT_explosionResetList();
    return 0;
}

int
__wrap_clock_gettime(clockid_t clockid, struct timespec *tp)
{
    assert_int_equal(clockid, CLOCK_MONOTONIC);
    assert_non_null(tp);
    tp->tv_sec = (time_t)mock_type(time_t);
    tp->tv_nsec = (long)mock_type(long);
    function_called();
    return 0;
}

static void
registerExplosionBullet(void)
{
    int x_pos = 10;
    int y_pos = 20;

    expect_function_call(__wrap_utilsCalloc);
    expect_function_call(__wrap_utilsCalloc);
    expect_function_call(__wrap_graphScaleImage);
    expect_function_call(__wrap_graphCreateImage);
    will_return(__wrap_clock_gettime, 0); /* tv_sec */
    will_return(__wrap_clock_gettime, 0); /* tv_nsec */
    expect_function_call(__wrap_clock_gettime);
    expect_function_call(__wrap_graphRegisterPrint);

    explosionCreate(x_pos, y_pos, EXPLOSION_BULLET_SPACESHIP);
}

static explosion_type_t explosions[] = {EXPLOSION_BULLET_SPACESHIP, EXPLOSION_BULLET_ALIEN, EXPLOSION_UFO, EXPLOSION_ALIEN};

void
testExplosionCreate(void **status)
{
    (void)status;
    int x_pos = 10;
    int y_pos = 20;

    for (size_t i = 0; i < sizeof(explosions) / sizeof(explosions[0]); i++)
    {
        expect_function_call(__wrap_utilsCalloc);
        expect_function_call(__wrap_utilsCalloc);
        expect_function_call(__wrap_graphScaleImage);
        expect_function_call(__wrap_graphCreateImage);
        will_return(__wrap_clock_gettime, 0); /* tv_sec */
        will_return(__wrap_clock_gettime, 0); /* tv_nsec */
        expect_function_call(__wrap_clock_gettime);
        expect_function_call(__wrap_graphRegisterPrint);

        explosionCreate(x_pos, y_pos, explosions[i]);
    }
}

void
testExplosionsDestroyListEmpty(void **status)
{
    (void)status;

    explosionsDestroy();
}

void
testExplosionsDestroyTimeoutFalse(void **status)
{
    (void)status;
    registerExplosionBullet();

    will_return(__wrap_utilsCheckTimeout, false);
    expect_function_call(__wrap_utilsCheckTimeout);
    explosionsDestroy();
}

void
testExplosionsDestroyTimeoutTrue(void **status)
{
    (void)status;
    registerExplosionBullet();

    will_return(__wrap_utilsCheckTimeout, true);
    expect_function_call(__wrap_utilsCheckTimeout);
    expect_function_call(__wrap_graphUnregisterPrint);
    expect_function_call(__wrap_graphDestroyImage);
    /* free explosion */
    expect_function_call(__wrap_utilsFree);
    /* free node in list */
    expect_function_call(__wrap_utilsFree);

    explosionsDestroy();
}

void
testExplosionsDestroyTwoExplosions(void **status)
{
    (void)status;
    int number_explosions = 2;

    for (int i = 0; i < number_explosions; i++)
    {
        registerExplosionBullet();
    }

    /* first registered explosion */
    will_return(__wrap_utilsCheckTimeout, false);
    expect_function_call(__wrap_utilsCheckTimeout);

    /* second registered explosion */
    will_return(__wrap_utilsCheckTimeout, true);
    expect_function_call(__wrap_utilsCheckTimeout);
    expect_function_call(__wrap_graphUnregisterPrint);
    expect_function_call(__wrap_graphDestroyImage);
    /* free explosion */
    expect_function_call(__wrap_utilsFree);
    /* free node in list */
    expect_function_call(__wrap_utilsFree);

    explosionsDestroy();
}
