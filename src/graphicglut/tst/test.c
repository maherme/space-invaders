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
        cmocka_unit_test_setup(testGraphInitGlut, setup),
        cmocka_unit_test_setup(testGraphRegisterPrintFailNullParameter, setup),
        cmocka_unit_test_setup(testGraphRegisterPrintSuccess, setup),
        cmocka_unit_test_setup(testGraphUnregisterPrintFailNullParameter, setup),
        cmocka_unit_test_setup(testGraphUnregisterPrintNoCallbacksFound, setup),
        cmocka_unit_test_setup(testGraphUnregisterPrintSuccessOneCallback, setup),
        cmocka_unit_test_setup(testGraphUnregisterPrintSuccessLastCallback, setup),
        cmocka_unit_test_setup(testGraphUnregisterPrintSuccessMiddleCallback, setup),
        cmocka_unit_test_setup(testGraphGlutReshape, setup),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
