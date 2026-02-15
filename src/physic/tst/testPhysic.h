/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Manuel Hernández Méndez
 *
 * Authors:
 *   Manuel Hernández Méndez <maherme.dev@gmail.com>
 */

#ifndef __TESTPHYSIC_H__
#define __TESTPHYSIC_H__

#include "physic.h"
#include <cmocka.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

void
testPhysicMoveSpriteFail(void **status);

void
testPhysicMoveSpriteWrongDirection(void **status);

void
testPhysicMoveSpriteRight(void **status);

void
testPhysicMoveSpriteRightMax(void **status);

void
testPhysicMoveSpriteLeft(void **status);

void
testPhysicMoveSpriteLeftMax(void **status);

void
testPhysicMoveSpriteUp(void **status);

void
testPhysicMoveSpriteUpMax(void **status);

void
testPhysicMoveSpriteTooEarlyToMove(void **status);

void
testPhysicCheckBorderCollisionNullParameter(void **status);

void
testPhysicCheckBorderCollisionUpTrue(void **status);

void
testPhysicCheckBorderCollisionRightTrue(void **status);

void
testPhysicCheckBorderCollisionLeftTrue(void **status);

void
testPhysicCheckBorderCollisionFalse(void **status);

void
testPhysicCheckSpriteBoxCollisionNullParameters(void **status);

void
testPhysicCheckSpriteBoxCollisionFalse(void **status);

#endif /* __TESTPHYSIC_H__ */
