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
#include <stdlib.h>

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
testAlienDestroyNullParameter(void **status)
{
    (void)status;
    alien_t ptr = NULL;

    alienDestroy(NULL);
    alienDestroy(&ptr);
}

void
testAlienDestroy(void **status)
{
    (void)status;
    alien_t alien = (alien_t)0xdeadbeef;

    expect_function_call(__wrap_graphGetSprite);
    expect_function_call(__wrap_graphUnregisterPrint);
    expect_function_call(__wrap_graphDestroyImage);
    expect_uint_value(__wrap_utilsFree, ptr, (uintptr_t)&alien);
    expect_function_call(__wrap_utilsFree);

    alienDestroy(&alien);
}

void
testAliensGetAlienInstanceInvalidIndex(void **status)
{
    (void)status;

    assert_null(aliensGetAlienInstance(aliensGetNumberInitialAliens() + 1));
}
