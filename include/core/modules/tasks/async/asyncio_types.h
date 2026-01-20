#ifndef _RANDOM_OS_ASYNC_TYPES_H
#define _RANDOM_OS_ASYNC_TYPES_H

#include "core/basic_types.h"

struct Awaiter {
	// Required:

	void (*method)(struct Awaiter* self); // Asynchronous method itself
	
	bool bActive; // Flag for check if method in activity

	bool bFinished; // Flag if task is finished

	// Optional:

	void* args; // args, nullptr if no args

	void* result; // Result of task, nullptr if result has void type

	void (*callback)(struct Awaiter* self); // Called when task is finished, nullptr if no callback
};

#endif