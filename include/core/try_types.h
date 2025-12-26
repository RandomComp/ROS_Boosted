#ifndef _RANDOM_OS_TRY_TYPES_H
#define _RANDOM_OS_TRY_TYPES_H

#include "core/types.h"

#include "core/stack.h"

typedef struct ExceptionStack {
    Stack stack;
} ExceptionStack;

#endif