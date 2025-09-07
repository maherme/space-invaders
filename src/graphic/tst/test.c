#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "testGraph.h"

int
main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(testGraphCreateImageFail),
        cmocka_unit_test(testGraphCreateImageSuccess),
        cmocka_unit_test(testGraphPrintImageFail),
        cmocka_unit_test(testGraphPrintImageSuccess),
        cmocka_unit_test(testGraphMoveImageFail),
        cmocka_unit_test(testGraphMoveImageWrongDirection),
        cmocka_unit_test(testGraphMoveImageRight),
        cmocka_unit_test(testGraphMoveImageRightMax),
        cmocka_unit_test(testGraphMoveImageLeft),
        cmocka_unit_test(testGraphMoveImageLeftMax),
        cmocka_unit_test(testGraphMoveImageTooEarlyToMove),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
