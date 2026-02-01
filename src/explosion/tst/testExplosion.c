/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "explosion.h"
#include "testExplosion.h"

int
__wrap_clock_gettime(clockid_t clockid,
                     struct timespec *tp) {
    assert_int_equal(clockid, CLOCK_MONOTONIC);
    assert_non_null(tp);
    tp->tv_sec = (time_t)mock_type(time_t);
    tp->tv_nsec = (long)mock_type(long);
    function_called();
    return 0;
}

void
testExplosionCreate(void **status) {
    (void)status;
    int x_pos = 10;
    int y_pos = 20;

    expect_function_call(__wrap_utilsCalloc);
    expect_function_call(__wrap_graphCreateImage);
    will_return(__wrap_clock_gettime, 0);   /* tv_sec */
    will_return(__wrap_clock_gettime, 0);   /* tv_nsec */
    expect_function_call(__wrap_clock_gettime);

    explosion_t explosion = explosionCreate(x_pos, y_pos);
    sprite_t *sprite = graphGetSprite((base_t *)explosion);

    assert_int_equal(sprite->x, x_pos);
    assert_int_equal(sprite->y, y_pos);
}

void
testExplosionTimeoutNullParameter(void **status) {
    (void)status;

    assert_false(explosionTimeout(NULL));
}

void
testExplosionTimeoutTrue(void **status) {
    (void)status;

    expect_function_call(__wrap_utilsCalloc);
    expect_function_call(__wrap_graphCreateImage);
    will_return(__wrap_clock_gettime, 0);   /* tv_sec */
    will_return(__wrap_clock_gettime, 0);   /* tv_nsec */
    expect_function_call(__wrap_clock_gettime);
    explosion_t explosion = explosionCreate(0, 0);

    will_return(__wrap_clock_gettime, 0);            /* tv_sec */
    will_return(__wrap_clock_gettime, 500000000);    /* tv_nsec */
    expect_function_call(__wrap_clock_gettime);
    assert_true(explosionTimeout(explosion));
}

void
testExplosionTimeoutFalse(void **status) {
    (void)status;

    expect_function_call(__wrap_utilsCalloc);
    expect_function_call(__wrap_graphCreateImage);
    will_return(__wrap_clock_gettime, 0);   /* tv_sec */
    will_return(__wrap_clock_gettime, 0);   /* tv_usec */
    expect_function_call(__wrap_clock_gettime);
    explosion_t explosion = explosionCreate(0, 0);

    will_return(__wrap_clock_gettime, 0);           /* tv_sec */
    will_return(__wrap_clock_gettime, 499999999);   /* tv_nsec */
    expect_function_call(__wrap_clock_gettime);
    assert_false(explosionTimeout(explosion));
}
