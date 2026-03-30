/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testGraphGlutCallbacks.h"
#include "graph.h"
#include "graphGlutCallbacks.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

void
__wrap_glClear(GLbitfield mask)
{
    check_expected_uint(mask);
    function_called();
}

void
__wrap_glutSwapBuffers(void)
{
    function_called();
}

void
__wrap_glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
    check_expected_int(x);
    check_expected_int(y);
    check_expected_int(width);
    check_expected_int(height);
    function_called();
}

void
__wrap_glMatrixMode(GLenum mode)
{
    check_expected_uint(mode);
    function_called();
}

void
__wrap_glLoadIdentity(void)
{
    function_called();
}

void
__wrap_gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
{
    check_expected_double(left);
    check_expected_double(right);
    check_expected_double(bottom);
    check_expected_double(top);
    function_called();
}

void
__wrap_graphPrintImage(const sprite_t *const sprite)
{
    check_expected_ptr(sprite);
    function_called();
}

void
__wrap_graphPrintGameBorder(void)
{
    function_called();
}

int
setup(void **state)
{
    (void)state;
    graphRegisterPrintInit();
    helperUT_graphGlutResetRegisteredSprites();
    return 0;
}

int
teardown(void **state)
{
    (void)state;
    helperUT_graphGlutResetRegisteredSprites();
    return 0;
}

void
testGraphRegisterPrintFailNullParameter(void **status)
{
    (void)status;

    int result = graphRegisterPrint(NULL);
    assert_int_equal(result, -1);
}

static void
register_sprites(sprite_t **sprite, int n)
{
    for (int i = 0; i < n; i++)
    {
        expect_function_call(__wrap_utilsCalloc);
        expect_function_call(__wrap_graphCreateImage);
        int result = graphRegisterPrint(sprite[i]);
        assert_int_equal(result, 0);
    }
}

void
testGraphRegisterPrintSuccess(void **status)
{
    (void)status;
    sprite_t sprite = {0};
    sprite.layer = LAYER_BACKGROUND;
    sprite_t *expected_sprites[] = {&sprite};

    register_sprites(expected_sprites, ARRAY_SIZE(expected_sprites));
    assert_true(helperUT_graphGlutSpriteIsRegistered(expected_sprites[0]));
}

void
testGraphUnregisterPrintFailNullParameter(void **status)
{
    (void)status;

    int result = graphUnregisterPrint(NULL);
    assert_int_equal(result, -1);
}

void
testGraphUnregisterPrintNoCallbacksFound(void **status)
{
    (void)status;
    sprite_t sprite = {0};
    sprite.layer = LAYER_BACKGROUND;

    int result = graphUnregisterPrint(&sprite);
    assert_int_equal(result, 0);
    assert_false(helperUT_graphGlutSpriteIsRegistered(&sprite));
}

void
testGraphUnregisterPrintSuccessOneCallback(void **status)
{
    (void)status;
    sprite_t sprite = {0};
    sprite.layer = LAYER_BACKGROUND;
    sprite_t *expected_sprites[] = {&sprite};

    register_sprites(expected_sprites, ARRAY_SIZE(expected_sprites));
    assert_true(helperUT_graphGlutSpriteIsRegistered(expected_sprites[0]));

    expect_function_call(__wrap_graphDestroyImage);
    expect_function_call(__wrap_utilsFree);
    int result = graphUnregisterPrint(expected_sprites[0]);
    assert_int_equal(result, 1);
    assert_false(helperUT_graphGlutSpriteIsRegistered(expected_sprites[0]));
}

void
testGraphUnregisterPrintSuccessLastCallback(void **status)
{
    (void)status;
    sprite_t sprite1 = {0}, sprite2 = {0};
    sprite1.layer = LAYER_BACKGROUND;
    sprite2.layer = LAYER_BACKGROUND;
    sprite_t *expected_sprites[] = {&sprite1, &sprite2};

    register_sprites(expected_sprites, ARRAY_SIZE(expected_sprites));
    assert_true(helperUT_graphGlutSpriteIsRegistered(expected_sprites[0]));
    assert_true(helperUT_graphGlutSpriteIsRegistered(expected_sprites[1]));

    expect_function_call(__wrap_graphDestroyImage);
    expect_function_call(__wrap_utilsFree);
    int result = graphUnregisterPrint(expected_sprites[1]);
    assert_int_equal(result, 1);
    assert_true(helperUT_graphGlutSpriteIsRegistered(expected_sprites[0]));
    assert_false(helperUT_graphGlutSpriteIsRegistered(expected_sprites[1]));
}

void
testGraphUnregisterPrintSuccessMiddleCallback(void **status)
{
    (void)status;
    sprite_t sprite1 = {0}, sprite2 = {0}, sprite3 = {0};
    sprite1.layer = LAYER_BACKGROUND;
    sprite2.layer = LAYER_BACKGROUND;
    sprite3.layer = LAYER_BACKGROUND;
    sprite_t *expected_sprites[] = {&sprite1, &sprite2, &sprite3};

    register_sprites(expected_sprites, ARRAY_SIZE(expected_sprites));
    assert_true(helperUT_graphGlutSpriteIsRegistered(expected_sprites[0]));
    assert_true(helperUT_graphGlutSpriteIsRegistered(expected_sprites[1]));
    assert_true(helperUT_graphGlutSpriteIsRegistered(expected_sprites[2]));

    expect_function_call(__wrap_graphDestroyImage);
    expect_function_call(__wrap_utilsFree);

    int result = graphUnregisterPrint(expected_sprites[1]);
    assert_int_equal(result, 1);
    assert_true(helperUT_graphGlutSpriteIsRegistered(expected_sprites[0]));
    assert_false(helperUT_graphGlutSpriteIsRegistered(expected_sprites[1]));
    assert_true(helperUT_graphGlutSpriteIsRegistered(expected_sprites[2]));
}

void
testGraphGlutDisplay(void **status)
{
    (void)status;
    sprite_t sprite = {0};
    sprite.layer = LAYER_BACKGROUND;
    sprite_t *expected_sprites[] = {&sprite};

    expect_function_call(__wrap_utilsCalloc);
    helperUT_graphGlutInjectSprite(expected_sprites[0]);

    expect_uint_value(__wrap_glClear, mask, GL_COLOR_BUFFER_BIT);
    expect_function_call(__wrap_glClear);
    expect_uint_value(__wrap_graphPrintImage, sprite, (uintptr_t)expected_sprites[0]);
    expect_function_call(__wrap_graphPrintImage);
    expect_function_call(__wrap_graphPrintGameBorder);
    expect_function_call(__wrap_glutSwapBuffers);

    graphGlutDisplay();
}

void
testGraphGlutReshapeScaleLowerThanOne(void **status)
{
    (void)status;
    int width = WINDOW_WIDTH / 2;
    int height = WINDOW_HEIGHT / 2;

    expect_int_value(__wrap_glViewport, x, (width - WINDOW_WIDTH) / 2);
    expect_int_value(__wrap_glViewport, y, (height - WINDOW_HEIGHT) / 2);
    expect_int_value(__wrap_glViewport, width, WINDOW_WIDTH);
    expect_int_value(__wrap_glViewport, height, WINDOW_HEIGHT);
    expect_function_call(__wrap_glViewport);

    expect_uint_value(__wrap_glMatrixMode, mode, GL_PROJECTION);
    expect_function_call(__wrap_glMatrixMode);

    expect_function_call(__wrap_glLoadIdentity);

    expect_double(__wrap_gluOrtho2D, left, 0, 0);
    expect_double(__wrap_gluOrtho2D, right, WINDOW_WIDTH, 0);
    expect_double(__wrap_gluOrtho2D, bottom, 0, 0);
    expect_double(__wrap_gluOrtho2D, top, WINDOW_HEIGHT, 0);
    expect_function_call(__wrap_gluOrtho2D);

    expect_uint_value(__wrap_glMatrixMode, mode, GL_MODELVIEW);
    expect_function_call(__wrap_glMatrixMode);

    expect_function_call(__wrap_glLoadIdentity);

    graphGlutReshape(width, height);
}

void
testGraphGlutReshapeScaleHigherThanOne(void **status)
{
    (void)status;
    int scale = 2;

    expect_int_value(__wrap_glViewport, x, 0);
    expect_int_value(__wrap_glViewport, y, 0);
    expect_int_value(__wrap_glViewport, width, WINDOW_WIDTH * scale);
    expect_int_value(__wrap_glViewport, height, WINDOW_HEIGHT * scale);
    expect_function_call(__wrap_glViewport);

    expect_uint_value(__wrap_glMatrixMode, mode, GL_PROJECTION);
    expect_function_call(__wrap_glMatrixMode);

    expect_function_call(__wrap_glLoadIdentity);

    expect_double(__wrap_gluOrtho2D, left, 0, 0);
    expect_double(__wrap_gluOrtho2D, right, WINDOW_WIDTH, 0);
    expect_double(__wrap_gluOrtho2D, bottom, 0, 0);
    expect_double(__wrap_gluOrtho2D, top, WINDOW_HEIGHT, 0);
    expect_function_call(__wrap_gluOrtho2D);

    expect_uint_value(__wrap_glMatrixMode, mode, GL_MODELVIEW);
    expect_function_call(__wrap_glMatrixMode);

    expect_function_call(__wrap_glLoadIdentity);

    graphGlutReshape(WINDOW_WIDTH * scale, WINDOW_HEIGHT * scale);
}
