/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testScore.h"
#include "events.h"
#include "score.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

int
setup(void **status)
{
    (void)status;
    helperUT_scoreReset();
    return 0;
}

void
testScoreInit(void **status)
{
    (void)status;

    expect_uint_value(__wrap_eventEmit, type, EVENT_SCORE_CHANGED);
    expect_uint_value(__wrap_eventEmit, value, 0);
    expect_function_call(__wrap_eventEmit);

    scoreInit();

    assert_uint_equal(0, helperUT_scoreGetScore());
}

void
testScoreAddPoints(void **status)
{
    (void)status;
    unsigned int expected_points = 50;

    expect_uint_value(__wrap_eventEmit, type, EVENT_SCORE_CHANGED);
    expect_uint_value(__wrap_eventEmit, value, expected_points);
    expect_function_call(__wrap_eventEmit);

    scoreAddPoints(expected_points);

    assert_uint_equal(expected_points, helperUT_scoreGetScore());
}
