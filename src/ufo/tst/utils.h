/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define NS_PER_MS   1000000LL
#define NS_PER_S    1000000000LL

void *
utilsCalloc(size_t nelem, size_t elsize);

void
utilsFree(void **ptr);

bool
utilsCheckTimeout(struct timespec time, long long timeout_ns);

#endif
