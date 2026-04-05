#ifndef _R_OS_ASYNC_TYPES_H
#define _R_OS_ASYNC_TYPES_H

#include "core/basic_types.h"

#include "tasks/async/asyncio_fwd.h"

struct Awaiter {
	// Required:

	AsyncIO_Method method; // Asynchronous method itself
	
	bool is_active; // Flag for check if method in activity
	bool is_finished; // Flag if task is finished
	ErrorCode error;
	word id;

	// Optional:

	void** args; size_t arg_cnt;

	void* result; // Result of task, nullptr if result has void type

	AsyncIO_Method callback; // Called when task is finished, nullptr if no callback
};

#endif