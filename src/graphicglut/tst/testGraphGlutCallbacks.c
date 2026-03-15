/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testGraphGlutCallbacks.h"
#include "graph.h"
#include "graphGlutCallbacks.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

void
__wrap_glClear(GLbitfield mask)
{
    check_expected_uint(mask);
    function_called();
}

void
__wrap_glutSwapBuffers(void)
{
    function_called();
}

void
__wrap_glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
    check_expected_int(x);
    check_expected_int(y);
    check_expected_int(width);
    check_expected_int(height);
    function_called();
}

void
__wrap_glMatrixMode(GLenum mode)
{
    check_expected_uint(mode);
    function_called();
}

void
__wrap_glLoadIdentity(void)
{
    function_called();
}

void
__wrap_gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)
{
    check_expected_double(left);
    check_expected_double(right);
    check_expected_double(bottom);
    check_expected_double(top);
    function_called();
}

void
__wrap_graphPrintImage(const sprite_t *const sprite)
{
    check_expected_ptr(sprite);
    function_called();
}

int
setup(void **state)
{
    (void)state;
    helperUT_graphGlutResetRegisteredContext();
    return 0;
}

void
testGraphRegisterPrintFailNullParameter(void **status)
{
    (void)status;

    expect_uint_value(__wrap_glClear, mask, GL_COLOR_BUFFER_BIT);
    expect_function_call(__wrap_glClear);
    expect_function_call(__wrap_glutSwapBuffers);

    int result = graphRegisterPrint(NULL);
    assert_int_equal(result, -1);
    graphGlutDisplay();
}

static void
register_ctxs(void **ctx, int n)
{
    for (int i = 0; i < n; i++)
    {
        expect_function_call(__wrap_utilsCalloc);
        int result = graphRegisterPrint(ctx[i]);
        assert_int_equal(result, 0);
    }
}

static void
expect_display_success(void **ctx, int n)
{
    expect_uint_value(__wrap_glClear, mask, GL_COLOR_BUFFER_BIT);
    expect_function_call(__wrap_glClear);

    for (int i = 0; i < n; i++)
    {
        expect_uint_value(__wrap_graphPrintImage, sprite, (uintptr_t)ctx[n - 1 - i]);
        expect_function_call(__wrap_graphPrintImage);
    }

    expect_function_call(__wrap_glutSwapBuffers);
}

void
testGraphRegisterPrintSuccess(void **status)
{
    (void)status;

    void *expected_ctx[] = {(void *)0xdeadbeef};
    register_ctxs(expected_ctx, ARRAY_SIZE(expected_ctx));

    expect_display_success(expected_ctx, ARRAY_SIZE(expected_ctx));
    graphGlutDisplay();
}

void
testGraphUnregisterPrintFailNullParameter(void **status)
{
    (void)status;

    expect_uint_value(__wrap_glClear, mask, GL_COLOR_BUFFER_BIT);
    expect_function_call(__wrap_glClear);
    expect_function_call(__wrap_glutSwapBuffers);

    int result = graphUnregisterPrint(NULL);
    assert_int_equal(result, -1);
    graphGlutDisplay();
}

void
testGraphUnregisterPrintNoCallbacksFound(void **status)
{
    (void)status;
    void *expected_ctx = (void *)0xdeadbeef;

    expect_uint_value(__wrap_glClear, mask, GL_COLOR_BUFFER_BIT);
    expect_function_call(__wrap_glClear);
    expect_function_call(__wrap_glutSwapBuffers);

    int result = graphUnregisterPrint(expected_ctx);
    assert_int_equal(result, 0);
    graphGlutDisplay();
}

void
testGraphUnregisterPrintSuccessOneCallback(void **status)
{
    (void)status;

    void *expected_ctx[] = {(void *)0xdeadbeef};
    register_ctxs(expected_ctx, ARRAY_SIZE(expected_ctx));

    expect_display_success(expected_ctx, ARRAY_SIZE(expected_ctx));
    graphGlutDisplay();

    expect_function_call(__wrap_utilsFree);
    expect_uint_value(__wrap_glClear, mask, GL_COLOR_BUFFER_BIT);
    expect_function_call(__wrap_glClear);
    expect_function_call(__wrap_glutSwapBuffers);

    int result = graphUnregisterPrint(expected_ctx[0]);
    assert_int_equal(result, 1);
    graphGlutDisplay();
}

static void
expect_display_list(void **ctx, int n)
{
    expect_uint_value(__wrap_glClear, mask, GL_COLOR_BUFFER_BIT);
    expect_function_call(__wrap_glClear);

    for (int i = 0; i < n; i++)
    {
        expect_uint_value(__wrap_graphPrintImage, sprite, (uintptr_t)ctx[i]);
        expect_function_call(__wrap_graphPrintImage);
    }

    expect_function_call(__wrap_glutSwapBuffers);
}

void
testGraphUnregisterPrintSuccessLastCallback(void **status)
{
    (void)status;
    void *expected_ctx[] = {(void *)0xdeadbeef, (void *)0xbeefdead};

    register_ctxs(expected_ctx, ARRAY_SIZE(expected_ctx));

    expect_display_success(expected_ctx, ARRAY_SIZE(expected_ctx));
    graphGlutDisplay();

    expect_function_call(__wrap_utilsFree);

    void *remaining[] = {expected_ctx[0]};
    expect_display_list(remaining, ARRAY_SIZE(remaining));

    int result = graphUnregisterPrint(expected_ctx[1]);
    assert_int_equal(result, 1);

    graphGlutDisplay();
}

void
testGraphUnregisterPrintSuccessMiddleCallback(void **status)
{
    (void)status;
    void *expected_ctx[] = {(void *)0x1, (void *)0x2, (void *)0x3};

    register_ctxs(expected_ctx, ARRAY_SIZE(expected_ctx));

    expect_display_success(expected_ctx, ARRAY_SIZE(expected_ctx));
    graphGlutDisplay();

    expect_function_call(__wrap_utilsFree);

    void *remaining[] = {expected_ctx[2], expected_ctx[0]};
    expect_display_list(remaining, ARRAY_SIZE(remaining));

    int result = graphUnregisterPrint(expected_ctx[1]);
    assert_int_equal(result, 1);

    graphGlutDisplay();
}

void
testGraphGlutReshape(void **status)
{
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
