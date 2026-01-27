#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "testPhysic.h"

int
main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(testPhysicMoveSpriteFail),
        cmocka_unit_test(testPhysicMoveSpriteWrongDirection),
        cmocka_unit_test(testPhysicMoveSpriteRight),
        cmocka_unit_test(testPhysicMoveSpriteRightMax),
        cmocka_unit_test(testPhysicMoveSpriteLeft),
        cmocka_unit_test(testPhysicMoveSpriteLeftMax),
        cmocka_unit_test(testPhysicMoveSpriteUp),
        cmocka_unit_test(testPhysicMoveSpriteUpMax),
        cmocka_unit_test(testPhysicMoveSpriteTooEarlyToMove),
        cmocka_unit_test(testPhysicCheckCeillingCollisionNullParameter),
        cmocka_unit_test(testPhysicCheckCeillingCollisionTrue),
        cmocka_unit_test(testPhysicCheckCeillingCollisionFalse),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
