/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "fonts.h"
#include "graph.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

#define FONTS_NUM 10
#define FONTS_WIDTH 4
#define FONTS_HEIGHT 6
#define FONTS_PIXELS_SPACE 1

static const char fontsImage[FONTS_NUM][FONTS_HEIGHT][FONTS_WIDTH][NUM_RGBA_CHANNELS] = {
    /* clang-format off */
    /* digit 0 */
    {{B, W, W, B},
     {W, B, B, W},
     {W, B, B, W},
     {W, B, B, W},
     {W, B, B, W},
     {B, W, W, B}},
    /* digit 1 */
    {{B, B, W, B},
     {B, W, W, B},
     {B, B, W, B},
     {B, B, W, B},
     {B, B, W, B},
     {B, B, W, B}},
    /* digit 2 */
    {{B, W, W, B},
     {W, B, B, W},
     {B, B, B, W},
     {B, B, W, B},
     {B, W, B, B},
     {W, W, W, W}},
    /* digit 3 */
    {{B, W, W, B},
     {W, B, B, W},
     {B, B, W, B},
     {B, B, B, W},
     {W, B, B, W},
     {B, W, W, B}},
    /* digit 4 */
    {{B, B, B, W},
     {B, B, W, W},
     {B, W, B, W},
     {W, B, B, W},
     {W, W, W, W},
     {B, B, B, W}},
    /* digit 5 */
    {{W, W, W, W}, 
     {W, B, B, B},
     {W, W, W, B},
     {B, B, B, W},
     {B, B, B, W},
     {W, W, W, B}},
    /* digit 6 */
    {{B, W, W, B},
     {W, B, B, B},
     {W, W, W, B},
     {W, B, B, W},
     {W, B, B, W},
     {B, W, W, B}},
    /* digit 7 */
    {{W, W, W, W},
     {B, B, B, W},
     {B, B, B, W},
     {B, B, B, W},
     {B, B, B, W},
     {B, B, B, W}},
    /* digit 8 */
    {{B, W, W, B},
     {W, B, B, W},
     {B, W, W, B},
     {W, B, B, W},
     {W, B, B, W},
     {B, W, W, B}},
    /* digit 9 */
    {{B, W, W, B},
     {W, B, B, W},
     {W, B, B, W},
     {B, W, W, W},
     {B, B, B, W},
     {B, W, W, B}}};
/* clang-format on */

static int
charToFontsIndex(char c)
{
    /* NOTE:
     * condition false && false is not possible
     */
    if (c >= '0' && c <= '9') /* GCOVR_EXCL_BR_WITHOUT_HIT: 1/4 */
    {
        return c - '0';
    }

    return -1;
}

static void
fontsSetInBuffer(const char *const text, sprite_t *const buffer)
{
    for (int i = 0; text[i]; i++)
    {
        int idx = charToFontsIndex(text[i]);
        if (idx >= 0)
        {
            buffer[i].image = (const char *)fontsImage[idx];
        }
    }
}

typedef struct fonts
{
    sprite_t *sprites;
    size_t size;
} fonts_handler_t;

fonts_handler_t *
fontsCreateFontsHandler(size_t size)
{
    fonts_handler_t *h = utilsCalloc(1, sizeof(*h));
    h->sprites = utilsCalloc(size, sizeof(sprite_t));
    h->size = size;
    return h;
}

void
fontsInitLayout(fonts_handler_t *h, int x, int y)
{
    for (size_t i = 0; i < h->size; i++)
    {
        h->sprites[i].x = x + i * (FONTS_WIDTH + FONTS_PIXELS_SPACE);
        h->sprites[i].y = y;
        h->sprites[i].width = FONTS_WIDTH;
        h->sprites[i].height = FONTS_HEIGHT;
        h->sprites[i].layer = LAYER_HUD;
    }
}

void
fontsRegisterSprites(fonts_handler_t *h)
{

    for (size_t i = 0; i < h->size; i++)
    {
        graphRegisterPrint(&h->sprites[i]);
    }
}

void
fontsDestroyFontsHandler(fonts_handler_t *fonts_handler)
{
    UTILS_FREE(fonts_handler->sprites);
    UTILS_FREE(fonts_handler);
}

void
fontsDraw(const char *const text, fonts_handler_t *fonts_handler)
{
    size_t len = strlen(text);
    if (fonts_handler->size < len)
    {
        return;
    }

    fontsSetInBuffer(text, fonts_handler->sprites);

    for (size_t i = 0; i < len; i++)
    {
        fonts_handler->sprites[i].visible = true;
        graphUpdateSprite(&fonts_handler->sprites[i]);
    }

    for (size_t i = len; i < fonts_handler->size; i++)
    {
        fonts_handler->sprites[i].visible = false;
    }
}

void
fontsDrawNumber(int num, fonts_handler_t *fonts_handler)
{
    char buf[fonts_handler->size + 1];
    snprintf(buf, sizeof(buf), "%0*d", (int)fonts_handler->size, num);
    fontsDraw(buf, fonts_handler);
}

#ifdef UNIT_TESTING
fonts_handler_t *
helperUT_fontsMakeFakeHandler(size_t size)
{
    fonts_handler_t *fonts_handler = calloc(1, sizeof(fonts_handler_t));
    fonts_handler->sprites = calloc(size, sizeof(sprite_t));
    fonts_handler->size = size;
    return fonts_handler;
}

sprite_t *
helperUT_fontsGetSpritesPointer(fonts_handler_t *h, int index)
{
    return &h->sprites[index];
}

fonts_sprite_info_t
helperUT_fontsGetSpriteInfo(fonts_handler_t *fonts_handler, int index)
{
    fonts_sprite_info_t info;

    info.x = fonts_handler->sprites[index].x;
    info.y = fonts_handler->sprites[index].y;
    info.width = fonts_handler->sprites[index].width;
    info.height = fonts_handler->sprites[index].height;
    info.layer = fonts_handler->sprites[index].layer;

    return info;
}

size_t
helperUT_fontsGetSize(fonts_handler_t *fonts_handler)
{
    return fonts_handler->size;
}

void
helperUT_fontsFreeHandler(fonts_handler_t *fonts_handler)
{
    free(fonts_handler->sprites);
    free(fonts_handler);
}
#endif /* UNIT_TESTING */
