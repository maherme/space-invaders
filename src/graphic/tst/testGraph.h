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

void
testGraphMoveImageFail(void ** status);

void
testGraphMoveImageWrongDirection(void ** status);

void
testGraphMoveImageRight(void ** status);

void
testGraphMoveImageRightMax(void ** status);

void
testGraphMoveImageLeft(void ** status);

void
testGraphMoveImageLeftMax(void ** status);

void
testGraphMoveImageTooEarlyToMove(void ** status);

#endif
