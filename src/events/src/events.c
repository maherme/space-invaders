/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "events.h"

static event_cb_t callbacks[EVENT_COUNT][EVENTS_MAX_NUM_CB];

void
eventRegister(event_type_t type, event_cb_t cb)
{
    if (type < 0 || type >= EVENT_COUNT)
    {
        return;
    }

    for (int i = 0; i < EVENTS_MAX_NUM_CB; i++)
    {
        if (!callbacks[type][i])
        {
            callbacks[type][i] = cb;
            return;
        }
    }
}

void
eventEmit(event_type_t type, void *data)
{
    int i = 0;

    if (type < 0 || type >= EVENT_COUNT)
    {
        return;
    }

    while (i < EVENTS_MAX_NUM_CB && callbacks[type][i])
    {
        callbacks[type][i](data);
        i++;
    }
}

#ifdef UNIT_TESTING
#include <stddef.h>

event_cb_t
helperUT_eventGetCallback(event_type_t type, unsigned int index)
{
    return callbacks[type][index];
}

void
helperUT_eventSetCallback(event_type_t type, unsigned int index, event_cb_t cb)
{
    callbacks[type][index] = cb;
}

void
helperUT_eventsClear(void)
{
    for (int i = 0; i < EVENT_COUNT; i++)
    {
        for (int j = 0; j < EVENTS_MAX_NUM_CB; j++)
        {
            callbacks[i][j] = NULL;
        }
    }
}
#endif /* UNIT_TESTING */
