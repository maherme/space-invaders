#include "utils.h"

void *
utilsCalloc(size_t nelem, size_t elsize) {
    void *ret = calloc(nelem, elsize);
    if(!ret) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }
    return ret;
}

void
utilsFree(void **ptr) {
    if(!ptr || !*ptr) {
        return;
    }

    free(*ptr);
    *ptr = NULL;
}
