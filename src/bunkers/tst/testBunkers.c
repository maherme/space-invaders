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
        expect_function_call(__wrap_graphCreateImage);
        expect_function_call(__wrap_graphRegisterPrint);
    }

    bunkersCreate();
}
