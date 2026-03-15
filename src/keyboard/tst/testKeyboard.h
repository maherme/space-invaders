/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __TESTKEYBOARD_H__
#define __TESTKEYBOARD_H__

int
setup(void **state);

void
testKeyboardInit(void **status);

void
testKeyboardRegisterActionNullAction(void **status);

void
testKeyboardRegisterActionInvalidKeyAction(void **status);

void
testKeyboardRegisterActionInvalidKey(void **status);

void
testKeyboardKeyPressed(void **status);

void
testKeyboardKeyReleased(void **status);

void
testKeyboardKeyPressedAndReleased(void **status);

void
testKeyboardSpecialKeyPressed(void **status);

void
testKeyboardSpecialKeyReleased(void **status);

void
testKeyboardSpecialKeyPressedAndReleased(void **status);

#endif
