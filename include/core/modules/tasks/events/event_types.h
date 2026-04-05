#ifndef _R_OS_EVENT_TYPES_H
#define _R_OS_EVENT_TYPES_H

#include "core/basic_types.h"

struct EventHandler {
	void (*handler)(void* context);
};

struct Event {
	struct EventHandler* handlers;

	size_t handler_count;
};

#endif