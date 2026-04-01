/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testLives.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

int
main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(testLivesCreate),
        cmocka_unit_test(testLivesRemoveLastLive),
        cmocka_unit_test(testLivesRemoveLastLiveNullCallback),
        cmocka_unit_test(testLivesRemovePenultimateLive),
        cmocka_unit_test(testLivesRemoveMaxLivesPrinted),
        cmocka_unit_test(testLivesRemoveZeroLives),
        cmocka_unit_test(testLivesAdd),
        cmocka_unit_test(testLivesAddMaxLivesPrinted),
        cmocka_unit_test(testLivesAddZeroLives),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
