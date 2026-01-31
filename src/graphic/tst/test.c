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
#include "testGraph.h"

int
main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(testGraphCreateImageFail),
        cmocka_unit_test(testGraphCreateImageSuccess),
        cmocka_unit_test(testGraphGetSpriteFail),
        cmocka_unit_test(testGraphGetSpriteSuccess),
        cmocka_unit_test(testGraphPrintImageFail),
        cmocka_unit_test(testGraphPrintImageSuccess),
        cmocka_unit_test(testGraphDestroyObjectNullParameter),
        cmocka_unit_test(testGraphDestroyObjectSuccess),
   };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
