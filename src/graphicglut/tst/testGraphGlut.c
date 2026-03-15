/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testGraphGlut.h"
#include "graph.h"
#include "graphGlut.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

void
__wrap_glutInit(int *argcp, char **argv)
{
    check_expected_ptr(argcp);
    check_expected_ptr(argv);
    function_called();
}

void
__wrap_glutInitDisplayMode(unsigned int mode)
{
    check_expected_uint(mode);
    function_called();
}

void
__wrap_glutInitWindowSize(int width, int height)
{
    check_expected_int(width);
    check_expected_int(height);
    function_called();
}

void
__wrap_glutInitWindowPosition(int x, int y)
{
    check_expected_int(x);
    check_expected_int(y);
    function_called();
}

int
__wrap_glutCreateWindow(char *name)
{
    int windowNumber = mock_type(int);
    check_expected_ptr(name);
    function_called();
    return (int)windowNumber;
}

void
__wrap_glutDisplayFunc(void (*_func)(void))
{
    void *func = cast_to_void_pointer(_func);
    check_expected_ptr(func);
    function_called();
}

void
__wrap_glutReshapeFunc(void (*_func)(int w, int h))
{
    void *func = cast_to_void_pointer(_func);
    check_expected_ptr(func);
    function_called();
}

void
__wrap_glEnable(GLenum cap)
{
    check_expected_uint(cap);
    function_called();
}

static void
fooDisplay(void)
{
}

static void
fooReshape(int w, int h)
{
    (void)w, (void)h;
}

void
testGraphInitGlut(void **status)
{
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
        .displayFunc = fooDisplay,
        .reshapeFunc = fooReshape,
    };

    expect_any(__wrap_glutInit, argcp);
    expect_any(__wrap_glutInit, argv);
    expect_function_call(__wrap_glutInit);

    expect_uint_value(__wrap_glutInitDisplayMode, mode, GLUT_DOUBLE | GLUT_RGB);
    expect_function_call(__wrap_glutInitDisplayMode);

    expect_int_value(__wrap_glutInitWindowSize, width, WINDOW_WIDTH);
    expect_int_value(__wrap_glutInitWindowSize, height, WINDOW_HEIGHT);
    expect_function_call(__wrap_glutInitWindowSize);

    expect_int_value(__wrap_glutInitWindowPosition, x, 0);
    expect_int_value(__wrap_glutInitWindowPosition, y, 0);
    expect_function_call(__wrap_glutInitWindowPosition);

    expect_string(__wrap_glutCreateWindow, name, "Foo");
    will_return(__wrap_glutCreateWindow, 1);
    expect_function_call(__wrap_glutCreateWindow);

    expect_uint_value(__wrap_glutDisplayFunc, func, (uintmax_t)fooDisplay);
    expect_function_call(__wrap_glutDisplayFunc);

    expect_uint_value(__wrap_glutReshapeFunc, func, (uintmax_t)fooReshape);
    expect_function_call(__wrap_glutReshapeFunc);

    expect_uint_value(__wrap_glEnable, cap, GL_TEXTURE_2D);
    expect_function_call(__wrap_glEnable);

    graphInitGlut(&initGlutConfig);
}
