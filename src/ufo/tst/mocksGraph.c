/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "graph.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

void
__wrap_graphCreateImage(sprite_t *sprite)
{
    (void)sprite;
    function_called();
}

void
__wrap_graphScaleImage(sprite_t *sprite)
{
    (void)sprite;
    function_called();
}

void
__wrap_graphDestroyImage(sprite_t *sprite)
{
    (void)sprite;
    function_called();
}

sprite_t dummy;

sprite_t *
__wrap_graphGetSprite(base_t *b)
{
    (void)b;
    function_called();
    return &dummy;
}

void
__wrap_graphPrintImage(const sprite_t *const sprite)
{
    (void)sprite;
    function_called();
}

void
__wrap_graphUpdateTimeSprite(sprite_t *sprite)
{
    (void)sprite;
    function_called();
}
