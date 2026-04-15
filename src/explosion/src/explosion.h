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

#include "entity_types.h"
#include <stdbool.h>

typedef struct explosion_instance *explosion_t;

explosion_t
explosionCreate(int x, int y, entity_type_t type, void (*callback)(void));

void
explosionsDestroy(void);

bool
explosionsAllFinished(void);

unsigned int
explosionsGetExplosionHeight(entity_type_t type);

#ifdef UNIT_TESTING
void
helperUT_explosionResetList(void);
#endif /* UNIT_TESTING */

#endif /* __EXPLOSION_H__ */
