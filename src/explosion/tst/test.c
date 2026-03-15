/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testExplosion.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

int
main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup(testExplosionCreateBullet, setup),
        cmocka_unit_test_setup(testExplosionCreateUfo, setup),
        cmocka_unit_test_setup(testExplosionsDestroyListEmpty, setup),
        cmocka_unit_test_setup(testExplosionsDestroyTimeoutFalse, setup),
        cmocka_unit_test_setup(testExplosionsDestroyTimeoutTrue, setup),
        cmocka_unit_test_setup(testExplosionsDestroyTwoExplosions, setup),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
