#ifndef _R_OS_ASYNCIO_H
#define _R_OS_ASYNCIO_H

#include "core/basic_types.h"

#include "tasks/async/asyncio_fwd.h"

// Валидация
bool AsyncIO_is_awaiter_valid(Awaiter* awaiter);
bool AsyncIO_is_awaiter_active(Awaiter* awaiter);

// Управление памятью
Awaiter* AsyncIO_newAwaiter(AsyncIO_Method method);
void AsyncIO_free(Awaiter* awaiter);

bool AsyncIO_any_arg(Awaiter* this);

// Геттеры и сеттеры
void* AsyncIO_get_arg(Awaiter* this, size_t arg_number);
ErrorCode AsyncIO_set_arg(Awaiter* this, size_t arg_number, void* args);

void* AsyncIO_get_args(Awaiter* this);
ErrorCode AsyncIO_set_args(Awaiter* this, void* args);

ErrorCode AsyncIO_return(Awaiter* this, void* result);
ErrorCode AsyncIO_get_result(Awaiter* this, void** result);

// Вызов при завершении
ErrorCode AsyncIO_set_callback(Awaiter* this, AsyncIO_Method callback);

// Управление жизнью awaiter
ErrorCode AsyncIO_start(Awaiter* awaiter);
ErrorCode AsyncIO_loop();
ErrorCode AsyncIO_await(Awaiter* awaiter);

#endif