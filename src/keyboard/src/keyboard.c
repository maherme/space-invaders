#include "keyboard.h"

static bool key_state[MAX_NUM_KEYS];
static actions_cb key_down_actions[MAX_NUM_KEYS];
static actions_cb key_up_actions[MAX_NUM_KEYS];
static bool special_key_state[MAX_NUM_KEYS];
static actions_cb special_key_down_actions[MAX_NUM_KEYS];
static actions_cb special_key_up_actions[MAX_NUM_KEYS];

static void
keyboardDown(unsigned char key, int x, int y) {
    (void)x, (void)y;
    key_state[key] = true;
    if(key_down_actions[key]) {
        key_down_actions[key]();
    }
}

static void
keyboardUp(unsigned char key, int x, int y) {
    (void) x, (void)y;
    key_state[key] = false;
    if(key_up_actions[key]) {
        key_up_actions[key]();
    }
}

static void
keyboardSpecialDown(int key, int x, int y) {
    (void) x, (void)y;
    int _key = MAX_SPECIAL_KEYS;

    switch(key) {
        case GLUT_KEY_LEFT:
            special_key_state[SPECIAL_KEY_LEFT] = true;
            _key = SPECIAL_KEY_LEFT;
            break;
        case GLUT_KEY_RIGHT:
            special_key_state[SPECIAL_KEY_RIGHT] = true;
            _key = SPECIAL_KEY_RIGHT;
            break;
    }

    if(special_key_down_actions[_key]) {
        special_key_down_actions[_key]();
    }
}

static void
keyboardSpecialUp(int key, int x, int y) {
    (void) x, (void)y;
    int _key = MAX_SPECIAL_KEYS;

    switch(key) {
        case GLUT_KEY_LEFT:
            special_key_state[SPECIAL_KEY_LEFT] = false;
            _key = SPECIAL_KEY_LEFT;
            break;
        case GLUT_KEY_RIGHT:
            special_key_state[SPECIAL_KEY_RIGHT] = false;
            _key = SPECIAL_KEY_RIGHT;
            break;
    }

    if(special_key_up_actions[_key]) {
        special_key_up_actions[_key]();
    }
}

int
keyboardRegisterAction(actions_cb action, key_action_t type, int key) {
    if(!action || key > MAX_NUM_KEYS) {
        return -1;
    }

    switch (type) {
        case ACTION_KEY_UP:
            key_up_actions[key] = action;
            break;
        case ACTION_KEY_DOWN:
            key_down_actions[key] = action;
            break;
        case ACTION_SPECIAL_KEY_UP:
            special_key_up_actions[key] = action;
            break;
        case ACTION_SPECIAL_KEY_DOWN: 
            special_key_down_actions[key] = action;
            break;
        default:
            return -1;
            break;
    }

    return 0;
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
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(keyboardSpecialDown);
    glutSpecialUpFunc(keyboardSpecialUp);
}

#ifdef UNIT_TESTING
void
helperUT_keyboardResetRegisteredCallbacks(void) {
    for(int i = 0; i < MAX_NUM_KEYS; i++) {
        key_down_actions[i] = NULL;
        key_up_actions[i] = NULL;
        special_key_down_actions[i] = NULL;
        special_key_up_actions[i] = NULL;
    }
}
#endif
