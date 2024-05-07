#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "utils.h"

void *
__wrap_utilsCalloc(size_t nelem, size_t elsize){
    (void)nelem, (void)elsize;
    function_called();
    return calloc(nelem, elsize);
}
