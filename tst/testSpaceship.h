#ifndef __TESTSPACESHIP_H__
#define __TESTSPACESHIP_H__

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdbool.h>

void
testSpaceshipCreate(void **status);

void
testSpaceshipGetSpriteFail(void **status);

void
testSpaceshipGetSpriteSuccess(void **status);

void
testSpaceshipPrintFail(void **status);

#endif
