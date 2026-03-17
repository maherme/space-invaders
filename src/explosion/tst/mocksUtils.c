/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Manuel Hernández Méndez
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
    function_called();
    return calloc(nelem, elsize);
}

void
__wrap_utilsFree(void **ptr)
{
    function_called();
    free(*ptr);
    *ptr = NULL;
}

bool
__wrap_utilsCheckTimeout(struct timespec time, long long timeout_ns)
{
    (void)time, (void)timeout_ns;
    function_called();
    return (bool)mock();
}
