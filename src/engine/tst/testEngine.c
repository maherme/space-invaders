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

void
testEngineRegisterFailNullParameter(void **status)
{
    (void)status;

    expect_uint_value(__wrap_usleep, usec, 1000);
    expect_function_call(__wrap_usleep);

    int result = engineRegister(NULL);
    assert_int_equal(result, -1);
    engineRun(1);
}

void
testEngineRegisterFailMaxCallbacks(void **status)
{
    (void)status;

    expect_function_calls(callback_foo, ENGINE_MAX_CALLBACKS);
    expect_uint_value(__wrap_usleep, usec, 1000);
    expect_function_call(__wrap_usleep);

    for (int i = 0; i < ENGINE_MAX_CALLBACKS; i++)
    {
        engineRegister(callback_foo);
    }
    int result = engineRegister(callback_foo);
    assert_int_equal(result, -1);
    engineRun(1);
}

void
testEngineRegisterSuccess(void **status)
{
    (void)status;

    expect_function_call(callback_foo);
    expect_uint_value(__wrap_usleep, usec, 1000);
    expect_function_call(__wrap_usleep);

    int result = engineRegister(callback_foo);
    assert_int_equal(result, 0);
    engineRun(1);
}

void
testEngineUnregisterFailNullParameter(void **status)
{
    (void)status;

    expect_uint_value(__wrap_usleep, usec, 1000);
    expect_function_call(__wrap_usleep);

    int result = engineUnregister(callback_foo);
    assert_int_equal(result, -1);
    engineRun(1);
}

void
testEngineUnregisterNoCallbackFound(void **status)
{
    (void)status;

    expect_uint_value(__wrap_usleep, usec, 1000);
    expect_function_call(__wrap_usleep);

    int result = engineUnregister(NULL);
    assert_int_equal(result, -1);
    engineRun(1);
}

void
testEngineUnregisterSuccess(void **status)
{
    (void)status;

    expect_function_call(callback_foo);
    expect_uint_value(__wrap_usleep, usec, 1000);
    expect_function_call(__wrap_usleep);

    int result = engineRegister(callback_foo);
    assert_int_equal(result, 0);
    engineRun(1);

    expect_uint_value(__wrap_usleep, usec, 1000);
    expect_function_call(__wrap_usleep);

    result = engineUnregister(callback_foo);
    assert_int_equal(result, 0);
    engineRun(1);
}
