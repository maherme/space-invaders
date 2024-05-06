#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "testUtils.h"

int
main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(testUtilsCallocFail),
        cmocka_unit_test(testUtilsCallocSuccess),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
