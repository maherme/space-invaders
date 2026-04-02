/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testFonts.h"
#include "fonts.h"
#include "graphGlutCallbacks.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

void
testFontsCreateFontsHandler(void **status)
{
    (void)status;
    size_t expected_size = 10;

    expect_function_call(__wrap_utilsCalloc);
    expect_function_call(__wrap_utilsCalloc);

    fonts_handler_t *fonts_handler = fontsCreateFontsHandler(expected_size);
    assert_uint_equal(expected_size, helperUT_fontsGetSize(fonts_handler));

    helperUT_fontsFreeHandler(fonts_handler);
}

void
testFontsInitLayout(void **status)
{
    (void)status;
    size_t expected_size = 2;
    int expected_x = 1, expected_y = 2;
    int expected_fonts_width = 4;
    int expected_fonts_height = 6;
    int expected_pixel_space = 1;

    fonts_handler_t *fonts_handler = helperUT_fontsMakeFakeHandler(expected_size);

    fontsInitLayout(fonts_handler, expected_x, expected_y);

    for (size_t i = 0; i < expected_size; i++)
    {
        fonts_sprite_info_t sprite = helperUT_fontsGetSpriteInfo(fonts_handler, i);
        assert_int_equal(sprite.x, expected_x + i * (expected_fonts_width + expected_pixel_space));
        assert_int_equal(sprite.y, expected_y);
        assert_int_equal(sprite.width, expected_fonts_width);
        assert_int_equal(sprite.height, expected_fonts_height);
        assert_int_equal(sprite.layer, LAYER_HUD);
    }

    helperUT_fontsFreeHandler(fonts_handler);
}

void
testFontsRegisterSprites(void **status)
{
    (void)status;
    size_t expected_size = 2;

    fonts_handler_t *fonts_handler = helperUT_fontsMakeFakeHandler(expected_size);

    for (size_t i = 0; i < expected_size; i++)
    {
        sprite_t *sprite_ptr = helperUT_fontsGetSpritesPointer(fonts_handler, i);
        expect_uint_value(__wrap_graphRegisterPrint, sprite, (uintptr_t)sprite_ptr);
        expect_function_call(__wrap_graphRegisterPrint);
    }

    fontsRegisterSprites(fonts_handler);

    helperUT_fontsFreeHandler(fonts_handler);
}

void
testFontsDestroyFontsHandler(void **status)
{
    (void)status;
    size_t expected_size = 2;
    fonts_handler_t *fonts_handler = helperUT_fontsMakeFakeHandler(expected_size);

    fontsDestroyFontsHandler(fonts_handler);

    /* No asserts, use ASAN */
}

void
testFontsDraw(void **status)
{
    (void)status;
    fonts_handler_t *fonts_handler = helperUT_fontsMakeFakeHandler(1);

    sprite_t *expected_sprite = helperUT_fontsGetSpritesPointer(fonts_handler, 0);
    expect_uint_value(__wrap_graphUpdateSprite, sprite, (uintptr_t)expected_sprite);
    expect_function_call(__wrap_graphUpdateSprite);

    fontsDraw("a", fonts_handler);

    helperUT_fontsFreeHandler(fonts_handler);
}

void
testFontsDrawBiggerBuffer(void **status)
{
    (void)status;
    size_t expected_size = 2;
    fonts_handler_t *fonts_handler = helperUT_fontsMakeFakeHandler(expected_size);

    sprite_t *expected_sprite = helperUT_fontsGetSpritesPointer(fonts_handler, 0);
    expect_uint_value(__wrap_graphUpdateSprite, sprite, (uintptr_t)expected_sprite);
    expect_function_call(__wrap_graphUpdateSprite);

    fontsDraw("a", fonts_handler);

    helperUT_fontsFreeHandler(fonts_handler);
}

void
testFontsDrawSmallerBuffer(void **status)
{
    (void)status;
    size_t expected_size = 1;
    fonts_handler_t *fonts_handler = helperUT_fontsMakeFakeHandler(expected_size);

    fontsDraw("aa", fonts_handler);

    helperUT_fontsFreeHandler(fonts_handler);
}

void
testFontsDrawNumber(void **status)
{
    (void)status;
    fonts_handler_t *fonts_handler = helperUT_fontsMakeFakeHandler(1);

    sprite_t *expected_sprite = helperUT_fontsGetSpritesPointer(fonts_handler, 0);
    expect_uint_value(__wrap_graphUpdateSprite, sprite, (uintptr_t)expected_sprite);
    expect_function_call(__wrap_graphUpdateSprite);

    fontsDrawNumber(0, fonts_handler);

    helperUT_fontsFreeHandler(fonts_handler);
}
