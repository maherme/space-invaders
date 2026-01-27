#include "testGraphGlutCallbacks.h"
#include "graphGlutCallbacks.h"
#include "graph.h"

void
__wrap_glClear(GLbitfield mask) {
    check_expected_uint(mask);
    function_called();
}

void
__wrap_glutSwapBuffers(void) {
    function_called();
}

void
__wrap_glViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    check_expected_int(x);
    check_expected_int(y);
    check_expected_int(width);
    check_expected_int(height);
    function_called();
}

void
__wrap_glMatrixMode(GLenum mode) {
    check_expected_uint(mode);
    function_called();
}

void
__wrap_glLoadIdentity(void) {
    function_called();
}

void
__wrap_gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top) {
    check_expected_double(left);
    check_expected_double(right);
    check_expected_double(bottom);
    check_expected_double(top);
    function_called();
}

void
__wrap_graphPrintImage(const sprite_t * const sprite) {
    check_expected_ptr(sprite);
    function_called();
}

int
setup(void **state) {
    (void)state;
    helperUT_graphGlutResetRegisteredContext();
    return 0;
}

void
testGraphRegisterPrintFailNullParameter(void **status) {
    (void)status;

    expect_uint_value(__wrap_glClear, mask, GL_COLOR_BUFFER_BIT);
    expect_function_call(__wrap_glClear);
    expect_function_call(__wrap_glutSwapBuffers);

    int result = graphRegisterPrint(NULL);
    assert_int_equal(result, -1);
    graphGlutDisplay();
}

void
testGraphRegisterPrintFailMaxCallbacks(void **status) {
    (void)status;
    void *expected_ctx = (void *)0xdeadbeef;

    expect_uint_value(__wrap_glClear, mask, GL_COLOR_BUFFER_BIT);
    expect_function_call(__wrap_glClear);
    expect_uint_value_count(__wrap_graphPrintImage, sprite, (uintptr_t)expected_ctx, MAX_PRINT_CONTEXTS);
    expect_function_calls(__wrap_graphPrintImage, MAX_PRINT_CONTEXTS);
    expect_function_call(__wrap_glutSwapBuffers);

    for(int i = 0; i < MAX_PRINT_CONTEXTS; i++) {
        graphRegisterPrint(expected_ctx);
    }
    int result = graphRegisterPrint(expected_ctx);
    assert_int_equal(result, -1);
    graphGlutDisplay();
}

void
testGraphRegisterPrintSuccess(void **status) {
    (void)status;
    void *expected_ctx = (void *)0xdeadbeef;

    expect_uint_value(__wrap_glClear, mask, GL_COLOR_BUFFER_BIT);
    expect_function_call(__wrap_glClear);
    expect_uint_value(__wrap_graphPrintImage, sprite, (uintptr_t)expected_ctx);
    expect_function_call(__wrap_graphPrintImage);
    expect_function_call(__wrap_glutSwapBuffers);

    graphRegisterPrint(expected_ctx);
    graphGlutDisplay();
}

void
testGraphUnregisterPrintFailNullParameter(void **status) {
    (void)status;

    expect_uint_value(__wrap_glClear, mask, GL_COLOR_BUFFER_BIT);
    expect_function_call(__wrap_glClear);
    expect_function_call(__wrap_glutSwapBuffers);

    int result = graphUnregisterPrint(NULL);
    assert_int_equal(result, -1);
    graphGlutDisplay();
}

void
testGraphUnregisterPrintFailMaxCallbacks(void **status) {
    (void)status;
    void *expected_ctx = (void *)0xdeadbeef;

    expect_uint_value(__wrap_glClear, mask, GL_COLOR_BUFFER_BIT);
    expect_function_call(__wrap_glClear);
    expect_function_call(__wrap_glutSwapBuffers);

    int result = graphUnregisterPrint(expected_ctx);
    assert_int_equal(result, -1);
    graphGlutDisplay();
}

void
testGraphUnregisterPrintSuccess(void **status) {
    (void)status;
    void *expected_ctx = (void *)0xdeadbeef;

    expect_uint_value(__wrap_glClear, mask, GL_COLOR_BUFFER_BIT);
    expect_function_call(__wrap_glClear);
    expect_uint_value(__wrap_graphPrintImage, sprite, (uintptr_t)expected_ctx);
    expect_function_call(__wrap_graphPrintImage);
    expect_function_call(__wrap_glutSwapBuffers);

    int result = graphRegisterPrint(expected_ctx);
    assert_int_equal(result, 0);
    graphGlutDisplay();

    expect_uint_value(__wrap_glClear, mask, GL_COLOR_BUFFER_BIT);
    expect_function_call(__wrap_glClear);
    expect_function_call(__wrap_glutSwapBuffers);

    result = graphUnregisterPrint(expected_ctx);
    assert_int_equal(result, 0);
    graphGlutDisplay();
}

void
testGraphGlutReshape(void **status) {
    (void)status;

    expect_int_value(__wrap_glViewport, x, 0);
    expect_int_value(__wrap_glViewport, y, 0);
    expect_int_value(__wrap_glViewport, width, 1);
    expect_int_value(__wrap_glViewport, height, 2);
    expect_function_call(__wrap_glViewport);

    expect_uint_value(__wrap_glMatrixMode, mode, GL_PROJECTION);
    expect_function_call(__wrap_glMatrixMode);

    expect_function_call(__wrap_glLoadIdentity);

    expect_double(__wrap_gluOrtho2D, left, 0, 0);
    expect_double(__wrap_gluOrtho2D, right, WINDOW_WIDTH, 0);
    expect_double(__wrap_gluOrtho2D, bottom, 0, 0);
    expect_double(__wrap_gluOrtho2D, top, WINDOW_HEIGHT, 0);
    expect_function_call(__wrap_gluOrtho2D);

    expect_uint_value(__wrap_glMatrixMode, mode, GL_MODELVIEW);
    expect_function_call(__wrap_glMatrixMode);

    expect_function_call(__wrap_glLoadIdentity);

    graphGlutReshape(1, 2);
}
