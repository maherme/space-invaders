/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testEngine.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

int
main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup(testEngineRegisterFailNullParameter, setup),
        cmocka_unit_test_setup(testEngineRegisterFailMaxCallbacks, setup),
        cmocka_unit_test_setup(testEngineRegisterSuccess, setup),
        cmocka_unit_test_setup(testEngineUnregisterFailNullParameter, setup),
        cmocka_unit_test_setup(testEngineUnregisterNoCallbackFound, setup),
        cmocka_unit_test_setup(testEngineUnregisterSuccess, setup),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
