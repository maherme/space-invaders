/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <stdbool.h>
#include <GL/glut.h>

#define MAX_NUM_KEYS 256

typedef enum {
    SPECIAL_KEY_RIGHT,
    SPECIAL_KEY_LEFT,
    MAX_SPECIAL_KEYS
}special_key_t;

typedef enum {
    ACTION_KEY_UP,
    ACTION_KEY_DOWN,
    ACTION_SPECIAL_KEY_UP,
    ACTION_SPECIAL_KEY_DOWN,
    MAX_KEY_ACTIONS
}key_action_t;

typedef void (*actions_cb)(void);

int
keyboardRegisterAction(actions_cb action, key_action_t type, int key);

bool
keyboardGetKeyState(unsigned char key);

bool
keyboardGetSpecialKeyState(special_key_t key);

void
keyboardInit(void);

#ifdef UNIT_TESTING
void
helperUT_keyboardResetRegisteredCallbacks(void);
#endif 

#endif 
