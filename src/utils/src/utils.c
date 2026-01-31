/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

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
