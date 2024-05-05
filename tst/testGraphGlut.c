#include "testGraphGlut.h"

void
__wrap_glutInit(int *argcp, char **argv) {
    check_expected(argcp);
    check_expected(argv);
    function_called();
}

void
__wrap_glutInitDisplayMode(unsigned int mode) {
    check_expected(mode);
    function_called();
}

void
__wrap_glutInitWindowSize(int width, int height) {
    check_expected(width);
    check_expected(height);
    function_called();
}

void
__wrap_glutInitWindowPosition(int x, int y) {
    check_expected(x);
    check_expected(y);
    function_called();
}

int
__wrap_glutCreateWindow(char *name) {
    int windowNumber = mock_type(int);
    check_expected(name);
    function_called();
    return (int)windowNumber;
}

void
__wrap_glutDisplayFunc(void (*func)(void)) {
    check_expected_ptr(func);
    function_called();
}

static void
foo(void) {}

void
testGraphInitGlut(void ** status) {
    (void)status;
    int argc = 1;
    char *argv[] = {"Foo"};

    graphInitGlutConfig_t initGlutConfig = {
        .main_argc = &argc,
        .main_argv = argv,
        .displayMode = GLUT_DOUBLE | GLUT_RGB,
        .windowWidth = WINDOW_WIDTH,
        .windowHeight = WINDOW_HEIGHT,
        .windowPositionX = 0,
        .windowPositionY = 0,
        .windowName = "Foo",
        .displayFunc = foo,
    };

    expect_any(__wrap_glutInit, argcp);
    expect_any(__wrap_glutInit, argv);
    expect_function_call(__wrap_glutInit);

    expect_value(__wrap_glutInitDisplayMode, mode, GLUT_DOUBLE |GLUT_RGB);
    expect_function_call(__wrap_glutInitDisplayMode);

    expect_value(__wrap_glutInitWindowSize, width, WINDOW_WIDTH);
    expect_value(__wrap_glutInitWindowSize, height, WINDOW_HEIGHT);
    expect_function_call(__wrap_glutInitWindowSize);

    expect_value(__wrap_glutInitWindowPosition, x, 0);
    expect_value(__wrap_glutInitWindowPosition, y, 0);
    expect_function_call(__wrap_glutInitWindowPosition);

    expect_string(__wrap_glutCreateWindow, name, "Foo");
    will_return(__wrap_glutCreateWindow, 1);
    expect_function_call(__wrap_glutCreateWindow);

    expect_value(__wrap_glutDisplayFunc, func, foo);
    expect_function_call(__wrap_glutDisplayFunc);

    graphInitGlut(&initGlutConfig);
}
