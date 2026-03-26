/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include <stdbool.h>

typedef enum
{
    EXPLOSION_BULLET_SPACESHIP,
    EXPLOSION_BULLET_ALIEN,
    EXPLOSION_SPACESHIP,
    EXPLOSION_UFO,
    EXPLOSION_ALIEN,
} explosion_type_t;

void
explosionCreate(int x, int y, explosion_type_t type, void (*callback)(void));

void
explosionsDestroy(void);

bool
explosionsAllFinished(void);

unsigned int
explosionsGetExplosionHeight(explosion_type_t type);

#ifdef UNIT_TESTING
void
helperUT_explosionResetList(void);
#endif /* UNIT_TESTING */

#endif /* __EXPLOSION_H__ */
