/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testBunkers.h"
#include "bunkers.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

void
testBunkersCreate(void **status)
{
    (void)status;

    /* Shall be 4 bunkers */
    for (int i = 0; i < 4; i++)
    {
        expect_function_call(__wrap_graphRegisterPrint);
    }

    bunkersCreate();
}

void
testBunkersCallFunctionForEachNullParameter(void **status)
{
    (void)status;

    bunkersCallFunctionForEach(NULL, NULL);
}

static void
foo(bunker_t bunker, void *ctx)
{
    (void)bunker;
    check_expected_ptr(ctx);
    function_called();
}

void
testBunkersCallFunctionForEach(void **status)
{
    (void)status;
    void *expected_ctx = (void *)0xdeadbeef;

    for (int i = 0; i < 4; i++)
    {
        expect_uint_value(foo, ctx, (uintptr_t)expected_ctx);
        expect_function_call(foo);
    }

    bunkersCallFunctionForEach(foo, expected_ctx);
}
