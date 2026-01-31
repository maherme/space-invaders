/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "testKeyboard.h"

static void (*registered_keyboard_func)(unsigned char, int, int) = NULL;
static void (*registered_keyboard_up_func)(unsigned char, int, int) = NULL;
static void (*registered_special_func)(int, int, int) = NULL;
static void (*registered_special_up_func)(int, int, int) = NULL;

void
__wrap_glutIgnoreKeyRepeat(int ignore) {
    check_expected_int(ignore);
    function_called();
}

void
__wrap_glutKeyboardFunc(void (*func)(unsigned char key, int x, int y)) {
    assert_non_null(func);
    registered_keyboard_func = func;
    function_called();
}
void
__wrap_glutKeyboardUpFunc(void (*func)(unsigned char key, int x, int y)) {
    assert_non_null(func);
    registered_keyboard_up_func = func;
    function_called();
}

void
__wrap_glutSpecialFunc(void (*func)(int key, int x, int y)) {
    assert_non_null(func);
    registered_special_func = func;
    function_called();
}

void
__wrap_glutSpecialUpFunc(void (*func)(int key, int x, int y)) {
    assert_non_null(func);
    registered_special_up_func = func;
    function_called();
}

static void
callback_foo(void) {
    function_called();
}

int
setup(void **state) {
    (void)state;
    helperUT_keyboardResetRegisteredCallbacks();
    return 0;
}

void
testKeyboardInit(void **status) {
    (void)status;

    expect_int_value(__wrap_glutIgnoreKeyRepeat, ignore, 1);
    expect_function_call(__wrap_glutIgnoreKeyRepeat);
    expect_function_call(__wrap_glutKeyboardFunc);
    expect_function_call(__wrap_glutKeyboardUpFunc);
    expect_function_call(__wrap_glutSpecialFunc);
    expect_function_call(__wrap_glutSpecialUpFunc);

    keyboardInit();
} 

void
testKeyboardRegisterActionNullAction(void **status) {
    (void)status;

    int result = keyboardRegisterAction(NULL, ACTION_KEY_DOWN, 'a');
    assert_int_equal(result, -1);

    registered_keyboard_func('a', 0, 0);
    assert_true(keyboardGetKeyState('a'));
}

void
testKeyboardRegisterActionInvalidKeyAction(void **status) {
    (void)status;

    int result = keyboardRegisterAction(callback_foo, MAX_KEY_ACTIONS, 'a');
    assert_int_equal(result, -1);

    registered_keyboard_func('a', 0, 0);
    assert_true(keyboardGetKeyState('a'));
}

void
testKeyboardRegisterActionInvalidKey(void **status) {
    (void)status;

    int result = keyboardRegisterAction(callback_foo, ACTION_KEY_DOWN, 257);
    assert_int_equal(result, -1);

    registered_keyboard_func('a', 0, 0);
    assert_true(keyboardGetKeyState('a'));
}

void
testKeyboardKeyPressed(void **status) {
    (void)status;

    expect_function_call(callback_foo);
    keyboardRegisterAction(callback_foo, ACTION_KEY_DOWN, 'a');

    registered_keyboard_func('a', 0, 0);
    assert_true(keyboardGetKeyState('a'));
}
void
testKeyboardKeyReleased(void **status) {
    (void)status;

    expect_function_call(callback_foo);
    keyboardRegisterAction(callback_foo, ACTION_KEY_UP, 'a');

    registered_keyboard_up_func('a', 0, 0);
    assert_false(keyboardGetKeyState('a'));
}

void
testKeyboardKeyPressedAndReleased(void **status) {
    (void)status;

    registered_keyboard_func('a', 0, 0);
    assert_true(keyboardGetKeyState('a'));

    registered_keyboard_up_func('a', 0, 0);
    assert_false(keyboardGetKeyState('a'));
}

void
testKeyboardSpecialKeyPressed(void **status) {
    (void)status;

    expect_function_call(callback_foo);
    keyboardRegisterAction(callback_foo, ACTION_SPECIAL_KEY_DOWN, SPECIAL_KEY_RIGHT);
    expect_function_call(callback_foo);
    keyboardRegisterAction(callback_foo, ACTION_SPECIAL_KEY_DOWN, SPECIAL_KEY_LEFT);

    registered_special_func(GLUT_KEY_RIGHT, 0, 0);
    registered_special_func(GLUT_KEY_LEFT, 0, 0);
    registered_special_func(GLUT_KEY_UP, 0, 0);
    assert_true(keyboardGetSpecialKeyState(SPECIAL_KEY_RIGHT));
    assert_true(keyboardGetSpecialKeyState(SPECIAL_KEY_LEFT));
}

void
testKeyboardSpecialKeyReleased(void **status) {
    (void)status;

    expect_function_call(callback_foo);
    keyboardRegisterAction(callback_foo, ACTION_SPECIAL_KEY_UP, SPECIAL_KEY_RIGHT);
    expect_function_call(callback_foo);
    keyboardRegisterAction(callback_foo, ACTION_SPECIAL_KEY_UP, SPECIAL_KEY_LEFT);

    registered_special_up_func(GLUT_KEY_RIGHT, 0, 0);
    registered_special_up_func(GLUT_KEY_LEFT, 0, 0);
    registered_special_up_func(GLUT_KEY_UP, 0, 0);
    assert_false(keyboardGetSpecialKeyState(SPECIAL_KEY_RIGHT));
    assert_false(keyboardGetSpecialKeyState(SPECIAL_KEY_LEFT));
}

void
testKeyboardSpecialKeyPressedAndReleased(void **status) {
    (void)status;

    registered_special_func(GLUT_KEY_RIGHT, 0, 0);
    registered_special_func(GLUT_KEY_LEFT, 0, 0);
    registered_special_func(GLUT_KEY_UP, 0, 0);
    assert_true(keyboardGetSpecialKeyState(SPECIAL_KEY_RIGHT));
    assert_true(keyboardGetSpecialKeyState(SPECIAL_KEY_LEFT));

    registered_special_up_func(GLUT_KEY_RIGHT, 0, 0);
    registered_special_up_func(GLUT_KEY_LEFT, 0, 0);
    registered_special_up_func(GLUT_KEY_UP, 0, 0);
    assert_false(keyboardGetSpecialKeyState(SPECIAL_KEY_RIGHT));
    assert_false(keyboardGetSpecialKeyState(SPECIAL_KEY_LEFT));
}
