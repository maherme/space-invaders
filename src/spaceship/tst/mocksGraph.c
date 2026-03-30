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
