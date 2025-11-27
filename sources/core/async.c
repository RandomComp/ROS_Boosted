#include "core/async.h"

#include "core/types.h"

AsyncMethods asyncMethods = { 0 };

uint16 addOffset = 0, callingPos = 0;

void ASYNCTick() {
    AsyncMethod currentAsyncMethod = asyncMethods.asyncMethods[callingPos];

    if (currentAsyncMethod != 0) {
        currentAsyncMethod();

        asyncMethods.asyncMethods[callingPos] = 0;

        callingPos++;
    }
}

void ASYNCaddAsyncMethod(AsyncMethod method) {
    asyncMethods.asyncMethods[addOffset] = method;

    addOffset++;

    if (addOffset >= MAX_QUEUE_SIZE - 1) {
        // wait for asyncMethods going to empty
    }
}