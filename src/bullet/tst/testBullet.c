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
#include <stdlib.h>

int
setup(void **state)
{
    (void)state;
    helperUT_bulletInitPool();
    return 0;
}

int
__wrap_rand(void)
{
    function_called();
    return (int)mock();
}

static bullet_type_t bullets[] = {BULLET_SPACESHIP, BULLET_ALIEN};

void
testBulletCreate(void **status)
{
    (void)status;

    for (size_t i = 0; i < sizeof(bullets) / sizeof(bullets[0]); i++)
    {
        if (bullets[i] != BULLET_SPACESHIP)
        {
            will_return(__wrap_rand, 1);
            expect_function_call(__wrap_rand);
        }

        expect_function_call(__wrap_graphCreateImage);
        expect_function_call(__wrap_graphRegisterPrint);

        bulletCreate(0, 0, bullets[i]);
    }
}

void
testBulletCreateAllTypeBulletAlien(void **status)
{
    (void)status;

    /* crackle */
    will_return(__wrap_rand, 0);
    expect_function_call(__wrap_rand);

    expect_function_call(__wrap_graphCreateImage);
    expect_function_call(__wrap_graphRegisterPrint);

    bulletCreate(0, 0, BULLET_ALIEN);

    /* coil */
    will_return(__wrap_rand, 50);
    expect_function_call(__wrap_rand);

    expect_function_call(__wrap_graphCreateImage);
    expect_function_call(__wrap_graphRegisterPrint);

    bulletCreate(0, 0, BULLET_ALIEN);

    /* plasma */
    will_return(__wrap_rand, 80);
    expect_function_call(__wrap_rand);

    expect_function_call(__wrap_graphCreateImage);
    expect_function_call(__wrap_graphRegisterPrint);

    bulletCreate(0, 0, BULLET_ALIEN);
}

void
testBulletCreateTwoBulletSpaceship(void **status)
{
    (void)status;

    expect_function_call(__wrap_graphCreateImage);
    expect_function_call(__wrap_graphRegisterPrint);

    bulletCreate(0, 0, BULLET_SPACESHIP);
    bulletCreate(0, 0, BULLET_SPACESHIP);
}

void
testBulletDestroyNullParameter(void **status)
{
    (void)status;

    bulletDestroy(NULL);
}

void
testBulletDestroy(void **status)
{
    (void)status;
    bullet_t bullet = helperUT_bulletInjectInPool(0, BULLET_SPACESHIP);

    expect_function_call(__wrap_graphGetSprite);
    expect_function_call(__wrap_graphUnregisterPrint);
    expect_function_call(__wrap_graphDestroyImage);

    bulletDestroy(bullet);
}

void
testBulletUsedNullParameter(void **status)
{
    (void)status;

    assert_false(bulletUsed(NULL));
}

void
testBulletUsedFalse(void **status)
{
    (void)status;
    bullet_t bullet = helperUT_bulletInjectInPool(0, BULLET_SPACESHIP);
    helperUT_bulletSetUsed(bullet, false);

    assert_false(bulletUsed(bullet));
}

void
testBulletUsedTrue(void **status)
{
    (void)status;
    bullet_t bullet = helperUT_bulletInjectInPool(0, BULLET_SPACESHIP);

    assert_true(bulletUsed(bullet));
}

void
testBulletGetTypeNullParameters(void **status)
{
    (void)status;
    bullet_t bullet = (bullet_t)0xdeadbeef;
    bullet_type_t *type = (bullet_type_t *)0xdeadbeef;

    assert_int_equal(-1, bulletGetType(NULL, NULL));
    assert_int_equal(-1, bulletGetType(bullet, NULL));
    assert_int_equal(-1, bulletGetType(NULL, type));
}

void
testBulletGetType(void **status)
{
    (void)status;
    bullet_t bullet = helperUT_bulletInjectInPool(0, BULLET_ALIEN);
    bullet_type_t type;

    assert_int_equal(0, bulletGetType(bullet, &type));
    assert_int_equal(BULLET_ALIEN, type);
}

void
testBulletCallFunctionForEachNullParameter(void **status)
{
    (void)status;

    bulletCallFunctionForEach(NULL);
}

static void
foo(bullet_t bullet)
{
    (void)bullet;
    function_called();
}

void
testBulletCallFunctionForEachBulletPoolEmpty(void **status)
{
    (void)status;

    bulletCallFunctionForEach(foo);
}

void
testBulletCallFunctionForEach(void **status)
{
    (void)status;

    helperUT_bulletInjectInPool(0, BULLET_SPACESHIP);

    expect_function_call(foo);

    bulletCallFunctionForEach(foo);
}

void
testBulletAlienInhibit(void **status)
{
    (void)status;

    bulletAlienInhibit(true);
    bulletCreate(0, 0, BULLET_ALIEN);
    assert_true(bulletNoneUsed());
}

void
testBulletNoneUsedTrue(void **status)
{
    (void)status;

    assert_true(bulletNoneUsed());
}

void
testBulletNoneUsedFalse(void **status)
{
    (void)status;

    helperUT_bulletInjectInPool(0, BULLET_SPACESHIP);

    assert_false(bulletNoneUsed());
}
