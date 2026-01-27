#ifndef __TESTKEYBOARD_H__
#define __TESTKEYBOARD_H__

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "keyboard.h"

int
setup(void **state);

void
testKeyboardInit(void ** status);

void
testKeyboardRegisterActionNullAction(void **status);

void
testKeyboardRegisterActionInvalidKeyAction(void **status);

void
testKeyboardRegisterActionInvalidKey(void **status);

void
testKeyboardKeyPressed(void ** status);

void
testKeyboardKeyReleased(void **status);

void
testKeyboardKeyPressedAndReleased(void ** status);

void
testKeyboardSpecialKeyPressed(void ** status);

void
testKeyboardSpecialKeyReleased(void **status);

void
testKeyboardSpecialKeyPressedAndReleased(void ** status);

#endif
