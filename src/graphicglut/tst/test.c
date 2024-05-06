#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "testGraphGlut.h"
#include "testGraphGlutCallbacks.h"

int
main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(testGraphInitGlut),
        cmocka_unit_test(testGraphGlutDisplay),
        cmocka_unit_test(testGraphGlutDisplayCallPrint),
        cmocka_unit_test(testGraphGlutReshape),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
