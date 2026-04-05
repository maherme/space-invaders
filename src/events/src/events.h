/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __EVENTS_H__
#define __EVENTS_H__

typedef enum
{
    EVENT_LIVES_DEPLETED,
    EVENT_ALIENS_REACHED_BOTTOM,
    EVENT_REMOVE_LIFE,
    EVENT_LIVES_CHANGED,
    EVENT_COUNT
} event_type_t;

typedef void (*event_cb_t)(void *data);

void
eventRegister(event_type_t type, event_cb_t cb);

void
eventEmit(event_type_t type, void *data);

#ifdef UNIT_TESTING
event_cb_t
helperUT_eventGetCallback(event_type_t type);

void
helperUT_eventSetCallback(event_type_t type, event_cb_t cb);

void
helperUT_eventsClear(void);
#endif /* UNIT_TESTING */

#endif /* __EVENTS_H__ */
