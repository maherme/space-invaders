#include "testUtils.h"

extern void *
__real_calloc(size_t nelem, size_t elsize);

void *
__wrap_calloc(size_t nelem, size_t elsize) {
    bool call_real = mock_type(bool);

    if(call_real) {
        return __real_calloc(nelem, elsize);
    }
    check_expected(nelem);
    check_expected(elsize);
    function_called();
    return (void *)mock();
}

void
__wrap_perror(const char *s) {
    check_expected(s);
    function_called();
}

void
__wrap_exit(int status) {
    check_expected(status);
    function_called();
}

void
testUtilsCallocFail(void **status) {
    (void)status;

    will_return(__wrap_calloc, false);
    will_return(__wrap_calloc, NULL);
    expect_value(__wrap_calloc, nelem, 1);
    expect_value(__wrap_calloc, elsize, 1);
    expect_function_call(__wrap_calloc);
    expect_string(__wrap_perror, s, "calloc");
    expect_function_call(__wrap_perror);
    expect_value(__wrap_exit, status, EXIT_FAILURE);
    expect_function_call(__wrap_exit);

    utilsCalloc(1, 1);
}

void
testUtilsCallocSuccess(void **status) {
    (void)status;
    void *expected = (void *)0x12345678;

    will_return(__wrap_calloc, false);
    will_return(__wrap_calloc, expected);
    expect_value(__wrap_calloc, nelem, 1);
    expect_value(__wrap_calloc, elsize, 1);
    expect_function_call(__wrap_calloc);

    assert_ptr_equal(utilsCalloc(1, 1), expected);
}
