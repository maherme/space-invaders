/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "events.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

void
__wrap_eventEmit(event_type_t type, void *data)
{
    unsigned int value = *(unsigned int *)data;

    check_expected_uint(type);
    check_expected_uint(value);
    function_called();
}
