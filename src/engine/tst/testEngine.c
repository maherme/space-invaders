/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testEngine.h"
#include "engine.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

int
__wrap_usleep(useconds_t usec)
{
    (void)usec;
    check_expected_uint(usec);
    function_called();
    return 0;
}

int
setup(void **state)
{
    (void)state;
    helperUT_engineResetRegisteredCallbacks();
    return 0;
}

static void
callback_foo(void)
{
    function_called();
}

static void
callback_fuu(void)
{
    function_called();
}

static void
register_callback_ok(engine_cb_t cb)
{
    expect_function_call(__wrap_utilsCalloc);
    int result = engineRegister(cb);
    assert_int_equal(result, 0);
}

static void
check_enginerun(bool cb_called)
{
    if (cb_called)
    {
        expect_function_call(callback_foo);
    }
    expect_uint_value(__wrap_usleep, usec, 1000);
    expect_function_call(__wrap_usleep);

    engineRun(1);
}

void
testEngineRegisterFailNullParameter(void **status)
{
    (void)status;

    int result = engineRegister(NULL);
    assert_int_equal(result, -1);

    check_enginerun(false);
}

void
testEngineRegisterSuccess(void **status)
{
    (void)status;

    register_callback_ok(callback_foo);
    check_enginerun(true);
}

void
testEngineUnregisterFailNullParameter(void **status)
{
    (void)status;

    int result = engineUnregister(NULL);
    assert_int_equal(result, -1);

    check_enginerun(false);
}

void
testEngineUnregisterNoCallbackFound(void **status)
{
    (void)status;

    register_callback_ok(callback_foo);

    int result = engineUnregister(callback_fuu);
    assert_int_equal(result, 0);

    check_enginerun(true);
}

void
testEngineUnregisterSuccess(void **status)
{
    (void)status;

    register_callback_ok(callback_foo);

    check_enginerun(true);

    int result = engineUnregister(callback_foo);
    assert_int_equal(result, 1);

    check_enginerun(false);
}
