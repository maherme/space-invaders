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

typedef enum
{
    SQUID,
    CRAB,
    OCTOPUS
} alien_type_t;

typedef struct alien_instance_t *alien_t;

void
aliensCreate(void);

void
alienDestroy(alien_t *alien);

int
aliensGetNumberInitialAliens(void);

alien_t *
aliensGetAlienInstance(int alien_index);

#endif /* __ALIENS_H__ */
