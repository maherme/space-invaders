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

sprite_t *
__wrap_graphGetSprite(base_t *b)
{
    if (!b)
    {
        return NULL;
    }
    return &b->sprite;
}

void
__wrap_graphUpdateImageToPrint(sprite_t *sprite)
{
    (void)sprite;
    function_called();
}
