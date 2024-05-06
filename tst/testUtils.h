#ifndef __TESTUTILS_H__
#define __TESTUTILS_H__

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <errno.h>
#include <stdbool.h>
#include "utils.h"

void
testUtilsCallocFail(void **status);

void
testUtilsCallocSuccess(void **status);

#endif
