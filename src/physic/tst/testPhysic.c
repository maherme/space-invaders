/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testPhysic.h"

int
__wrap_gettimeofday(struct timeval *restrict tv, struct timezone *restrict tz) {
    if(tv) {
        tv->tv_sec = mock_type(time_t);
        tv->tv_usec = mock_type(suseconds_t);
    }
    check_expected_ptr(tz);
    function_called();
    return 0;
}

void
testPhysicMoveSpriteFail(void **status) {
    (void)status;

    physicMoveSprite(NULL, RIGHT);
}

void
testPhysicMoveSpriteWrongDirection(void **status) {
    (void)status;
    sprite_t sprite = {
        .width = 10,
        .height = 20,
        .last_update.tv_sec = 0,
        .last_update.tv_usec = 0,
        .time_to_move = 0,
    };

    will_return(__wrap_gettimeofday, (time_t)1);
    will_return(__wrap_gettimeofday, (suseconds_t)0);
    expect_uint_value(__wrap_gettimeofday, tz, (uintptr_t)NULL);
    expect_function_call(__wrap_gettimeofday);

    physicMoveSprite(&sprite, 0xFF);
}

void
testPhysicMoveSpriteRight(void **status) {
    (void)status;
    sprite_t sprite = {
        .x = 100,
        .y = 0,
        .width = 10,
        .height = 20,
        .last_update.tv_sec = 0,
        .last_update.tv_usec = 0,
        .time_to_move = 0,
        .pixels_to_move = 10,
        .scaled_width = 20,
    };
    sprite_t old_sprite = sprite;

    will_return(__wrap_gettimeofday, (time_t)1);
    will_return(__wrap_gettimeofday, (suseconds_t)0);
    expect_uint_value(__wrap_gettimeofday, tz, (uintptr_t)NULL);
    expect_function_call(__wrap_gettimeofday);

    physicMoveSprite(&sprite, RIGHT);
    assert_int_equal(sprite.x, old_sprite.x + sprite.pixels_to_move);
    assert_int_equal(sprite.y, old_sprite.y);
}

void
testPhysicMoveSpriteRightMax(void **status) {
    (void)status;
    sprite_t sprite = {
        .y = 0,
        .width = 10,
        .height = 20,
        .last_update.tv_sec = 0,
        .last_update.tv_usec = 0,
        .time_to_move = 0,
        .pixels_to_move = 10,
        .scaled_width = 20,
    };
    sprite.x = WINDOW_WIDTH - sprite.pixels_to_move;

    will_return(__wrap_gettimeofday, (time_t)1);
    will_return(__wrap_gettimeofday, (suseconds_t)0);
    expect_uint_value(__wrap_gettimeofday, tz, (uintptr_t)NULL);
    expect_function_call(__wrap_gettimeofday);

    physicMoveSprite(&sprite, RIGHT);
    assert_int_equal(sprite.x, WINDOW_WIDTH - sprite.scaled_width);
}

void
testPhysicMoveSpriteLeft(void **status) {
    (void)status;
    sprite_t sprite = {
        .x = 100,
        .y = 0,
        .width = 10,
        .height = 20,
        .last_update.tv_sec = 0,
        .last_update.tv_usec = 0,
        .time_to_move = 0,
        .pixels_to_move = 10,
        .scaled_width = 20,
    };
    sprite_t old_sprite = sprite;

    will_return(__wrap_gettimeofday, (time_t)1);
    will_return(__wrap_gettimeofday, (suseconds_t)0);
    expect_uint_value(__wrap_gettimeofday, tz, (uintptr_t)NULL);
    expect_function_call(__wrap_gettimeofday);

    physicMoveSprite(&sprite, LEFT);
    assert_int_equal(sprite.x, old_sprite.x - sprite.pixels_to_move);
    assert_int_equal(sprite.y, old_sprite.y);
}

void
testPhysicMoveSpriteLeftMax(void **status) {
    (void)status;
    sprite_t sprite = {
        .x = 9,
        .y = 0,
        .width = 10,
        .height = 20,
        .last_update.tv_sec = 0,
        .last_update.tv_usec = 0,
        .time_to_move = 0,
        .pixels_to_move = 10,
    };

    will_return(__wrap_gettimeofday, (time_t)1);
    will_return(__wrap_gettimeofday, (suseconds_t)0);
    expect_uint_value(__wrap_gettimeofday, tz, (uintptr_t)NULL);
    expect_function_call(__wrap_gettimeofday);

    physicMoveSprite(&sprite, LEFT);
    assert_int_equal(sprite.x, 0);
}

void
testPhysicMoveSpriteUp(void **status) {
    (void)status;
    sprite_t sprite = {
        .x = 0,
        .y = 100,
        .width = 10,
        .height = 20,
        .last_update.tv_sec = 0,
        .last_update.tv_usec = 0,
        .time_to_move = 0,
        .pixels_to_move = 10,
        .scaled_width = 20,
    };
    sprite_t old_sprite = sprite;

    will_return(__wrap_gettimeofday, (time_t)1);
    will_return(__wrap_gettimeofday, (suseconds_t)0);
    expect_uint_value(__wrap_gettimeofday, tz, (uintptr_t)NULL);
    expect_function_call(__wrap_gettimeofday);

    physicMoveSprite(&sprite, UP);
    assert_int_equal(sprite.x, old_sprite.x);
    assert_int_equal(sprite.y, old_sprite.y + sprite.pixels_to_move);
}

void
testPhysicMoveSpriteUpMax(void **status) {
    (void)status;
    sprite_t sprite = {
        .x = 0,
        .width = 10,
        .height = 10,
        .last_update.tv_sec = 0,
        .last_update.tv_usec = 0,
        .time_to_move = 0,
        .pixels_to_move = 10,
    };
    sprite.y = WINDOW_HEIGHT - sprite.pixels_to_move;

    will_return(__wrap_gettimeofday, (time_t)1);
    will_return(__wrap_gettimeofday, (suseconds_t)0);
    expect_uint_value(__wrap_gettimeofday, tz, (uintptr_t)NULL);
    expect_function_call(__wrap_gettimeofday);

    physicMoveSprite(&sprite, UP);
    assert_int_equal(sprite.y, WINDOW_HEIGHT - sprite.scaled_width);
}

void
testPhysicMoveSpriteTooEarlyToMove(void **status) {
    (void)status;
    sprite_t sprite = {
        .x = 9,
        .y = 0,
        .width = 10,
        .height = 20,
        .last_update.tv_sec = 0,
        .last_update.tv_usec = 0,
        .time_to_move = 10000,
        .pixels_to_move = 10,
    };
    sprite_t old_sprite = sprite;

    will_return(__wrap_gettimeofday, (time_t)1);
    will_return(__wrap_gettimeofday, (suseconds_t)0);
    expect_uint_value(__wrap_gettimeofday, tz, (uintptr_t)NULL);
    expect_function_call(__wrap_gettimeofday);

    physicMoveSprite(&sprite, LEFT);
    assert_int_equal(sprite.x, old_sprite.x);
    assert_int_equal(sprite.y, old_sprite.y);
}

void
testPhysicCheckCeillingCollisionNullParameter(void **status) {
    (void)status;

    assert_false(physicCheckCeillingCollision(NULL));
}

void
testPhysicCheckCeillingCollisionTrue(void **status) {
    (void)status;
    sprite_t sprite = {
        .y = 0,
        .scaled_height = WINDOW_HEIGHT,
    };

    assert_true(physicCheckCeillingCollision(&sprite));
}

void
testPhysicCheckCeillingCollisionFalse(void **status) {
    (void)status;
    sprite_t sprite = {
        .y = 0,
        .scaled_height = WINDOW_HEIGHT - 1,
    };

    assert_false(physicCheckCeillingCollision(&sprite));

}
