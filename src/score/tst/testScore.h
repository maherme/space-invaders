/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __TESTSCORE_H__
#define __TESTSCORE_H__

int
setup(void **status);

void
testScoreInit(void **status);

void
testScoreAddPoints(void **status);

#endif /* __TESTSCORE_H__ */
