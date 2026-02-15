#ifndef _RANDOM_OS_EVENT_H
#define _RANDOM_OS_EVENT_H

#include "core/basic_types.h"

#include "tasks/events/event_fwd.h"

Event* Event_new();

ErrorCode Event_subscribe(Event* event, EventHandler handler);

ErrorCode Event_invoke(const Event* event, void* context);

#endif