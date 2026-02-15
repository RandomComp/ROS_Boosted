#include "tasks/async/asyncio.h"

#include "core/basic_types.h"

#include "tasks/async/asyncio_types.h"

#include "tasks/async/asyncio_fwd.h"

#include "std/std.h"

#include "drivers/memory/ram.h"

static Awaiter* awaiters[MAX_QUEUE_SIZE] = { nullptr };

static int32 callingPos = 0;

bool AsyncIO_isAwaiterValid(Awaiter* awaiter) {
	return 	awaiter &&
			awaiter->method &&
			awaiter->bActive;
}

bool AsyncIO_isAwaiterActive(Awaiter* awaiter) {
	return 	AsyncIO_isAwaiterValid(awaiter) && 
			awaiter->id != 0 && 
			!awaiter->bFinished;
}

static inline Awaiter* getMethodByID(size_t id) {
	if (id >= MAX_QUEUE_SIZE) return nullptr;

	return awaiters[id];
}

static void freeInactiveMethods() {
	size_t id = getInactiveMethodIndexAfter(0);

	while (id < MAX_QUEUE_SIZE) {
		awaiters[id] = nullptr;

		id = getInactiveMethodIndexAfter(id + 1);
	}
}

static size_t getActiveMethodIndexAfter(size_t pos) {
	size_t result = pos;

	while (!AsyncIO_isAwaiterActive(getMethodByID(result))) {
		result++;

		if (result >= MAX_QUEUE_SIZE)
			return MAX_QUEUE_SIZE;
	}

	return result;
}

static size_t getInactiveMethodIndexAfter(size_t afterPos) {
	size_t result = afterPos;

	while (AsyncIO_isAwaiterActive(getMethodByID(result))) {
		result++;

		if (result >= MAX_QUEUE_SIZE)
			return MAX_QUEUE_SIZE;
	}

	return result;
}

Awaiter* AsyncIO_newAwaiter(AsyncIO_Method method) {
	if (method == nullptr) {
		klog(LOG_SEVERITY_ERROR, "Create new awaiter failure: requested method is nullptr");

		return nullptr;
	}

	Awaiter* result = malloc(sizeof(Awaiter));

	if (result == nullptr) {
		klog(LOG_SEVERITY_CRITICAL, 
			"Create new awaiter failure: malloc for awaiter"
			"returned nullptr (out of memory)"
		);

		return nullptr;
	}

	result->method = method;

	result->bActive = true;
	result->bFinished = false;

	result->id = 0;

	return result;
}

void AsyncIO_free(Awaiter* awaiter) {
	free(awaiter);
}

void* AsyncIO_getArgs(Awaiter* this) {
	if (!AsyncIO_isAwaiterValid(this)) {
		klog(LOG_SEVERITY_ERROR, "Argument getting failure: awaiter invalid");

		return nullptr;
	}

	return this->args;
}

ErrorCode AsyncIO_setArgs(Awaiter* this, void* args) {
	if (!AsyncIO_isAwaiterValid(this)) {
		klog(LOG_SEVERITY_ERROR, "Argument setting failure: awaiter invalid");

		return CODE_FAIL;
	}

	this->args = args;

	return CODE_OK;
}

ErrorCode AsyncIO_return(Awaiter* this, void* result) {
	if (!AsyncIO_isAwaiterActive(this)) {
		klog(LOG_SEVERITY_ERROR, "AsyncIO return failure: awaiter is not active or invalid.");
		
		return CODE_FAIL;
	}

	this->bFinished = true;

	this->result = result;

	return CODE_OK;
}

ErrorCode AsyncIO_getResult(Awaiter* this, void** result) {
	if (!AsyncIO_isAwaiterActive(this) || this->bFinished == false)
		return CODE_FAIL;

	*result = this->result;

	return CODE_OK;
}

ErrorCode AsyncIO_callback(Awaiter* this) {
	if (!AsyncIO_isAwaiterActive(this)) return CODE_FAIL;

	if (this->callback == nullptr) {
		klog(LOG_SEVERITY_ERROR, "Callback from awaiter failure: callback is nullptr");

		return CODE_FAIL;
	}

	this->callback(this);

	return CODE_OK;
}

ErrorCode AsyncIO_start(Awaiter* awaiter) {
	if (!AsyncIO_isAwaiterValid(awaiter)) {
		klog(LOG_SEVERITY_ERROR, "Awaiter start failure: awaiter is nullptr");

		return CODE_FAIL;
	}

	word id = getInactiveMethodIndexAfter(0);

	if (id >= MAX_QUEUE_SIZE) {
		klog(LOG_SEVERITY_ERROR, "Awaiter start failure: no free space for awaiter");

		return CODE_FAIL;
	}

	awaiters[id] = awaiter;

	awaiter->id = id;

	return CODE_OK;
}

ErrorCode AsyncIO_handleAwaiter() {
	size_t id = getActiveMethodIndexAfter(callingPos);

	if (id >= MAX_QUEUE_SIZE) {
		klog(LOG_SEVERITY_INFO, "There are no asynchronous methods to handle since "
			"everything has already been handled");

		freeInactiveMethods();

		callingPos = 0;

		return CODE_OK;
	}

	Awaiter* awaiter = awaiters[id];

	awaiter->method(awaiter);

	if (awaiter->error == CODE_FAIL) {
		awaiter->bFinished = true;

		return CODE_FAIL;
	}

	callingPos++;

	return CODE_OK;
}

ErrorCode AsyncIO_await(Awaiter* awaiter) {
	if (!AsyncIO_isAwaiterActive(awaiter)) {
		klog(LOG_SEVERITY_ERROR, "AsyncIO await failure: awaiter is not active or invalid");
			
		return CODE_FAIL;
	}

	ErrorCode code = AsyncIO_start(awaiter);

	if (code == CODE_FAIL) {
		klog(LOG_SEVERITY_ERROR, "AsyncIO await failure: AsyncIO_start for awaiter returned CODE_FAIL");
			
		return CODE_FAIL;
	}

	while (!awaiter->bFinished) {
		AsyncIO_handleAwaiter();
	}

	if (awaiter->error == CODE_FAIL)
		AsyncIO_free(awaiter);

	return awaiter->error;
}