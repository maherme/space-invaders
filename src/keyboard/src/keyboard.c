#include "keyboard.h"

static bool key_state[256] = {false};
static bool special_key_state[256] = {false};

static void
keyboardDown(unsigned char key, int x, int y) {
    (void)x, (void)y;
    key_state[key] = true;
}

static void
keyboardUp(unsigned char key, int x, int y) {
    (void) x, (void)y;
    key_state[key] = false;
}

static void
keyboardSpecialDown(int key, int x, int y) {
    (void) x, (void)y;

    switch(key) {
        case GLUT_KEY_LEFT:
            special_key_state[KEY_LEFT] = true;
            break;
        case GLUT_KEY_RIGHT:
            special_key_state[KEY_RIGHT] = true;
            break;
    }
}

static void
keyboardSpecialUp(int key, int x, int y) {
    (void) x, (void)y;

    switch(key) {
        case GLUT_KEY_LEFT:
            special_key_state[KEY_LEFT] = false;
            break;
        case GLUT_KEY_RIGHT:
            special_key_state[KEY_RIGHT] = false;
            break;
    }
}

bool
keyboardGetKeyState(unsigned char key) {
    return key_state[key];
}

bool
keyboardGetSpecialKeyState(special_key_t key) {
    return special_key_state[key];
}

void
keyboardInit(void) {
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(keyboardSpecialDown);
    glutSpecialUpFunc(keyboardSpecialUp);
}
