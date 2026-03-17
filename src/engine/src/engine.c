/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "engine.h"
#include "list.h"
#include "utils.h"
#include <unistd.h>

typedef struct cb_node
{
    engine_cb_t callback;
    struct list_head node;
} cb_node_t;

static LIST_HEAD(callbacks);

int
engineRegister(engine_cb_t cb)
{
    if (!cb)
    {
        return -1;
    }

    cb_node_t *n = utilsCalloc(1, sizeof(*n));
    n->callback = cb;
    list_add(&n->node, &callbacks);

    return 0;
}

int
engineUnregister(engine_cb_t cb)
{
    if (!cb)
    {
        return -1;
    }

    cb_node_t *n, *tmp;
    int removed = 0;

    list_for_each_entry_safe(n, tmp, &callbacks, node)
    {
        if (n->callback == cb)
        {
            list_del(&n->node);
            utilsFree((void **)&n);
            removed++;
        }
    }

    return removed;
}

void
engineRun(int rate)
{
    for (int i = 0; i < rate; i++)
    {
        cb_node_t *n;

        list_for_each_entry(n, &callbacks, node)
        {
            n->callback();
        }
        usleep(1000);
    }
}

#ifdef UNIT_TESTING
void
helperUT_engineResetRegisteredCallbacks(void)
{
    list_clear_with_free(&callbacks, cb_node_t, node);
}
#endif
