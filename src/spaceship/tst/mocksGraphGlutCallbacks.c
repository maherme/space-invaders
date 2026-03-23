/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "graphGlutCallbacks.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

int
__wrap_graphRegisterPrint(void *ctx)
{
    (void)ctx;
    function_called();
    return 0;
}

int
__wrap_graphUnregisterPrint(void *ctx)
{
    (void)ctx;
    function_called();
    return 0;
}
