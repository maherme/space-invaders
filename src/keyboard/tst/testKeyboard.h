#ifndef __TESTKEYBOARD_H__
#define __TESTKEYBOARD_H__

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "keyboard.h"

void
testKeyboardInit(void ** status);

void
testKeyboardKeyPressed(void ** status);

void
testKeyboardKeyPressedAndReleased(void ** status);

void
testKeyboardSpecialKeyPressed(void ** status);

void
testKeyboardSpecialKeyPressedAndReleased(void ** status);

#endif
