/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testPhysic.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

int
main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(testPhysicMoveSpriteFail),
        cmocka_unit_test(testPhysicMoveSpriteWrongDirection),
        cmocka_unit_test(testPhysicMoveSpriteRight),
        cmocka_unit_test(testPhysicMoveSpriteRightMax),
        cmocka_unit_test(testPhysicMoveSpriteLeft),
        cmocka_unit_test(testPhysicMoveSpriteLeftMax),
        cmocka_unit_test(testPhysicMoveSpriteUp),
        cmocka_unit_test(testPhysicMoveSpriteUpMax),
        cmocka_unit_test(testPhysicMoveSpriteDown),
        cmocka_unit_test(testPhysicMoveSpriteDownMax),
        cmocka_unit_test(testPhysicMoveSpriteTooEarlyToMove),
        cmocka_unit_test(testPhysicCheckBorderCollisionNullParameter),
        cmocka_unit_test(testPhysicCheckBorderCollisionUpTrue),
        cmocka_unit_test(testPhysicCheckBorderCollisionDownTrue),
        cmocka_unit_test(testPhysicCheckBorderCollisionRightTrue),
        cmocka_unit_test(testPhysicCheckBorderCollisionLeftTrue),
        cmocka_unit_test(testPhysicCheckBorderCollisionFalse),
        cmocka_unit_test(testPhysicCheckSpriteBoxCollisionNullParameters),
        cmocka_unit_test(testPhysicCheckSpriteBoxCollisionFalse),
        cmocka_unit_test(testPhysicCheckSpriteBoxCollisionTrue),
        cmocka_unit_test(testPhysicCheckSpritePixelCollisionNullParameters),
        cmocka_unit_test(testPhysicCheckSpritePixelCollisionCheckBoxesFalse),
        cmocka_unit_test(testPhysicCheckSpritePixelCollisionFalseCheckBoxesTrue),
        cmocka_unit_test(testPhysicCheckSpritePixelCollisionJustBoder),
        cmocka_unit_test(testPhysicCheckSpritePixelCollisionTrueCheckBoxesTrue),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
