/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testEvents.h"
#include "events.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

int
setup(void **state)
{
    (void)state;
    helperUT_eventsClear();
    return 0;
}

void
foo_cb(void)
{
    function_called();
}

void
testEventRegister(void **status)
{
    (void)status;

    eventRegister(EVENT_LIVES_DEPLETED, foo_cb);

    assert_uint_equal((uintptr_t)foo_cb, (uintptr_t)helperUT_eventGetCallback(EVENT_LIVES_DEPLETED));
}

void
testEventAlreadyRegistered(void **status)
{
    (void)status;

    eventRegister(EVENT_LIVES_DEPLETED, foo_cb);

    assert_uint_equal((uintptr_t)foo_cb, (uintptr_t)helperUT_eventGetCallback(EVENT_LIVES_DEPLETED));

    eventRegister(EVENT_LIVES_DEPLETED, foo_cb);
}

void
testEventRegisterInvalidType(void **status)
{
    (void)status;

    eventRegister(-1, foo_cb);
    eventRegister(EVENT_COUNT, foo_cb);
}

void
testEventEmit(void **status)
{
    (void)status;

    helperUT_eventSetCallback(EVENT_LIVES_DEPLETED, foo_cb);

    expect_function_call(foo_cb);

    eventEmit(EVENT_LIVES_DEPLETED);
}

void
testEventEmitNotRegistered(void **status)
{
    (void)status;

    eventEmit(EVENT_LIVES_DEPLETED);
}

void
testEventEmitInvalidType(void **status)
{
    (void)status;

    eventEmit(-1);
    eventEmit(EVENT_COUNT);
}
