/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void *
utilsCalloc(size_t nelem, size_t elsize)
{
    void *ret = calloc(nelem, elsize);
    if (!ret)
    {
        perror("calloc");
        exit(EXIT_FAILURE);
    }
    return ret;
}

bool
utilsCheckTimeout(struct timespec time, long long timeout_ns)
{
    if (timeout_ns < 0)
    {
        return false;
    }

    struct timespec current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    long long delta_time = (current_time.tv_sec - time.tv_sec) * NS_PER_S + (current_time.tv_nsec - time.tv_nsec);
    if (delta_time >= timeout_ns)
    {
        return true;
    }

    return false;
}
