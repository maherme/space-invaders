#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "testKeyboard.h"

int
main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup(testKeyboardInit, setup),
        cmocka_unit_test_setup(testKeyboardRegisterActionNullAction, setup),
        cmocka_unit_test_setup(testKeyboardRegisterActionInvalidKeyAction, setup),
        cmocka_unit_test_setup(testKeyboardRegisterActionInvalidKey, setup),
        cmocka_unit_test_setup(testKeyboardKeyPressed, setup),
        cmocka_unit_test_setup(testKeyboardKeyReleased, setup),
        cmocka_unit_test_setup(testKeyboardKeyPressedAndReleased, setup),
        cmocka_unit_test_setup(testKeyboardSpecialKeyPressed, setup),
        cmocka_unit_test_setup(testKeyboardSpecialKeyReleased, setup),
        cmocka_unit_test_setup(testKeyboardSpecialKeyPressedAndReleased, setup),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
