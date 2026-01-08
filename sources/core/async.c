#include "core/async.h"

#include "core/types/basic_types.h"

AsyncMethods asyncMethods = { 0 };

uint16 addOffset = 0, callingPos = 0;

void asyncHandle() {
    AsyncMethod currentAsyncMethod = asyncMethods.asyncMethods[callingPos];

    if (currentAsyncMethod != 0)
        currentAsyncMethod();

    asyncMethods.asyncMethods[callingPos] = 0;

    callingPos++;
}

void asyncAddAsyncMethod(AsyncMethod method) {
    if (asyncMethods.asyncMethods[addOffset] == 0) {
        asyncMethods.asyncMethods[addOffset] = method;

        addOffset++;

        addOffset = addOffset % MAX_QUEUE_SIZE;
    }
}