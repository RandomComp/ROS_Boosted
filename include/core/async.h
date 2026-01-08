#ifndef _ASYNC_H
#define _ASYNC_H

#include "core/types/basic_types.h"

#define MAX_QUEUE_SIZE 100

#define ASYNC_TICK_US 1 * 1000 // 1 MILLISECOND TICK

typedef bool (*AsyncMethod)(void);

typedef struct {
    AsyncMethod asyncMethods[MAX_QUEUE_SIZE];
} AsyncMethods;

void asyncHandle();

void asyncAddAsyncMethod(AsyncMethod method);

#endif