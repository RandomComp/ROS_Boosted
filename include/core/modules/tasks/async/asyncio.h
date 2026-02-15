#ifndef _RANDOM_OS_ASYNCIO_H
#define _RANDOM_OS_ASYNCIO_H

#include "core/basic_types.h"

#include "tasks/async/asyncio_fwd.h"

// Валидация
bool AsyncIO_isAwaiterValid(Awaiter* awaiter);
bool AsyncIO_isAwaiterActive(Awaiter* awaiter);

// Управление памятью
Awaiter* AsyncIO_newAwaiter(AsyncIO_Method method);
void AsyncIO_free(Awaiter* awaiter);

// Геттеры и сеттеры
void* AsyncIO_getArgs(Awaiter* this);
ErrorCode AsyncIO_setArgs(Awaiter* this, void* args);
ErrorCode AsyncIO_return(Awaiter* this, void* result);
ErrorCode AsyncIO_getResult(Awaiter* this, void** result);

// Вызов при завершении
ErrorCode AsyncIO_callback(Awaiter* this);

// Управление жизнью awaiter
ErrorCode AsyncIO_start(Awaiter* awaiter);
ErrorCode AsyncIO_handleAwaiter();
ErrorCode AsyncIO_await(Awaiter* awaiter);

#endif