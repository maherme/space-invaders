/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __GRAPHGLUTCALLBACKS_H__
#define __GRAPHGLUTCALLBACKS_H__

#define MAX_PRINT_CONTEXTS 59

int
graphRegisterPrint(void *ctx);

int
graphUnregisterPrint(void *ctx);

void
graphGlutDisplay(void);

void
graphGlutReshape(int w, int h);

#ifdef UNIT_TESTING
void
helperUT_graphGlutResetRegisteredContext(void);
#endif

#endif
