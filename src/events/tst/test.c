/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testEvents.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

int
main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup(testEventRegister, setup),
        cmocka_unit_test_setup(testEventAlreadyRegistered, setup),
        cmocka_unit_test_setup(testEventRegisterInvalidType, setup),
        cmocka_unit_test_setup(testEventEmit, setup),
        cmocka_unit_test_setup(testEventEmitNotRegistered, setup),
        cmocka_unit_test_setup(testEventEmitInvalidType, setup),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
