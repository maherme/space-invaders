/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testPhysic.h"
#include <stdio.h>

void
testPhysicMoveSpriteFail(void **status) {
    (void)status;

    physicMoveSprite(NULL, RIGHT);
}

static int
check_time_struct(CMockaValueData value, CMockaValueData check_data) {
    struct timespec *expected = (struct timespec *)check_data.ptr;
    struct timespec *actual = (struct timespec *)value.ptr;

    return(actual->tv_sec == expected->tv_sec &&
           actual->tv_nsec == expected->tv_nsec);
}

static struct timespec expected_time_struct;

static void
checkUtilsCheckTimeout(struct timespec actual, long long timeout, bool ret_mock) {
    expected_time_struct.tv_sec = actual.tv_sec;
    expected_time_struct.tv_nsec = actual.tv_nsec;
    
    will_return(__wrap_utilsCheckTimeout, ret_mock);
    expect_check_data(__wrap_utilsCheckTimeout, time,
                      check_time_struct, cast_ptr_to_cmocka_value(&expected_time_struct));
    expect_int_value(__wrap_utilsCheckTimeout, timeout_ns, timeout);
    expect_function_call(__wrap_utilsCheckTimeout);
}

void
testPhysicMoveSpriteWrongDirection(void **status) {
    (void)status;
    sprite_t sprite = {
        .width = 10,
        .height = 20,
        .last_update.tv_sec = 10,
        .last_update.tv_nsec = 20,
        .time_to_move = 0
    };
    
    checkUtilsCheckTimeout(sprite.last_update, sprite.time_to_move, true);
    expect_uint_value(__wrap_graphUpdateTimeSprite, sprite, (uintptr_t)&sprite);
    expect_function_call(__wrap_graphUpdateTimeSprite);

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
        .last_update.tv_sec = 99,
        .last_update.tv_nsec = 99 * NS_PER_MS,
        .time_to_move = 0,
        .pixels_to_move = 10,
        .scaled_width = 20,
    };
    sprite_t old_sprite = sprite;

    checkUtilsCheckTimeout(sprite.last_update, sprite.time_to_move, true);
    expect_uint_value(__wrap_graphUpdateTimeSprite, sprite, (uintptr_t)&sprite);
    expect_function_call(__wrap_graphUpdateTimeSprite);

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
        .last_update.tv_nsec = 0,
        .time_to_move = 0,
        .pixels_to_move = 10,
        .scaled_width = 20,
    };
    sprite.x = WINDOW_WIDTH - sprite.pixels_to_move;

    checkUtilsCheckTimeout(sprite.last_update, sprite.time_to_move, true);

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
        .last_update.tv_nsec = 0,
        .time_to_move = 0,
        .pixels_to_move = 10,
        .scaled_width = 20,
    };
    sprite_t old_sprite = sprite;

    checkUtilsCheckTimeout(sprite.last_update, sprite.time_to_move, true);
    expect_uint_value(__wrap_graphUpdateTimeSprite, sprite, (uintptr_t)&sprite);
    expect_function_call(__wrap_graphUpdateTimeSprite);

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
        .last_update.tv_nsec = 0,
        .time_to_move = 0,
        .pixels_to_move = 10,
    };

    checkUtilsCheckTimeout(sprite.last_update, sprite.time_to_move, true);

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
        .last_update.tv_nsec = 0,
        .time_to_move = 0,
        .pixels_to_move = 10,
        .scaled_width = 20,
    };
    sprite_t old_sprite = sprite;

    checkUtilsCheckTimeout(sprite.last_update, sprite.time_to_move, true);
    expect_uint_value(__wrap_graphUpdateTimeSprite, sprite, (uintptr_t)&sprite);
    expect_function_call(__wrap_graphUpdateTimeSprite);

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
        .last_update.tv_nsec = 0,
        .time_to_move = 0,
        .pixels_to_move = 10,
    };
    sprite.y = WINDOW_HEIGHT - sprite.pixels_to_move;

    checkUtilsCheckTimeout(sprite.last_update, sprite.time_to_move, true);

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
        .last_update.tv_nsec = 0,
        .time_to_move = 0,
        .pixels_to_move = 10,
    };
    sprite_t old_sprite = sprite;

    checkUtilsCheckTimeout(sprite.last_update, sprite.time_to_move, false);

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
