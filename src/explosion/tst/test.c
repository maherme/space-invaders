/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "testExplosion.h"

int
main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(testExplosionCreate),
        cmocka_unit_test(testExplosionTimeoutNullParameter),
        cmocka_unit_test(testExplosionTimeoutTrue),
        cmocka_unit_test(testExplosionTimeoutFalse),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
