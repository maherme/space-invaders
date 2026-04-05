/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testLives.h"
#include "events.h"
#include "graph.h"
#include "lives.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

static void
checkEmitEventLivesDepleted(void)
{
    expect_uint_value(__wrap_eventEmit, data, (uintptr_t)NULL);
    expect_uint_value(__wrap_eventEmit, type, EVENT_LIVES_DEPLETED);
    expect_function_call(__wrap_eventEmit);
}

void
testLivesCreate(void **status)
{
    (void)status;
    int expected_printed_lives = 2;
    int expected_num_lives = 3;
    int x = 1, y = 2;
    int expected_x_sprite1 = x;
    int expected_x_sprite2 = 18;
    int expected_y_sprites = y;

    for (int i = 0; i < expected_printed_lives; i++)
    {
        expect_uint_value(__wrap_graphRegisterPrint, sprite, (uintptr_t)helperUT_livesGetSpriteByInstanceIndex(i));
        expect_function_call(__wrap_graphRegisterPrint);
    }

    livesCreate(x, y);
    assert_int_equal(expected_num_lives, helperUT_livesGetNumLives());
    sprite_t *sprite1 = helperUT_livesGetSpriteByInstanceIndex(0);
    assert_int_equal(expected_x_sprite1, sprite1->x);
    assert_int_equal(expected_y_sprites, sprite1->y);
    sprite_t *sprite2 = helperUT_livesGetSpriteByInstanceIndex(1);
    assert_int_equal(expected_x_sprite2, sprite2->x);
    assert_int_equal(expected_y_sprites, sprite2->y);
}

void
testLivesRemoveLastLive(void **status)
{
    (void)status;

    helperUT_livesSetNumLives(1);
    checkEmitEventLivesDepleted();

    livesRemove();
    assert_int_equal(0, helperUT_livesGetNumLives());
}

void
testLivesRemovePenultimateLive(void **status)
{
    (void)status;
    int num_lives_no_last = 2;

    helperUT_livesSetNumLives(num_lives_no_last);
    expect_uint_value(__wrap_graphUnregisterPrint, sprite, (uintptr_t)helperUT_livesGetSpriteByInstanceIndex(0));
    expect_function_call(__wrap_graphUnregisterPrint);

    livesRemove();
    assert_int_equal(num_lives_no_last - 1, helperUT_livesGetNumLives());
}

void
testLivesRemoveMaxLivesPrinted(void **status)
{
    (void)status;
    int num_lives_no_more_print = 6;

    helperUT_livesSetNumLives(num_lives_no_more_print);

    livesRemove();
    assert_int_equal(num_lives_no_more_print - 1, helperUT_livesGetNumLives());
}

void
testLivesRemoveZeroLives(void **status)
{
    (void)status;

    helperUT_livesSetNumLives(0);

    livesRemove();
    assert_int_equal(0, helperUT_livesGetNumLives());
}

void
testLivesAdd(void **status)
{
    (void)status;
    int num_lives = 1;

    helperUT_livesSetNumLives(num_lives);
    expect_uint_value(__wrap_graphRegisterPrint, sprite, (uintptr_t)helperUT_livesGetSpriteByInstanceIndex(num_lives - 1));
    expect_function_call(__wrap_graphRegisterPrint);

    livesAdd();
    assert_int_equal(num_lives + 1, helperUT_livesGetNumLives());
}

void
testLivesAddMaxLivesPrinted(void **status)
{
    (void)status;
    int num_lives = 5;

    helperUT_livesSetNumLives(num_lives);

    livesAdd();
    assert_int_equal(num_lives + 1, helperUT_livesGetNumLives());
}

void
testLivesAddZeroLives(void **status)
{
    (void)status;

    helperUT_livesSetNumLives(0);

    livesAdd();
    assert_int_equal(0, helperUT_livesGetNumLives());
}
