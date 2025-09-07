#include "testEngine.h"

int
__wrap_usleep(useconds_t usec) {
    (void)usec;
    check_expected_uint(usec);
    function_called();
    return 0;
}

int
setup(void ** state) {
    (void)state;
    helperUT_engineResetRegisteredCallbacks();
    return 0;
}

static void
callback_foo(void) {
    function_called();
}

void
testEngineRegisterFailNullParameter(void ** status) {
    (void)status;

    int result = engineRegister(NULL);
    assert_int_equal(result, -1);
}

void
testEngineRegisterFailMaxCallbacks(void ** status) {
    (void)status;

    for(int i = 0; i < ENGINE_MAX_CALLBACKS; i++) {
        engineRegister(callback_foo);
    }
    int result = engineRegister(callback_foo);
    assert_int_equal(result, -1);
}

void
testEngineRegisterSuccess(void ** status) {
    (void)status;

    int result = engineRegister(callback_foo);
    assert_int_equal(result, 1);
}

void
testEngineRun(void ** status) {
    (void)status;

    engineRegister(callback_foo);

    for(int i = 0; i < ENGINE_RATE; i++) {
        expect_function_call(callback_foo);
        expect_uint_value(__wrap_usleep, usec, 1000);
        expect_function_call(__wrap_usleep);
    }
    engineRun();
}
