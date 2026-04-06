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
    switch (type)
    {
        case EVENT_LIVES_DEPLETED:
            check_expected_ptr(data);
            break;
        case EVENT_LIVES_CHANGED:
            assert_non_null(data);
            unsigned int value = *(unsigned int *)data;
            check_expected_uint(value);
            break;
        default:
            break;
    }
    check_expected_uint(type);
    function_called();
}
