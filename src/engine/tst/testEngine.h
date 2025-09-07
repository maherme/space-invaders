#ifndef __TESTENGINE_H__
#define __TESTENGINE_H__

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "engine.h"

int
setup(void ** state);

void
testEngineRegisterFailNullParameter(void ** status);

void
testEngineRegisterFailMaxCallbacks(void ** status);

void
testEngineRegisterSuccess(void ** status);

void
testEngineRun(void ** status);

#endif
