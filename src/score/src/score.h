/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __SCORE_H__
#define __SCORE_H__

void
scoreInit(void);

void
scoreAddPoints(unsigned int points);

#ifdef UNIT_TESTING
void
helperUT_scoreReset(void);

unsigned int
helperUT_scoreGetScore(void);
#endif /* UNIT_TESTING */

#endif /* __SCORE_H__ */
