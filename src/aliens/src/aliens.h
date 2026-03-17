/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __ALIENS_H__
#define __ALIENS_H__

#include <stdbool.h>

#define ALIENS_ROWS 5
#define ALIENS_COLS 11
#define ALIENS_INITIAL_NUMBER (ALIENS_ROWS * ALIENS_COLS)

typedef enum
{
    SQUID,
    CRAB,
    OCTOPUS
} alien_type_t;

typedef struct alien_instance *alien_t;

void
aliensCreate(void);

void
alienDestroy(alien_t alien);

bool
alienAlive(alien_t alien);

alien_t
aliensGetAlienInstance(int alien_index);

alien_t
aliensGetShooter(void);

#ifdef UNIT_TESTING
void
helperUT_alienInitPool(void);

void
helperUT_alienSetAlive(alien_t alien, bool alive);

alien_t
helperUT_alienInjectInPool(int row, int col);
#endif /* UNIT_TESTING */

#endif /* __ALIENS_H__ */
