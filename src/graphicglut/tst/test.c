/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testGraphGlut.h"
#include "testGraphGlutCallbacks.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

int
main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(testGraphInitGlut),
        cmocka_unit_test_setup_teardown(testGraphRegisterPrintFailNullParameter, setup, teardown),
        cmocka_unit_test_setup_teardown(testGraphRegisterPrintSuccess, setup, teardown),
        cmocka_unit_test_setup_teardown(testGraphUnregisterPrintFailNullParameter, setup, teardown),
        cmocka_unit_test_setup_teardown(testGraphUnregisterPrintNoCallbacksFound, setup, teardown),
        cmocka_unit_test_setup_teardown(testGraphUnregisterPrintSuccessOneCallback, setup, teardown),
        cmocka_unit_test_setup_teardown(testGraphUnregisterPrintSuccessLastCallback, setup, teardown),
        cmocka_unit_test_setup_teardown(testGraphUnregisterPrintSuccessMiddleCallback, setup, teardown),
        cmocka_unit_test_setup_teardown(testGraphGlutDisplay, setup, teardown),
        cmocka_unit_test(testGraphGlutReshapeScaleLowerThanOne),
        cmocka_unit_test(testGraphGlutReshapeScaleHigherThanOne),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
