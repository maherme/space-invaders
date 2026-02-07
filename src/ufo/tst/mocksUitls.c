/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "utils.h"

void *
__wrap_utilsCalloc(size_t nelem, size_t elsize) {
    (void)nelem, (void)elsize;
    function_called();
    return calloc(nelem, elsize);
}

bool
__wrap_utilsCheckTimeout(struct timespec time, long long timeout_ns) {
    (void)time, (void)timeout_ns;
    function_called();
    return (bool)mock();
}
