/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __SPACESHIP_H__
#define __SPACESHIP_H__

typedef struct spaceship_instance_t *spaceship_t;

spaceship_t
spaceshipCreate(int x, int y);

#endif
