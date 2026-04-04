/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testUtils.h"
#include "utils.h"
#include <cmocka.h>
#include <errno.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

extern void *
__real_calloc(size_t nelem, size_t elsize);

void *
__wrap_calloc(size_t nelem, size_t elsize)
{
    bool call_real = mock_type(bool);

    if (call_real)
    {
        return __real_calloc(nelem, elsize);
    }
    check_expected_int(nelem);
    check_expected_int(elsize);
    function_called();
    return (void *)mock();
}

void
__wrap_perror(const char *s)
{
    check_expected_ptr(s);
    function_called();
}

void
__wrap_exit(int status)
{
    check_expected_int(status);
    function_called();
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

void
testUtilsCallocFail(void **status)
{
    (void)status;

    will_return(__wrap_calloc, false);
    will_return(__wrap_calloc, NULL);
    expect_int_value(__wrap_calloc, nelem, 1);
    expect_int_value(__wrap_calloc, elsize, 1);
    expect_function_call(__wrap_calloc);
    expect_string(__wrap_perror, s, "calloc");
    expect_function_call(__wrap_perror);
    expect_int_value(__wrap_exit, status, EXIT_FAILURE);
    expect_function_call(__wrap_exit);

    utilsCalloc(1, 1);
}

void
testUtilsCallocSuccess(void **status)
{
    (void)status;
    void *expected = (void *)0x12345678;

    will_return(__wrap_calloc, false);
    will_return(__wrap_calloc, expected);
    expect_int_value(__wrap_calloc, nelem, 1);
    expect_int_value(__wrap_calloc, elsize, 1);
    expect_function_call(__wrap_calloc);

    assert_ptr_equal(utilsCalloc(1, 1), expected);
}

void
testUtilsCheckTimeoutNegativeTimeoutParameter(void **status)
{
    (void)status;
    struct timespec time = {0};

    assert_false(utilsCheckTimeout(time, -1));
}

void
testUtilsCheckTimeoutExact(void **status)
{
    (void)status;
    struct timespec time = {.tv_sec = 0, .tv_nsec = 0};

    will_return(__wrap_clock_gettime, (time_t)0);
    will_return(__wrap_clock_gettime, (long)(500 * NS_PER_MS));
    expect_function_call(__wrap_clock_gettime);

    assert_true(utilsCheckTimeout(time, 500 * NS_PER_MS));
}

void
testUtilsCheckTimeoutBefore(void **status)
{
    (void)status;
    struct timespec time = {.tv_sec = 0, .tv_nsec = 0};

    will_return(__wrap_clock_gettime, (time_t)0);
    will_return(__wrap_clock_gettime, (long)(499999999));
    expect_function_call(__wrap_clock_gettime);

    assert_false(utilsCheckTimeout(time, 500 * NS_PER_MS));
}

void
testUtilsCheckTimeoutZero(void **status)
{
    (void)status;
    struct timespec time = {.tv_sec = 0, .tv_nsec = 0};

    will_return(__wrap_clock_gettime, (time_t)1);
    will_return(__wrap_clock_gettime, (long)(123456789));
    expect_function_call(__wrap_clock_gettime);

    assert_true(utilsCheckTimeout(time, 0));
}

void
testUtilsCheckTimeoutFuture(void **status)
{
    (void)status;
    struct timespec time = {.tv_sec = 1, .tv_nsec = 500 * NS_PER_MS};

    will_return(__wrap_clock_gettime, (time_t)1);
    will_return(__wrap_clock_gettime, (long)(500 * NS_PER_MS - 1));
    expect_function_call(__wrap_clock_gettime);

    assert_false(utilsCheckTimeout(time, 500 * NS_PER_MS));
}
