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

sprite_t *
__wrap_graphGetSprite(base_t *b) {
    if(!b) {
        return NULL;
    }
    return &b->sprite;
}

void
__wrap_graphPrintImage(const sprite_t * const sprite) {
    (void)sprite;
    function_called();
}
