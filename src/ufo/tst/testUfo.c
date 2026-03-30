/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testUfo.h"
#include "ufo.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

int
__wrap_rand(void)
{
    function_called();
    return (int)mock();
}

void
testUfoCreateLeftDirection(void **status)
{
    (void)status;

    will_return(__wrap_rand, 1);
    expect_function_call(__wrap_rand);
    expect_function_call(__wrap_graphUpdateTimeSprite);
    expect_function_call(__wrap_graphRegisterPrint);

    ufo_t ufo = ufoCreate();
    assert_int_equal(LEFT, ufoGetDirection(ufo));
}

void
testUfoCreateRightDirection(void **status)
{
    (void)status;

    will_return(__wrap_rand, RAND_MAX);
    expect_function_call(__wrap_rand);
    expect_function_call(__wrap_graphUpdateTimeSprite);
    expect_function_call(__wrap_graphRegisterPrint);

    ufo_t ufo = ufoCreate();
    assert_int_equal(RIGHT, ufoGetDirection(ufo));
}

void
testUfoDestroyNullParameter(void **status)
{
    (void)status;

    ufoDestroy(NULL);
}

void
testUfoDestroy(void **status)
{
    (void)status;
    ufo_t ufo = helperUT_ufoGetInstance();

    expect_function_call(__wrap_graphGetSprite);
    expect_function_call(__wrap_graphUnregisterPrint);

    ufoDestroy(ufo);

    assert_false(ufoAlive(ufo));
}

void
testUfoAliveNullParameter(void **status)
{
    (void)status;

    assert_false(ufoAlive(NULL));
}

void
testUfoAliveFalse(void **status)
{
    (void)status;
    ufo_t ufo = helperUT_ufoGetInstance();
    helperUT_ufoSetAlive(ufo, false);

    assert_false(ufoAlive(ufo));
}

void
testUfoAliveTrue(void **status)
{
    (void)status;
    ufo_t ufo = helperUT_ufoGetInstance();

    assert_true(ufoAlive(ufo));
}

void
testUfoGetDirectionNullParameter(void **status)
{
    (void)status;

    assert_int_equal(INVALID_DIR, ufoGetDirection(NULL));
}

void
testUfoCheckForMovingNullParameter(void **status)
{
    (void)status;

    assert_false(ufoCheckForMoving(NULL));
}

void
testUfoCheckForMovingAliveFalse(void **status)
{
    (void)status;

    ufo_t ufo = helperUT_ufoGetInstance();
    helperUT_ufoSetAlive(ufo, false);

    assert_false(ufoCheckForMoving(ufo));
}

void
testUfoCheckForMovingTimeoutFalse(void **status)
{
    (void)status;

    ufo_t ufo = helperUT_ufoGetInstance();
    helperUT_ufoSetTimeToAppear(ufo, 1);

    will_return(__wrap_utilsCheckTimeout, false);
    expect_function_call(__wrap_utilsCheckTimeout);

    assert_false(ufoCheckForMoving(ufo));
}

void
testUfoCheckForMovingTrue(void **status)
{
    (void)status;

    ufo_t ufo = helperUT_ufoGetInstance();
    helperUT_ufoSetTimeToAppear(ufo, 1);

    will_return(__wrap_utilsCheckTimeout, true);
    expect_function_call(__wrap_utilsCheckTimeout);

    assert_true(ufoCheckForMoving(ufo));
}

void
testUfoCheckForMovingTrueMoreCalls(void **status)
{
    (void)status;

    ufo_t ufo = helperUT_ufoGetInstance();
    helperUT_ufoSetTimeToAppear(ufo, 1);

    will_return(__wrap_utilsCheckTimeout, true);
    expect_function_call(__wrap_utilsCheckTimeout);

    assert_true(ufoCheckForMoving(ufo));
    /* no more calls to utilsCheckTimeout are expected from here */
    assert_true(ufoCheckForMoving(ufo));
}
