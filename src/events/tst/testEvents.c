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
foo_cb(void *data)
{
    check_expected_ptr(data);
    function_called();
}

void
testEventRegister(void **status)
{
    (void)status;

    eventRegister(EVENT_LIVES_DEPLETED, foo_cb);

    assert_uint_equal((uintptr_t)foo_cb, (uintptr_t)helperUT_eventGetCallback(EVENT_LIVES_DEPLETED, 0));
}

void
testEventMaxRegistered(void **status)
{
    (void)status;

    for (int i = 0; i < EVENTS_MAX_NUM_CB; i++)
    {
        eventRegister(EVENT_LIVES_DEPLETED, foo_cb);
        assert_uint_equal((uintptr_t)foo_cb, (uintptr_t)helperUT_eventGetCallback(EVENT_LIVES_DEPLETED, i));
    }

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
    int expected_data = 0;

    for (int i = 0; i < EVENTS_MAX_NUM_CB; i++)
    {
        helperUT_eventSetCallback(EVENT_LIVES_DEPLETED, i, foo_cb);

        expect_uint_value(foo_cb, data, (uintptr_t)&expected_data);
        expect_function_call(foo_cb);
    }

    eventEmit(EVENT_LIVES_DEPLETED, &expected_data);
}

void
testEventEmitNotRegistered(void **status)
{
    (void)status;

    eventEmit(EVENT_LIVES_DEPLETED, NULL);
}

void
testEventEmitInvalidType(void **status)
{
    (void)status;

    eventEmit(-1, NULL);
    eventEmit(EVENT_COUNT, NULL);
}
