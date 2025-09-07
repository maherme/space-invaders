#include "testKeyboard.h"

static void (*registered_keyboard_func)(unsigned char, int, int) = NULL;
static void (*registered_keyboard_up_func)(unsigned char, int, int) = NULL;
static void (*registered_special_func)(int, int, int) = NULL;
static void (*registered_special_up_func)(int, int, int) = NULL;

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
testingKeyboardInit(void) {
    expect_function_call(__wrap_glutKeyboardFunc);
    expect_function_call(__wrap_glutKeyboardUpFunc);
    expect_function_call(__wrap_glutSpecialFunc);
    expect_function_call(__wrap_glutSpecialUpFunc);

    keyboardInit();
}

void
testKeyboardInit(void ** status) {
    (void)status;

    testingKeyboardInit();
} 

void
testKeyboardKeyPressed(void ** status) {
    (void)status;

    testingKeyboardInit();

    registered_keyboard_func('a', 0, 0);
    assert_true(keyboardGetKeyState('a'));
}

void
testKeyboardKeyPressedAndReleased(void ** status) {
    (void)status;

    testingKeyboardInit();
    registered_keyboard_func('a', 0, 0);
    assert_true(keyboardGetKeyState('a'));

    registered_keyboard_up_func('a', 0, 0);
    assert_false(keyboardGetKeyState('a'));
}

static void
testingSpecialKeyPressed(void) {
    registered_special_func(GLUT_KEY_RIGHT, 0, 0);
    registered_special_func(GLUT_KEY_LEFT, 0, 0);
    registered_special_func(GLUT_KEY_UP, 0, 0);
    assert_true(keyboardGetSpecialKeyState(KEY_RIGHT));
    assert_true(keyboardGetSpecialKeyState(KEY_LEFT));
}

void
testKeyboardSpecialKeyPressed(void ** status) {
    (void)status;

    testingKeyboardInit();
    testingSpecialKeyPressed();
}

void
testKeyboardSpecialKeyPressedAndReleased(void ** status) {
    (void)status;

    testingKeyboardInit();
    testingSpecialKeyPressed();

    registered_special_up_func(GLUT_KEY_RIGHT, 0, 0);
    registered_special_up_func(GLUT_KEY_LEFT, 0, 0);
    registered_special_up_func(GLUT_KEY_UP, 0, 0);
    assert_false(keyboardGetSpecialKeyState(KEY_RIGHT));
    assert_false(keyboardGetSpecialKeyState(KEY_LEFT));
}
