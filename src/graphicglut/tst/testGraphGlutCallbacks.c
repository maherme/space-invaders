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
    (void)sprite;
    function_called();
}

void
testGraphGlutDisplay(void **status) {
    (void)status;

    expect_uint_value(__wrap_glClear, mask, GL_COLOR_BUFFER_BIT);
    expect_function_call(__wrap_glClear);

    expect_function_call(__wrap_glutSwapBuffers);

    graphGlutDisplay();
}

void
testGraphGlutDisplayCallPrint(void **status) {
    (void)status;

    void *expected_ctx = (void *)0xdeadbeef;

    expect_uint_value(__wrap_glClear, mask, GL_COLOR_BUFFER_BIT);
    expect_function_call(__wrap_glClear);

    expect_function_call(__wrap_graphPrintImage);

    expect_function_call(__wrap_glutSwapBuffers);

    graphRegisterPrint(expected_ctx);
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
