#ifndef _ASYNC_H
#define _ASYNC_H

#include "types.h"

#define MAX_QUEUE_SIZE 100

typedef bool (*AsyncMethod)(void);

typedef struct {
    AsyncMethod asyncMethods[MAX_QUEUE_SIZE];
} AsyncMethodStack;

#endif