#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "testEngine.h"

int
main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup(testEngineRegisterFailNullParameter, setup),
        cmocka_unit_test_setup(testEngineRegisterFailMaxCallbacks, setup),
        cmocka_unit_test_setup(testEngineRegisterSuccess, setup),
        cmocka_unit_test_setup(testEngineRun, setup),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
