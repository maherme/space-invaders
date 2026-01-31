/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "testGraphGlut.h"
#include "testGraphGlutCallbacks.h"

int
main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup(testGraphInitGlut, setup),
        cmocka_unit_test_setup(testGraphRegisterPrintFailNullParameter, setup),
        cmocka_unit_test_setup(testGraphRegisterPrintFailMaxCallbacks, setup),
        cmocka_unit_test_setup(testGraphRegisterPrintSuccess, setup),
        cmocka_unit_test_setup(testGraphUnregisterPrintFailNullParameter, setup),
        cmocka_unit_test_setup(testGraphUnregisterPrintFailMaxCallbacks, setup),
        cmocka_unit_test_setup(testGraphUnregisterPrintSuccess, setup),
        cmocka_unit_test_setup(testGraphGlutReshape, setup),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
