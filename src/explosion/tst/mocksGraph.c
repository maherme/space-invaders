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
__wrap_graphNextImageToPrint(sprite_t *sprite)
{
    (void)sprite;
    function_called();
}
