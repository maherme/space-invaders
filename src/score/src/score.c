/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#include "score.h"
#include "events.h"

static unsigned int score = 0;

void
scoreInit(void)
{
    score = 0;
    unsigned int value = score;
    eventEmit(EVENT_SCORE_CHANGED, &value);
}

void
scoreAddPoints(unsigned int points)
{
    score += points;
    unsigned int value = score;
    eventEmit(EVENT_SCORE_CHANGED, &value);
}

#ifdef UNIT_TESTING
void
helperUT_scoreReset(void)
{
    score = 0;
}

unsigned int
helperUT_scoreGetScore(void)
{
    return score;
}
#endif /* UNIT_TESTING */
