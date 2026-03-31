/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

struct sprite;
typedef struct sprite sprite_t;

int
__wrap_graphRegisterPrint(sprite_t *sprite)
{
    check_expected_ptr(sprite);
    function_called();
    return 0;
}

int
__wrap_graphUnregisterPrint(sprite_t *sprite)
{
    check_expected_ptr(sprite);
    function_called();
    return 0;
}
