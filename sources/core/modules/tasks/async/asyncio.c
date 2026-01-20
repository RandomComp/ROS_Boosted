#include "tasks/async/asyncio.h"

#include "tasks/async/asyncio_types.h"

#include "tasks/async/asyncio_fwd.h"

#include "exceptions/exception.h"

#include "core/basic_types.h"

static Awaiter awaiters[MAX_QUEUE_SIZE] = { 0 };

static int32 callingPos = 0;

static inline bool isMethodValid(Awaiter* awaiter) {
	return 	awaiter && 
			awaiter->method && 
			awaiter->bActive;
}

static inline bool isActiveMethod(Awaiter* awaiter) {
	return 	isMethodValid(awaiter) && 
			!awaiter->bFinished;
}

static inline Awaiter* getMethodByID(int32 id) {
	if (id <= -1) return 0;

	return &awaiters[id];
}

static void freeInactiveMethods() {
	int32 id = getInactiveMethodIndexAfter(0);

	while (id != -1) {
		awaiters[id] = (Awaiter){ 0 };

		id = getInactiveMethodIndexAfter(id + 1);
	}
}

static int32 getActiveMethodIndexAfter(int32 afterPos) {
	int32 result = afterPos;

	while (!isActiveMethod(getMethodByID(result))) {
		result++;

		if (result >= MAX_QUEUE_SIZE) return -1;
	}

	return result;
}

static int32 getInactiveMethodIndexAfter(int32 afterPos) {
	int32 result = afterPos;

	while (isActiveMethod(getMethodByID(result))) {
		result++;

		if (result >= MAX_QUEUE_SIZE) return -1;
	}

	return result;
}

void AsyncIO_handleAwaiter() {
	int32 methodID = getActiveMethodIndexAfter(callingPos);

	if (methodID == -1) {
		freeInactiveMethods();

		callingPos = 0;

		return;
	}

	Awaiter* awaiter = &awaiters[methodID];

	awaiter->method(awaiter);

	callingPos++;

	callingPos %= MAX_QUEUE_SIZE;
}

void AsyncIO_run(Awaiter* method) {
	if (!isMethodValid(method)) {
		throw(
			Exception_errorInvalidArgument(
				"Attempt to start an invalid awaiter ( asyncio method )."
			)
		);

		return;
	}

	int32 id = getInactiveMethodIndexAfter(0);

	// TODO: Добавить проверку

	Awaiter* awaiter = &awaiters[id];

	*awaiter = *method;

	return awaiter;
}

void AsyncIO_await(Awaiter* method) {
	Awaiter* awaiter = reserveNewAwaiter(method);

	while (!awaiter->bFinished) {
		AsyncIO_handleAwaiter();
	}
}