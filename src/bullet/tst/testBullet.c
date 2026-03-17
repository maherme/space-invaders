/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testBullet.h"
#include "bullet.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

void
testBulletCreate(void **status)
{
    (void)status;

    expect_function_call(__wrap_utilsCalloc);
    expect_function_call(__wrap_graphCreateImage);
    expect_function_call(__wrap_graphRegisterPrint);

    bullet_t bullet = bulletCreate(0, 0);
    assert_non_null(bullet);
}

void
testBulletDestroyNullParameter(void **status)
{
    (void)status;
    bullet_t ptr = NULL;

    bulletDestroy(NULL);
    bulletDestroy(&ptr);
}

void
testBulletDestroy(void **status)
{
    (void)status;
    bullet_t bullet = (bullet_t)0xdeadbeef;

    expect_function_call(__wrap_graphGetSprite);
    expect_function_call(__wrap_graphUnregisterPrint);
    expect_function_call(__wrap_graphDestroyImage);
    expect_uint_value(__wrap_utilsFree, ptr, (uintptr_t)&bullet);
    expect_function_call(__wrap_utilsFree);

    bulletDestroy(&bullet);
}
