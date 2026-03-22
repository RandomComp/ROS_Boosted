#include "tasks/async/asyncio.h"

#include "core/basic_types.h"

#include "tasks/async/asyncio_types.h"

#include "std/std.h"

#include "drivers/memory/ram.h"

static Awaiter* awaiters[MAX_QUEUE_SIZE] = { nullptr };

static int32 callingPos = 0;

bool AsyncIO_is_awaiter_valid(Awaiter* awaiter) {
	return 	awaiter &&
			awaiter->method &&
			awaiter->is_active;
}

bool AsyncIO_is_awaiter_active(Awaiter* awaiter) {
	return 	AsyncIO_is_awaiter_valid(awaiter) && 
			awaiter->id != 0 && 
			!awaiter->is_finished;
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

	while (!AsyncIO_is_awaiter_active(getMethodByID(result))) {
		result++;

		if (result >= MAX_QUEUE_SIZE)
			return MAX_QUEUE_SIZE;
	}

	return result;
}

static size_t getInactiveMethodIndexAfter(size_t afterPos) {
	size_t result = afterPos;

	while (AsyncIO_is_awaiter_active(getMethodByID(result))) {
		result++;

		if (result >= MAX_QUEUE_SIZE)
			return MAX_QUEUE_SIZE;
	}

	return result;
}

Awaiter* AsyncIO_newAwaiter(AsyncIO_Method method) {
	if (method == nullptr) {
		klog(LOG_ERROR, "Create new awaiter failure: requested method is nullptr");

		return nullptr;
	}

	Awaiter* result = malloc(sizeof(Awaiter));

	if (result == nullptr) {
		klog(LOG_CRITICAL, 
			"Create new awaiter failure: malloc for awaiter"
			"returned nullptr (out of memory)"
		);

		return nullptr;
	}

	result->method = method;

	result->is_active = true;
	result->is_finished = false;

	result->id = 0;

	return result;
}

void AsyncIO_free(Awaiter* awaiter) {
	free(awaiter);
}

bool AsyncIO_any_arg(Awaiter* this) {
	return this->args != nullptr && this->arg_cnt > 0;
}

size_t AsyncIO_arg_cnt(Awaiter* this) {
	if (this == nullptr || this->args == nullptr) return 0;

	return this->arg_cnt;
}

void* AsyncIO_get_arg(Awaiter* this, size_t arg_number) {
	if (!AsyncIO_is_awaiter_valid(this)) {
		klog(LOG_ERROR, "Argument getting failure: awaiter invalid");

		return nullptr;
	}

	if (this->args == nullptr) {
		klog(LOG_ERROR, "Argument getting failure: awaiter has not arguments");

		return nullptr;
	}

	if (arg_number >= this->arg_cnt) {
		klog(LOG_ERROR, "Argument getting failure: argument index overpowered");

		return nullptr;
	}

	return this->args[arg_number];
}

ErrorCode AsyncIO_set_arg(Awaiter* this, size_t arg_number, void* arg) {
	if (!AsyncIO_is_awaiter_valid(this)) {
		klog(LOG_ERROR, "Argument setting failure: awaiter invalid");

		return CODE_FAIL;
	}

	if (arg_number >= this->arg_cnt) {
		size_t new_size = this->arg_cnt * sizeof(void*);

		void* new_args = realloc(this->args, new_size);

		if (new_args == nullptr) {
			klog(LOG_CRITICAL, 
				"Argument setting failure: realloc for size [value: size] for "
				"Awaiter->args returned nullptr (out of memory)", new_size
			);

			return CODE_FAIL;
		}

		this->args = new_args;
	}

	this->args[arg_number] = arg;

	return CODE_OK;
}

void* AsyncIO_get_args(Awaiter* this) {
	if (!AsyncIO_is_awaiter_valid(this)) {
		klog(LOG_ERROR, "Arguments getting failure: awaiter invalid");

		return nullptr;
	}

	return this->args;
}

ErrorCode AsyncIO_set_args(Awaiter* this, void* args) {
	if (!AsyncIO_is_awaiter_valid(this)) {
		klog(LOG_ERROR, "Arguments setting failure: awaiter invalid");

		return CODE_FAIL;
	}

	this->args = args;

	return CODE_OK;
}

ErrorCode AsyncIO_set_callback(Awaiter* this, AsyncIO_Method callback) {
	if (this == nullptr) {
		klog(LOG_ERROR, "AsyncIO set callback failure: awaiter is nullptr");

		return CODE_FAIL;
	}

	if (callback == nullptr) {
		klog(LOG_ERROR, "AsyncIO set callback failure: callback is nullptr");

		return CODE_FAIL;
	}

	
}

ErrorCode AsyncIO_return(Awaiter* this, void* result) {
	if (this == nullptr) {
		klog(LOG_ERROR, "AsyncIO return failure: awaiter is not active or invalid.");
		
		return CODE_FAIL;
	}

	this->is_finished = true;
	this->result = result;

	if (this->callback)
		this->callback(this);

	return CODE_OK;
}

ErrorCode AsyncIO_get_result(Awaiter* this, void** result) {
	if (this == nullptr)
		return CODE_FAIL;

	*result = this->result;

	return CODE_OK;
}

ErrorCode AsyncIO_start(Awaiter* awaiter) {
	if (!AsyncIO_is_awaiter_valid(awaiter)) {
		klog(LOG_ERROR, "Awaiter start failure: awaiter is nullptr");

		return CODE_FAIL;
	}

	word id = getInactiveMethodIndexAfter(0);

	if (id >= MAX_QUEUE_SIZE) {
		klog(LOG_ERROR, "Awaiter start failure: no free space for awaiter");

		return CODE_FAIL;
	}

	awaiters[id] = awaiter;

	awaiter->id = id;

	return CODE_OK;
}

ErrorCode AsyncIO_loop() {
	size_t id = getActiveMethodIndexAfter(callingPos);

	if (id >= MAX_QUEUE_SIZE) {
		// klog(LOG_INFO, "There are no asynchronous methods to handle since "
		// 				"everything has already been handled");

		freeInactiveMethods();

		callingPos = 0;

		return CODE_OK;
	}

	Awaiter* awaiter = awaiters[id];

	awaiter->method(awaiter);

	if (awaiter->error == CODE_FAIL) {
		awaiter->is_finished = true;

		return CODE_FAIL;
	}

	callingPos++;

	return CODE_OK;
}

ErrorCode AsyncIO_await(Awaiter* awaiter) {
	if (!AsyncIO_is_awaiter_active(awaiter)) {
		klog(LOG_ERROR, "AsyncIO await failure: awaiter is not active or invalid");
			
		return CODE_FAIL;
	}

	ErrorCode code = AsyncIO_start(awaiter);

	if (code == CODE_FAIL) {
		klog(LOG_ERROR, "AsyncIO await failure: AsyncIO_start for awaiter returned CODE_FAIL");
			
		return CODE_FAIL;
	}

	while (!awaiter->is_finished && 
			awaiter->error == CODE_OK) {
		AsyncIO_loop();
	}

	return awaiter->error;
}