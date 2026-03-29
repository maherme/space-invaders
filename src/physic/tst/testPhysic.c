/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testPhysic.h"
#include "graph.h"
#include "physic.h"
#include "utils.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

void
testPhysicMoveSpriteFail(void **status)
{
    (void)status;

    physicMoveSprite(NULL, RIGHT);
}

static int
check_time_struct(CMockaValueData value, CMockaValueData check_data)
{
    struct timespec *expected = (struct timespec *)check_data.ptr;
    struct timespec *actual = (struct timespec *)value.ptr;

    return (actual->tv_sec == expected->tv_sec && actual->tv_nsec == expected->tv_nsec);
}

static struct timespec expected_time_struct;

static void
checkUtilsCheckTimeout(struct timespec actual, long long timeout, bool ret_mock)
{
    expected_time_struct.tv_sec = actual.tv_sec;
    expected_time_struct.tv_nsec = actual.tv_nsec;

    will_return(__wrap_utilsCheckTimeout, ret_mock);
    expect_check_data(__wrap_utilsCheckTimeout, time, check_time_struct, cast_ptr_to_cmocka_value(&expected_time_struct));
    expect_int_value(__wrap_utilsCheckTimeout, timeout_ns, timeout);
    expect_function_call(__wrap_utilsCheckTimeout);
}

static void
checkGraphGetSpriteCoordinates(sprite_t *sprite, int x1, int x2, int y1, int y2)
{
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)sprite);
    will_return(__wrap_graphGetSpriteCoordinates, x1); // x1
    will_return(__wrap_graphGetSpriteCoordinates, x2); // x2
    will_return(__wrap_graphGetSpriteCoordinates, y1); // y1
    will_return(__wrap_graphGetSpriteCoordinates, y2); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);
}

void
testPhysicMoveSpriteWrongDirection(void **status)
{
    (void)status;
    sprite_t sprite = {.width = 10, .height = 20, .last_update.tv_sec = 10, .last_update.tv_nsec = 20, .time_to_move = 0};

    checkUtilsCheckTimeout(sprite.last_update, sprite.time_to_move, true);
    checkGraphGetSpriteCoordinates(&sprite, 0, 10, 0, 20);

    physicMoveSprite(&sprite, 0xFF);
}

void
testPhysicMoveSpriteRight(void **status)
{
    (void)status;
    sprite_t sprite = {
        .x = 0,
        .pixels_to_move = 10,
        .max_movement.right = 31,
    };
    sprite_t old_sprite = sprite;

    checkUtilsCheckTimeout(sprite.last_update, sprite.time_to_move, true);
    checkGraphGetSpriteCoordinates(&sprite, sprite.x, sprite.x + sprite.width, 0, 0);
    expect_uint_value(__wrap_graphNextImageToPrint, sprite, (uintptr_t)&sprite);
    expect_function_call(__wrap_graphNextImageToPrint);
    expect_uint_value(__wrap_graphUpdateTimeSprite, sprite, (uintptr_t)&sprite);
    expect_function_call(__wrap_graphUpdateTimeSprite);

    physicMoveSprite(&sprite, RIGHT);
    assert_int_equal(sprite.x, old_sprite.x + sprite.pixels_to_move);
    assert_int_equal(sprite.y, old_sprite.y);
}

void
testPhysicMoveSpriteRightMax(void **status)
{
    (void)status;
    sprite_t sprite = {
        .pixels_to_move = 10,
    };
    sprite.x = WINDOW_WIDTH - sprite.width;
    sprite.max_movement.right = WINDOW_WIDTH;

    checkUtilsCheckTimeout(sprite.last_update, sprite.time_to_move, true);
    checkGraphGetSpriteCoordinates(&sprite, sprite.x, sprite.x + sprite.width, 0, 0);

    physicMoveSprite(&sprite, RIGHT);
    assert_int_equal(sprite.x, sprite.max_movement.right - sprite.width);
}

void
testPhysicMoveSpriteLeft(void **status)
{
    (void)status;
    sprite_t sprite = {
        .x = 11,
        .pixels_to_move = 10,
        .max_movement.left = 0,
    };
    sprite_t old_sprite = sprite;

    checkUtilsCheckTimeout(sprite.last_update, sprite.time_to_move, true);
    checkGraphGetSpriteCoordinates(&sprite, sprite.x, sprite.x + sprite.width, 0, 0);
    expect_uint_value(__wrap_graphNextImageToPrint, sprite, (uintptr_t)&sprite);
    expect_function_call(__wrap_graphNextImageToPrint);
    expect_uint_value(__wrap_graphUpdateTimeSprite, sprite, (uintptr_t)&sprite);
    expect_function_call(__wrap_graphUpdateTimeSprite);

    physicMoveSprite(&sprite, LEFT);
    assert_int_equal(sprite.x, old_sprite.x - sprite.pixels_to_move);
    assert_int_equal(sprite.y, old_sprite.y);
}

void
testPhysicMoveSpriteLeftMax(void **status)
{
    (void)status;
    sprite_t sprite = {
        .x = 9,
        .pixels_to_move = 10,
        .max_movement.left = 0,
    };

    checkUtilsCheckTimeout(sprite.last_update, sprite.time_to_move, true);
    checkGraphGetSpriteCoordinates(&sprite, sprite.x, sprite.x + sprite.width, 0, 0);

    physicMoveSprite(&sprite, LEFT);
    assert_int_equal(sprite.x, sprite.max_movement.left);
}

void
testPhysicMoveSpriteUp(void **status)
{
    (void)status;
    sprite_t sprite = {
        .y = 0,
        .pixels_to_move = 10,
    };
    sprite.max_movement.up = WINDOW_HEIGHT - sprite.height;
    sprite_t old_sprite = sprite;

    checkUtilsCheckTimeout(sprite.last_update, sprite.time_to_move, true);
    checkGraphGetSpriteCoordinates(&sprite, 0, 0, sprite.y, sprite.y + sprite.height);
    expect_uint_value(__wrap_graphNextImageToPrint, sprite, (uintptr_t)&sprite);
    expect_function_call(__wrap_graphNextImageToPrint);
    expect_uint_value(__wrap_graphUpdateTimeSprite, sprite, (uintptr_t)&sprite);
    expect_function_call(__wrap_graphUpdateTimeSprite);

    physicMoveSprite(&sprite, UP);
    assert_int_equal(sprite.x, old_sprite.x);
    assert_int_equal(sprite.y, old_sprite.y + sprite.pixels_to_move);
}

void
testPhysicMoveSpriteUpMax(void **status)
{
    (void)status;
    sprite_t sprite = {
        .pixels_to_move = 20,
    };
    sprite.y = WINDOW_HEIGHT - sprite.pixels_to_move;
    sprite.max_movement.up = WINDOW_HEIGHT;

    checkUtilsCheckTimeout(sprite.last_update, sprite.time_to_move, true);
    checkGraphGetSpriteCoordinates(&sprite, 0, 0, sprite.y, sprite.y + sprite.height);

    physicMoveSprite(&sprite, UP);
    assert_int_equal(sprite.y, sprite.max_movement.up - sprite.height);
}

void
testPhysicMoveSpriteDown(void **status)
{
    (void)status;
    sprite_t sprite = {
        .y = 100,
        .pixels_to_move = 10,
    };
    sprite.max_movement.down = 0;
    sprite_t old_sprite = sprite;

    checkUtilsCheckTimeout(sprite.last_update, sprite.time_to_move, true);
    checkGraphGetSpriteCoordinates(&sprite, 0, 0, sprite.y, sprite.y + sprite.height);
    expect_uint_value(__wrap_graphNextImageToPrint, sprite, (uintptr_t)&sprite);
    expect_function_call(__wrap_graphNextImageToPrint);
    expect_uint_value(__wrap_graphUpdateTimeSprite, sprite, (uintptr_t)&sprite);
    expect_function_call(__wrap_graphUpdateTimeSprite);

    physicMoveSprite(&sprite, DOWN);
    assert_int_equal(sprite.x, old_sprite.x);
    assert_int_equal(sprite.y, old_sprite.y - sprite.pixels_to_move);
}

void
testPhysicMoveSpriteDownMax(void **status)
{
    (void)status;
    sprite_t sprite = {
        .time_to_move = 0,
        .pixels_to_move = 10,
    };
    sprite.y = sprite.pixels_to_move;
    sprite.max_movement.down = 0;

    checkUtilsCheckTimeout(sprite.last_update, sprite.time_to_move, true);
    checkGraphGetSpriteCoordinates(&sprite, 0, 0, sprite.y, sprite.y + sprite.height);

    physicMoveSprite(&sprite, DOWN);
    assert_int_equal(sprite.y, 0);
}

void
testPhysicMoveSpriteTooEarlyToMove(void **status)
{
    (void)status;
    sprite_t sprite = {
        .x = 9,
        .y = 0,
        .pixels_to_move = 10,
    };
    sprite_t old_sprite = sprite;

    checkUtilsCheckTimeout(sprite.last_update, sprite.time_to_move, false);

    physicMoveSprite(&sprite, LEFT);
    assert_int_equal(sprite.x, old_sprite.x);
    assert_int_equal(sprite.y, old_sprite.y);
}

void
testPhysicCheckBorderCollisionNullParameter(void **status)
{
    (void)status;

    assert_false(physicCheckBorderCollision(NULL, RIGHT));
}

void
testPhysicCheckBorderCollisionUpTrue(void **status)
{
    (void)status;
    sprite_t sprite = {
        .max_movement.up = 10,
    };

    checkGraphGetSpriteCoordinates(&sprite, 0, 0, 0, sprite.max_movement.up);
    assert_true(physicCheckBorderCollision(&sprite, UP));
}

void
testPhysicCheckBorderCollisionDownTrue(void **status)
{
    (void)status;
    sprite_t sprite = {
        .max_movement.down = 10,
    };

    checkGraphGetSpriteCoordinates(&sprite, 0, 0, sprite.max_movement.down, 0);
    assert_true(physicCheckBorderCollision(&sprite, DOWN));
}

void
testPhysicCheckBorderCollisionRightTrue(void **status)
{
    (void)status;
    sprite_t sprite = {
        .max_movement.right = 10,
    };

    checkGraphGetSpriteCoordinates(&sprite, 0, sprite.max_movement.right, 0, 0);
    assert_true(physicCheckBorderCollision(&sprite, RIGHT));
}

void
testPhysicCheckBorderCollisionLeftTrue(void **status)
{
    (void)status;
    sprite_t sprite = {
        .max_movement.left = 10,
    };

    checkGraphGetSpriteCoordinates(&sprite, sprite.max_movement.left, 0, 0, 0);
    assert_true(physicCheckBorderCollision(&sprite, LEFT));
}

void
testPhysicCheckBorderCollisionInvalidDir(void **status)
{
    (void)status;
    sprite_t sprite = {
        .max_movement.left = 10,
    };

    checkGraphGetSpriteCoordinates(&sprite, 0, 0, 0, 0);
    assert_false(physicCheckBorderCollision(&sprite, INVALID_DIR));
}

void
testPhysicCheckSpriteBoxCollisionNullParameters(void **status)
{
    (void)status;
    sprite_t sprite1 = {0};
    sprite_t sprite2 = {0};

    assert_false(physicCheckSpritesBoxCollision(&sprite1, NULL));
    assert_false(physicCheckSpritesBoxCollision(NULL, &sprite2));
    assert_false(physicCheckSpritesBoxCollision(NULL, NULL));
}

void
testPhysicCheckSpriteBoxCollisionFalse(void **status)
{
    (void)status;
    sprite_t sprite1 = {0};
    sprite_t sprite2 = {0};

    /* sprites separate in x axi (right and left) */
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite1);
    will_return(__wrap_graphGetSpriteCoordinates, (int)0);  // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)10); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)0);  // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)10); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite2);
    will_return(__wrap_graphGetSpriteCoordinates, (int)20); // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)30); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)0);  // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)10); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);

    assert_false(physicCheckSpritesBoxCollision(&sprite1, &sprite2));

    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite1);
    will_return(__wrap_graphGetSpriteCoordinates, (int)20); // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)30); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)0);  // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)10); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite2);
    will_return(__wrap_graphGetSpriteCoordinates, (int)0);  // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)10); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)0);  // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)10); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);

    assert_false(physicCheckSpritesBoxCollision(&sprite1, &sprite2));

    /* sprites separate in y axi above and below */
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite1);
    will_return(__wrap_graphGetSpriteCoordinates, (int)0);  // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)10); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)0);  // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)10); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite2);
    will_return(__wrap_graphGetSpriteCoordinates, (int)0);  // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)10); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)20); // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)30); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);

    assert_false(physicCheckSpritesBoxCollision(&sprite1, &sprite2));

    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite1);
    will_return(__wrap_graphGetSpriteCoordinates, (int)0);  // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)10); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)20); // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)30); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite2);
    will_return(__wrap_graphGetSpriteCoordinates, (int)0);  // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)10); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)0);  // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)10); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);

    assert_false(physicCheckSpritesBoxCollision(&sprite1, &sprite2));

    /* sprites separate in x and y axi */
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite1);
    will_return(__wrap_graphGetSpriteCoordinates, (int)0);  // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)10); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)0);  // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)10); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite2);
    will_return(__wrap_graphGetSpriteCoordinates, (int)20); // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)30); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)20); // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)30); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);

    assert_false(physicCheckSpritesBoxCollision(&sprite1, &sprite2));
}

void
testPhysicCheckSpriteBoxCollisionTrue(void **status)
{
    (void)status;
    sprite_t sprite1 = {0};
    sprite_t sprite2 = {0};

    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite1);
    will_return(__wrap_graphGetSpriteCoordinates, (int)0);  // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)10); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)0);  // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)10); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite2);
    will_return(__wrap_graphGetSpriteCoordinates, (int)5);  // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)15); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)5);  // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)15); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);

    assert_true(physicCheckSpritesBoxCollision(&sprite1, &sprite2));
}

void
testPhysicCheckSpritePixelCollisionNullParameters(void **status)
{
    (void)status;
    sprite_t sprite1 = {0};
    sprite_t sprite2 = {0};

    assert_false(physicCheckSpritesPixelCollision(&sprite1, NULL));
    assert_false(physicCheckSpritesPixelCollision(NULL, &sprite2));
    assert_false(physicCheckSpritesPixelCollision(NULL, NULL));
}

void
testPhysicCheckSpritePixelCollisionCheckBoxesFalse(void **status)
{
    (void)status;
    sprite_t sprite1 = {0};
    sprite_t sprite2 = {0};

    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite1);
    will_return(__wrap_graphGetSpriteCoordinates, (int)0); // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)1); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)0); // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)1); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite2);
    will_return(__wrap_graphGetSpriteCoordinates, (int)2); // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)3); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)0); // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)1); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);

    assert_false(physicCheckSpritesPixelCollision(&sprite1, &sprite2));
}

void
testPhysicCheckSpritePixelCollisionJustBoder(void **status)
{
    (void)status;
    const char image1[2][2][NUM_RGBA_CHANNELS] = {
        {B, B},
        {W, B},
    };
    sprite_t sprite1 = {
        .image = (const char *)image1,
        .width = 2,
        .height = 2,
    };
    const char image2[4][4][NUM_RGBA_CHANNELS] = {
        {B, B, B, B},
        {B, B, W, B},
        {B, B, B, B},
        {B, B, B, B},
    };
    sprite_t sprite2 = {
        .image = (const char *)image2,
        .width = 4,
        .height = 4,
    };

    /*
     * Test branch if (overlap_left >= overlap_right || overlap_bottom >= overlap_top)
     * true || false
     */
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite1);
    will_return(__wrap_graphGetSpriteCoordinates, (int)0); // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)2); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)0); // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)2); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite2);
    will_return(__wrap_graphGetSpriteCoordinates, (int)2); // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)6); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)0); // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)4); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);

    assert_false(physicCheckSpritesPixelCollision(&sprite1, &sprite2));

    /*
     * Test branch if (overlap_left >= overlap_right || overlap_bottom >= overlap_top)
     * false || true
     */
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite1);
    will_return(__wrap_graphGetSpriteCoordinates, (int)0); // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)2); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)0); // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)2); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite2);
    will_return(__wrap_graphGetSpriteCoordinates, (int)0); // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)4); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)2); // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)6); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);

    assert_false(physicCheckSpritesPixelCollision(&sprite1, &sprite2));
}

void
testPhysicCheckSpritePixelCollisionFalseCheckBoxesTrue(void **status)
{
    (void)status;
    const char image1[2][2][NUM_RGBA_CHANNELS] = {
        {B, B},
        {W, B},
    };
    sprite_t sprite1 = {
        .image = (const char *)image1,
        .width = 2,
        .height = 2,
    };
    const char image2[4][4][NUM_RGBA_CHANNELS] = {
        {B, B, W, B},
        {B, B, B, B},
        {B, B, B, B},
        {B, B, B, B},
    };
    sprite_t sprite2 = {
        .image = (const char *)image2,
        .width = 4,
        .height = 4,
    };

    /*
     * Test branch if (overlap_left >= overlap_right || overlap_bottom >= overlap_top)
     * false || false
     */
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite1);
    will_return(__wrap_graphGetSpriteCoordinates, (int)2); // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)4); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)2); // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)4); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite2);
    will_return(__wrap_graphGetSpriteCoordinates, (int)0); // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)4); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)0); // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)4); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);

    assert_false(physicCheckSpritesPixelCollision(&sprite1, &sprite2));
}

void
testPhysicCheckSpritePixelCollisionTrueCheckBoxesTrue(void **status)
{
    (void)status;
    const char image1[2][2][NUM_RGBA_CHANNELS] = {
        {W, B},
        {B, B},
    };
    sprite_t sprite1 = {
        .image = (const char *)image1,
        .width = 2,
        .height = 2,
    };
    const char image2[4][4][NUM_RGBA_CHANNELS] = {
        {B, B, W, B},
        {B, B, B, B},
        {B, B, B, B},
        {B, B, B, B},
    };
    sprite_t sprite2 = {
        .image = (const char *)image2,
        .width = 4,
        .height = 4,
    };

    /*
     * Test branch if (overlap_left >= overlap_right || overlap_bottom >= overlap_top)
     * false || false
     */
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite1);
    will_return(__wrap_graphGetSpriteCoordinates, (int)2); // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)4); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)2); // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)4); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite2);
    will_return(__wrap_graphGetSpriteCoordinates, (int)0); // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)4); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)0); // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)4); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);

    assert_true(physicCheckSpritesPixelCollision(&sprite1, &sprite2));
}

void
testPhysicMakeFootprintSpriteNoOverlap(void **status)
{
    (void)status;
    const char image1[2][2][NUM_RGBA_CHANNELS] = {
        {B, B},
        {W, B},
    };
    sprite_t sprite1 = {
        .image = (const char *)image1,
        .width = 2,
        .height = 2,
    };
    const char image2[4][4][NUM_RGBA_CHANNELS] = {
        {B, B, B, B},
        {B, B, W, B},
        {B, B, B, B},
        {B, B, B, B},
    };
    sprite_t sprite2 = {
        .image = (const char *)image2,
        .width = 4,
        .height = 4,
    };

    /*
     * Test branch if (overlap_left >= overlap_right || overlap_bottom >= overlap_top)
     * true || true
     */
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite1);
    will_return(__wrap_graphGetSpriteCoordinates, (int)0); // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)2); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)0); // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)2); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite2);
    will_return(__wrap_graphGetSpriteCoordinates, (int)2); // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)6); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)2); // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)6); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);

    physicMakeFootprintSprite(&sprite1, &sprite2);
}

void
testPhysicMakeFootprintSpriteNoOverlapJustBorder(void **status)
{
    (void)status;
    const char image1[2][2][NUM_RGBA_CHANNELS] = {
        {B, B},
        {W, B},
    };
    sprite_t sprite1 = {
        .image = (const char *)image1,
        .width = 2,
        .height = 2,
    };
    const char image2[4][4][NUM_RGBA_CHANNELS] = {
        {B, B, B, B},
        {B, B, W, B},
        {B, B, B, B},
        {B, B, B, B},
    };
    sprite_t sprite2 = {
        .image = (const char *)image2,
        .width = 4,
        .height = 4,
    };

    /*
     * Test branch if (overlap_left >= overlap_right || overlap_bottom >= overlap_top)
     * false || true
     */
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite1);
    will_return(__wrap_graphGetSpriteCoordinates, (int)0); // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)2); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)0); // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)2); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite2);
    will_return(__wrap_graphGetSpriteCoordinates, (int)0); // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)4); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)2); // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)6); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);

    physicMakeFootprintSprite(&sprite1, &sprite2);
}

void
testPhysicMakeFootprintSpriteOverlapPixelsMatch(void **status)
{
    (void)status;
    const char image1[2][2][NUM_RGBA_CHANNELS] = {
        {W, B},
        {B, B},
    };
    sprite_t sprite1 = {
        .image = (const char *)image1,
        .width = 2,
        .height = 2,
    };
    const char image2[4][4][NUM_RGBA_CHANNELS] = {
        {B, B, W, B},
        {B, B, B, B},
        {B, B, B, B},
        {B, B, B, B},
    };
    sprite_t sprite2 = {
        .image = (const char *)image2,
        .width = 4,
        .height = 4,
    };

    /*
     * Test branch if (overlap_left >= overlap_right || overlap_bottom >= overlap_top)
     * false || false
     */
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite1);
    will_return(__wrap_graphGetSpriteCoordinates, (int)2); // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)4); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)2); // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)4); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite2);
    will_return(__wrap_graphGetSpriteCoordinates, (int)0); // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)4); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)0); // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)4); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);

    physicMakeFootprintSprite(&sprite1, &sprite2);
}

void
testPhysicMakeFootprintSpriteOverlapPixelsUnmatch(void **status)
{
    (void)status;
    const char image1[2][2][NUM_RGBA_CHANNELS] = {
        {B, W},
        {B, B},
    };
    sprite_t sprite1 = {
        .image = (const char *)image1,
        .width = 2,
        .height = 2,
    };
    const char image2[4][4][NUM_RGBA_CHANNELS] = {
        {B, B, W, B},
        {B, B, B, B},
        {B, B, B, B},
        {B, B, B, B},
    };
    sprite_t sprite2 = {
        .image = (const char *)image2,
        .width = 4,
        .height = 4,
    };

    /*
     * Test branch if (overlap_left >= overlap_right || overlap_bottom >= overlap_top)
     * false || false
     */
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite1);
    will_return(__wrap_graphGetSpriteCoordinates, (int)2); // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)4); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)2); // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)4); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);
    expect_uint_value(__wrap_graphGetSpriteCoordinates, sprite, (uintptr_t)&sprite2);
    will_return(__wrap_graphGetSpriteCoordinates, (int)0); // x1
    will_return(__wrap_graphGetSpriteCoordinates, (int)4); // x2
    will_return(__wrap_graphGetSpriteCoordinates, (int)0); // y1
    will_return(__wrap_graphGetSpriteCoordinates, (int)4); // y2
    expect_function_call(__wrap_graphGetSpriteCoordinates);

    physicMakeFootprintSprite(&sprite1, &sprite2);
}
