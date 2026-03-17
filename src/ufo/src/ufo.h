/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __UFO_H__
#define __UFO_H__

#include "physic.h"
#include <stdbool.h>

typedef struct ufo_instance_t *ufo_t;

ufo_t
ufoCreate(void);

void
ufoDestroy(ufo_t *this);

direction_t
ufoGetDirection(const ufo_t this);

bool ufoCheckForMoving(ufo_t this);

#endif /* __UFO_H__ */
