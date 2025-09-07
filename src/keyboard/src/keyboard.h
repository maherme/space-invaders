#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <stdbool.h>
#include <GL/glut.h>

typedef enum {
    KEY_RIGHT,
    KEY_LEFT
}special_key_t;

bool
keyboardGetKeyState(unsigned char key);

bool
keyboardGetSpecialKeyState(special_key_t key);

void
keyboardInit(void);

#endif 
