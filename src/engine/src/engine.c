#include "engine.h"

static engine_cb_t callbacks[ENGINE_MAX_CALLBACKS];
static int cb_count;

int
engineRegister(engine_cb_t cb) {
    if((cb_count >= ENGINE_MAX_CALLBACKS) || !cb) {
        return -1;
    }

    callbacks[cb_count] = cb;
    return ++cb_count;
}

void
engineRun(void) {
    for(int i = 0 ; i < ENGINE_RATE; i++) {
        for(int j = 0 ; j < cb_count; j++) {
            callbacks[j]();
        }
        usleep(1000);
    }
}

void
helperUT_engineResetRegisteredCallbacks(void) {
    for(int i = 0; i < cb_count; i++) {
        callbacks[i] = NULL;
    }
    cb_count = 0;
}
