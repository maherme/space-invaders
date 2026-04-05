/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "events.h"

static event_cb_t callbacks[EVENT_COUNT];

void
eventRegister(event_type_t type, event_cb_t cb)
{
    if (type < 0 || type >= EVENT_COUNT)
    {
        return;
    }

    if (!callbacks[type])
    {
        callbacks[type] = cb;
    }
}

void
eventEmit(event_type_t type, void *data)
{
    if (type < 0 || type >= EVENT_COUNT)
    {
        return;
    }

    if (callbacks[type])
    {
        callbacks[type](data);
    }
}

#ifdef UNIT_TESTING
#include <stddef.h>

event_cb_t
helperUT_eventGetCallback(event_type_t type)
{
    return callbacks[type];
}

void
helperUT_eventSetCallback(event_type_t type, event_cb_t cb)
{
    callbacks[type] = cb;
}

void
helperUT_eventsClear(void)
{
    for (int i = 0; i < EVENT_COUNT; i++)
    {
        callbacks[i] = NULL;
    }
}
#endif /* UNIT_TESTING */
