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

    expect_function_call(__wrap_utilsCalloc);
    will_return(__wrap_rand, 1);
    expect_function_call(__wrap_rand);
    expect_function_call(__wrap_graphScaleImage);
    expect_function_call(__wrap_graphCreateImage);
    expect_function_call(__wrap_graphUpdateTimeSprite);
    expect_function_call(__wrap_graphRegisterPrint);

    ufo_t ufo = ufoCreate();
    assert_int_equal(LEFT, ufoGetDirection(ufo));

    free(ufo);
}

void
testUfoCreateRightDirection(void **status)
{
    (void)status;

    expect_function_call(__wrap_utilsCalloc);
    will_return(__wrap_rand, RAND_MAX);
    expect_function_call(__wrap_rand);
    expect_function_call(__wrap_graphScaleImage);
    expect_function_call(__wrap_graphCreateImage);
    expect_function_call(__wrap_graphUpdateTimeSprite);
    expect_function_call(__wrap_graphRegisterPrint);

    ufo_t ufo = ufoCreate();
    assert_int_equal(RIGHT, ufoGetDirection(ufo));

    free(ufo);
}

void
testUfoDestroyNullParameter(void **status)
{
    (void)status;
    ufo_t ptr = NULL;

    ufoDestroy(NULL);
    ufoDestroy(&ptr);
}

void
testUfoDestroy(void **status)
{
    (void)status;
    ufo_t ufo = (ufo_t)0xdeadbeef;

    expect_function_call(__wrap_graphGetSprite);
    expect_function_call(__wrap_graphUnregisterPrint);
    expect_function_call(__wrap_graphDestroyImage);
    expect_uint_value(__wrap_utilsFree, ptr, (uintptr_t)&ufo);
    expect_function_call(__wrap_utilsFree);

    ufoDestroy(&ufo);
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
testUfoCheckForMovingFalse(void **status)
{
    (void)status;

    expect_function_call(__wrap_utilsCalloc);
    will_return(__wrap_rand, RAND_MAX);
    expect_function_call(__wrap_rand);
    expect_function_call(__wrap_graphScaleImage);
    expect_function_call(__wrap_graphCreateImage);
    expect_function_call(__wrap_graphUpdateTimeSprite);
    expect_function_call(__wrap_graphRegisterPrint);

    ufo_t ufo = ufoCreate();

    will_return(__wrap_utilsCheckTimeout, false);
    expect_function_call(__wrap_utilsCheckTimeout);

    assert_false(ufoCheckForMoving(ufo));

    free(ufo);
}

void
testUfoCheckForMovingTrue(void **status)
{
    (void)status;

    expect_function_call(__wrap_utilsCalloc);
    will_return(__wrap_rand, RAND_MAX);
    expect_function_call(__wrap_rand);
    expect_function_call(__wrap_graphScaleImage);
    expect_function_call(__wrap_graphCreateImage);
    expect_function_call(__wrap_graphUpdateTimeSprite);
    expect_function_call(__wrap_graphRegisterPrint);

    ufo_t ufo = ufoCreate();

    will_return(__wrap_utilsCheckTimeout, true);
    expect_function_call(__wrap_utilsCheckTimeout);

    assert_true(ufoCheckForMoving(ufo));

    free(ufo);
}

void
testUfoCheckForMovingTrueMoreCalls(void **status)
{
    (void)status;

    expect_function_call(__wrap_utilsCalloc);
    will_return(__wrap_rand, RAND_MAX);
    expect_function_call(__wrap_rand);
    expect_function_call(__wrap_graphScaleImage);
    expect_function_call(__wrap_graphCreateImage);
    expect_function_call(__wrap_graphUpdateTimeSprite);
    expect_function_call(__wrap_graphRegisterPrint);

    ufo_t ufo = ufoCreate();

    will_return(__wrap_utilsCheckTimeout, true);
    expect_function_call(__wrap_utilsCheckTimeout);

    assert_true(ufoCheckForMoving(ufo));
    /* no more calls to utilsCheckTimeout are expected from here */
    assert_true(ufoCheckForMoving(ufo));

    free(ufo);
}
