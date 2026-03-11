/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testAliens.h"
#include "aliens.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

void
testAliensCreate(void **status)
{
    (void)status;

    for (int i = 0; i < aliensGetNumberInitialAliens(); i++)
    {
        expect_function_call(__wrap_utilsCalloc);
        expect_function_call(__wrap_graphCreateImage);
        expect_function_call(__wrap_graphUpdateTimeSprite);
        expect_function_call(__wrap_graphRegisterPrint);
    }

    aliensCreate();

    for (int i = 0; i < aliensGetNumberInitialAliens(); i++)
    {
        assert_non_null(aliensGetAlienInstance(i));
    }
}

void
testAliensGetAlienInstanceInvalidIndex(void **status)
{
    (void)status;

    assert_null(aliensGetAlienInstance(aliensGetNumberInitialAliens() + 1));
}
