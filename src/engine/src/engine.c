#include "engine.h"

static engine_cb_t callbacks[ENGINE_MAX_CALLBACKS];

int
engineRegister(engine_cb_t cb) {
    if(!cb) {
        return -1;
    }

    for(int i = 0; i < ENGINE_MAX_CALLBACKS; i++) {
        if(!callbacks[i]) {
            callbacks[i] = cb;
            return 0;
        }
    }
    return -1;
}

int
engineUnregister(engine_cb_t cb) {
    if(!cb) {
        return -1;
    }

    for(int i = 0; i < ENGINE_MAX_CALLBACKS; i++) {
        if(callbacks[i] == cb) {
            callbacks[i] = NULL;
            return 0;
        }
    }

    return -1;
}

void
engineRun(int rate) {
    for(int i = 0; i < rate; i++) {
        for(int j = 0; j < ENGINE_MAX_CALLBACKS; j++) {
            if(callbacks[j] != NULL) {
                callbacks[j]();
            }
        }
        usleep(1000);
    }
}


#ifdef UNIT_TESTING
void
helperUT_engineResetRegisteredCallbacks(void) {
    for(int i = 0; i < ENGINE_MAX_CALLBACKS; i++) {
        callbacks[i] = NULL;
    }
}
#endif
