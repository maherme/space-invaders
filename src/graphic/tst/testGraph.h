#ifndef __TESTGRAPH_H__
#define __TESTGRAPH_H__

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include "graph.h"

void
testGraphCreateImageFail(void ** status);

void
testGraphCreateImageSuccess(void ** status);

void
testGraphPrintImageFail(void ** status);

void
testGraphPrintImageSuccess(void ** status);

#endif
