#ifndef __TESTPHYSIC_H__
#define __TESTPHYSIC_H__ 

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "physic.h"

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
testPhysicCheckCeillingCollisionNullParameter(void **status);

void
testPhysicCheckCeillingCollisionTrue(void **status);

void
testPhysicCheckCeillingCollisionFalse(void **status);

#endif
