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
#include <stdlib.h>

void *
__wrap_utilsCalloc(size_t nelem, size_t elsize)
{
    (void)nelem, (void)elsize;
    function_called();
    return calloc(nelem, elsize);
}

void
__wrap_utilsFree(void **ptr)
{
    check_expected_ptr(ptr);
    function_called();
}
