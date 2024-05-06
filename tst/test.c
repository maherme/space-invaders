#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "testGraphGlut.h"
#include "testGraphGlutCallbacks.h"
#include "testSpaceship.h"
#include "testUtils.h"

int
main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(testGraphInitGlut),
        cmocka_unit_test(testGraphGlutDisplay),
        cmocka_unit_test(testSpaceshipCreate),
        cmocka_unit_test(testUtilsCallocFail),
        cmocka_unit_test(testUtilsCallocSuccess),
        cmocka_unit_test(testSpaceshipGetSpriteFail),
        cmocka_unit_test(testSpaceshipGetSpriteSuccess),
        cmocka_unit_test(testSpaceshipPrintFail),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
