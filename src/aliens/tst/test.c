/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testAliens.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

int
main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(testAliensCreate),
        cmocka_unit_test(testAlienDestroyNullParameter),
        cmocka_unit_test(testAlienDestroy),
        cmocka_unit_test(testAliensGetAlienInstanceInvalidIndex),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
