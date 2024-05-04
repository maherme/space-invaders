#include "testGraphGlutCallbacks.h"

void
__wrap_glClear(GLbitfield mask) {
    check_expected(mask);
    function_called();
}

void
__wrap_glutSwapBuffers(void) {
    function_called();
}

void
testGraphGlutDisplay(void **status) {
    (void)status;

    expect_value(__wrap_glClear, mask, GL_COLOR_BUFFER_BIT);
    expect_function_call(__wrap_glClear);

    expect_function_call(__wrap_glutSwapBuffers);

    graphGlutDisplay();
}
