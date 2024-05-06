#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "graph.h"

void
__wrap_graphCreateImage(sprite_t *sprite) {
    (void)sprite;
    function_called();
}

void
__wrap_graphPrintImage(const sprite_t * const sprite) {
    (void)sprite;
    function_called();
}
