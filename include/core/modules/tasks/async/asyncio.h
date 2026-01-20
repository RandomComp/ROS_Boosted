#ifndef _RANDOM_OS_ASYNCIO_H
#define _RANDOM_OS_ASYNCIO_H

#include "core/basic_types.h"

#include "tasks/async/asyncio_fwd.h"

void AsyncIO_handleAwaiter();

void AsyncIO_run(Awaiter* method);

void AsyncIO_await(Awaiter* method);

#endif