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
registerExplosionBullet(void (*callback)(void))
{
    expect_function_call(__wrap_utilsCalloc);
    expect_function_call(__wrap_utilsCalloc);
    will_return(__wrap_clock_gettime, 0); /* tv_sec */
    will_return(__wrap_clock_gettime, 0); /* tv_nsec */
    expect_function_call(__wrap_clock_gettime);
    expect_function_call(__wrap_graphRegisterPrint);

    explosionCreate(0, 0, EXPLOSION_BULLET_SPACESHIP, callback);
}

static void
registerExplosionSpaceship(void (*callback)(void))
{
    expect_function_call(__wrap_utilsCalloc);
    expect_function_call(__wrap_utilsCalloc);
    will_return(__wrap_clock_gettime, 0); /* tv_sec */
    will_return(__wrap_clock_gettime, 0); /* tv_nsec */
    expect_function_call(__wrap_clock_gettime);
    will_return(__wrap_clock_gettime, 0); /* tv_sec */
    will_return(__wrap_clock_gettime, 0); /* tv_nsec */
    expect_function_call(__wrap_clock_gettime);
    expect_function_call(__wrap_graphRegisterPrint);

    explosionCreate(0, 0, EXPLOSION_SPACESHIP, callback);
}

static explosion_type_t explosions[] = {
    EXPLOSION_BULLET_SPACESHIP, EXPLOSION_BULLET_ALIEN, EXPLOSION_SPACESHIP, EXPLOSION_UFO, EXPLOSION_ALIEN};

void
testExplosionCreate(void **status)
{
    (void)status;

    for (size_t i = 0; i < sizeof(explosions) / sizeof(explosions[0]); i++)
    {
        expect_function_call(__wrap_utilsCalloc);
        expect_function_call(__wrap_utilsCalloc);
        if (i == EXPLOSION_SPACESHIP)
        {
            will_return(__wrap_clock_gettime, 0); /* tv_sec */
            will_return(__wrap_clock_gettime, 0); /* tv_nsec */
            expect_function_call(__wrap_clock_gettime);
        }
        will_return(__wrap_clock_gettime, 0); /* tv_sec */
        will_return(__wrap_clock_gettime, 0); /* tv_nsec */
        expect_function_call(__wrap_clock_gettime);
        expect_function_call(__wrap_graphRegisterPrint);

        explosionCreate(0, 0, explosions[i], NULL);
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
    registerExplosionBullet(NULL);

    will_return(__wrap_utilsCheckTimeout, false);
    expect_function_call(__wrap_utilsCheckTimeout);
    explosionsDestroy();
}

void
testExplosionsDestroyTimeoutTrue(void **status)
{
    (void)status;
    registerExplosionBullet(NULL);

    will_return(__wrap_utilsCheckTimeout, true);
    expect_function_call(__wrap_utilsCheckTimeout);
    expect_function_call(__wrap_graphUnregisterPrint);

    explosionsDestroy();
}

static void
foo(void)
{
    function_called();
}

void
testExplosionsDestroyTimeoutCallback(void **status)
{
    (void)status;
    registerExplosionBullet(foo);

    will_return(__wrap_utilsCheckTimeout, true);
    expect_function_call(__wrap_utilsCheckTimeout);
    expect_function_call(__wrap_graphUnregisterPrint);
    expect_function_call(foo);

    explosionsDestroy();
}

void
testExplosionsDestroyTwoExplosions(void **status)
{
    (void)status;
    int number_explosions = 2;

    for (int i = 0; i < number_explosions; i++)
    {
        registerExplosionBullet(NULL);
    }

    /* first registered explosion */
    will_return(__wrap_utilsCheckTimeout, false);
    expect_function_call(__wrap_utilsCheckTimeout);

    /* second registered explosion */
    will_return(__wrap_utilsCheckTimeout, true);
    expect_function_call(__wrap_utilsCheckTimeout);
    expect_function_call(__wrap_graphUnregisterPrint);

    explosionsDestroy();
}

void
testExplosionDestroyMoreOneFrame(void **status)
{
    (void)status;

    /* Only EXPLOSION_SPACESHIP has more than one frame */
    registerExplosionSpaceship(NULL);

    will_return(__wrap_utilsCheckTimeout, true);
    expect_function_call(__wrap_utilsCheckTimeout);
    expect_function_call(__wrap_graphNextImageToPrint);
    will_return(__wrap_clock_gettime, 0); /* tv_sec */
    will_return(__wrap_clock_gettime, 0); /* tv_nsec */
    expect_function_call(__wrap_clock_gettime);
    will_return(__wrap_utilsCheckTimeout, false);
    expect_function_call(__wrap_utilsCheckTimeout);

    explosionsDestroy();
}

void
testExplosionDestroyMoreOneFrameTimeoutFalse(void **status)
{
    (void)status;

    /* Only EXPLOSION_SPACESHIP has more than one frame */
    registerExplosionSpaceship(NULL);

    will_return(__wrap_utilsCheckTimeout, false);
    expect_function_call(__wrap_utilsCheckTimeout);
    will_return(__wrap_utilsCheckTimeout, false);
    expect_function_call(__wrap_utilsCheckTimeout);

    explosionsDestroy();
}

void
testExplosionAllFinishedTrue(void **status)
{
    (void)status;

    assert_true(explosionsAllFinished());
}

void
testExplosionAllFinishedFalse(void **status)
{
    (void)status;

    registerExplosionBullet(NULL);
    assert_false(explosionsAllFinished());
}

static const unsigned int expected_explosion_heights[] = {
    [EXPLOSION_BULLET_SPACESHIP] = 8,
    [EXPLOSION_BULLET_ALIEN] = 8,
    [EXPLOSION_SPACESHIP] = 8,
    [EXPLOSION_UFO] = 8,
    [EXPLOSION_ALIEN] = 8,
};

void
testExplosionsGetExplosionHeight(void **status)
{
    (void)status;

    for (size_t i = 0; i < sizeof(explosions) / sizeof(explosions[0]); i++)
    {
        assert_uint_equal(expected_explosion_heights[i], explosionsGetExplosionHeight(explosions[i]));
    }
}
