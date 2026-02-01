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

void *
utilsCalloc(size_t nelem, size_t elsize);

void
utilsFree(void **ptr);

#endif
