#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "testKeyboard.h"

int
main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(testKeyboardInit),
        cmocka_unit_test(testKeyboardKeyPressed),
        cmocka_unit_test(testKeyboardKeyPressedAndReleased),
        cmocka_unit_test(testKeyboardSpecialKeyPressed),
        cmocka_unit_test(testKeyboardSpecialKeyPressedAndReleased),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
