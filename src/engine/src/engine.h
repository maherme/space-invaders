/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <unistd.h>

#define MONITOR_REFRESH_RATE    60
#define ENGINE_RATE             (int)((1/(double)MONITOR_REFRESH_RATE)*1000)
#define ENGINE_MAX_CALLBACKS 5

typedef void (*engine_cb_t)(void);

int
engineRegister(engine_cb_t cb);

int
engineUnregister(engine_cb_t cb);

void
engineRun(int rate);

#ifdef UNIT_TESTING
void
helperUT_engineResetRegisteredCallbacks(void);
#endif

#endif
