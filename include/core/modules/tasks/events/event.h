#ifndef _RANDOM_OS_EVENT_H
#define _RANDOM_OS_EVENT_H

#include "tasks/events/event_fwd.h"

Event* Event_new();

void Event_subscribe(Event* event, EventHandler handler);

void Event_invoke(Event* event, void* context);

#endif