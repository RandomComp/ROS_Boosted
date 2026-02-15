#include "tasks/events/event.h"

#include "tasks/events/event_types.h"

#include "exceptions/exception.h"

#include "drivers/memory/ram.h"

#include "builtins/mem.h"

Event* Event_new() {
	Event* result = malloc(sizeof(Event));

	if (result == nullptr) {
		throw(
			Exception_fromError(
				ERROR_MEMORY_LACK,
				"malloc(sizeof(Event)) returned nullptr, so memory lack"
			)
		);

		return nullptr;
	}

	memset(result, 0, sizeof(Event));

	result->handler_count = 0;

	result->handlers = 0;

	return result;
}

ErrorCode Event_subscribe(Event* event, EventHandler handler) {
	if (!isEventHandlerActive(handler)) {
		throw(
			Exception_errorInvalidArgument(
				"Event subscribe failed, because event handler is nullptr"
			)
		);

		return CODE_FAIL;
	}

	size_t new_handler_count = event->handler_count + 1;

	EventHandler* new_handlers = realloc(event->handlers, 
										new_handler_count * sizeof(EventHandler)
								);

	if (new_handlers == nullptr) {
		throw(
			Exception_fromError(
				ERROR_MEMORY_LACK,
				"Event subscribe failed, realloc "
				"returned nullptr, so memory lack"
			)
		);

		return CODE_FAIL;
	}

	event->handlers = new_handlers;

	event->handler_count = new_handler_count;

	event->handlers[event->handler_count - 1] = handler;

	return CODE_OK;
}

ErrorCode Event_invoke(const Event* event, void* context) {
	if (event == nullptr) {
		throw(
			Exception_errorInvalidArgument(
				"Event invoke failed: event is invalid or inactive."
			)
		);

		return CODE_FAIL;
	}

	if (event->handler_count == 0 || event->handlers == nullptr) {
		throw(
			Exception_warningInvalidArgument(
				"Event invoke failed: event has no handlers."
			)
		);

		return CODE_FAIL;
	}

	for (size_t i = 0; i < event->handler_count; i++) {
		EventHandler handler = event->handlers[i];

		if (handler.handler)
			handler.handler(context);
	}

	return CODE_OK;
}