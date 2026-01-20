#include "tasks/events/event.h"

#include "tasks/events/event_types.h"

#include "exceptions/exception.h"

#include "drivers/memory/ram.h"

#include "builtins/mem.h"

static bool isEventActive(Event* event) {
	return 	event->handlers != 0 && 
			event->handler_count > 0;
}

static bool isEventHandlerActive(EventHandler handler) {
	return handler.handler != nullptr;
}

Event* Event_new() {
	Event* result = malloc(sizeof(Event), MEMORY_STATUS_ACTIVE);

	memset(result, 0, sizeof(Event));

	result->handler_count = 0;

	result->handlers = 0;

	return result;
}

void Event_subscribe(Event* event, EventHandler handler) {
	size_t index = event->handler_count;
	
	event->handler_count++;

	event->handlers = realloc(event->handlers, event->handler_count * sizeof(EventHandler));

	// TODO: Сделать проверку на то что realloc вернуло ли nullptr, и обработать

	event->handlers[index] = handler;
}

void Event_invoke(Event* event, void* context) {
	if (!isEventActive(event)) {
		throw(
			Exception_warningInvalidArgument(
				"Event is not valid or inactive."
			)
		);
	}

	for (uint32 i = 0; i < event->handler_count; i++) {
		EventHandler handler = event->handlers[i];

		if (isEventHandlerActive(handler))
			handler.handler(context);
	}
}