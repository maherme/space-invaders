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
#include "testUtils.h"

int
main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(testUtilsCallocFail),
        cmocka_unit_test(testUtilsCallocSuccess),
        cmocka_unit_test(testUtilsFreeFail),
        cmocka_unit_test(testUtilsFreeSuccess),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
