/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __LIST_H__
#define __LIST_H__

#include <stddef.h>
#include <stdlib.h>

/* clang-format off */
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))
/* clang-format on */

struct list_head
{
    struct list_head *next;
    struct list_head *prev;
};

/* clang-format off */
#define LIST_HEAD_INIT(name) \
    {&(name), &(name)}

#define LIST_HEAD(name) \
    struct list_head name = LIST_HEAD_INIT(name)
/* clang-format on */

static inline void
init_list_head(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}

static inline void
list_add__(struct list_head *new, struct list_head *prev, struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

static inline void
list_add(struct list_head *new, struct list_head *head)
{
    list_add__(new, head, head->next);
}

static inline void
list_add_tail(struct list_head *new, struct list_head *head)
{
    list_add__(new, head->prev, head);
}

static inline void
list_del__(struct list_head *prev, struct list_head *next)
{
    next->prev = prev;
    prev->next = next;
}

static inline void
list_del(struct list_head *entry)
{
    list_del__(entry->prev, entry->next);
}

/* clang-format off */
#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_safe(pos, n, head) \
    for (pos = (head)->next, n = pos->next; pos != (head); pos = n, n = pos->next)

#define list_for_each_entry(pos, head, member) \
    for (pos = list_entry((head)->next, __typeof__(*pos), member); \
         &pos->member != (head); \
         pos = list_entry(pos->member.next, __typeof__(*pos), member))

#define list_for_each_entry_safe(pos, n, head, member) \
    for (pos = list_entry((head)->next, __typeof__(*pos), member), n = list_entry(pos->member.next, __typeof__(*pos), member); \
         &pos->member != (head); \
         pos = n, n = list_entry(n->member.next, __typeof__(*n), member))

#define list_clear(head, type, member) \
    do { \
        type *pos, *tmp; \
        list_for_each_entry_safe(pos, tmp, head, member) { \
            list_del(&pos->member); \
            free(pos); \
        } \
    } while (0)
/* clang-format on */

#endif /* __LIST_H__ */
