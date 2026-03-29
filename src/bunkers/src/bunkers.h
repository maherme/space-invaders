/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __BUNKERS__H__
#define __BUNKERS__H__

typedef struct bunker_instance_t *bunker_t;

void
bunkersCreate(void);

void
bunkersCallFunctionForEach(void (*fn)(bunker_t, void *ctx), void *ctx);

#endif /* __BUNKERS__H__ */
