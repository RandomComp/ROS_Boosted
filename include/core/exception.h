#ifndef _RANDOM_OS_EXCEPTION_H
#define _RANDOM_OS_EXCEPTION_H

#include "core/warning.h"

#include "core/error.h"

#include "core/fatal_error.h"

#include "charset/cp437.h"

inline void throw(Exception exception) {
	switch (exception.exceptionType) {
		case EXCEPTION_TYPE_WARNING:
			Warning_warn(exception.value.warning, exception.message);
		break;

		case EXCEPTION_TYPE_ERROR:
			Error_throw(exception.value.error, exception.message);
		break;
		
		default:
			Error_throw(UNKNOWN_ERROR, exception.message);
		break;
	}

	// TODO: Сделать стэк Exception'ов, и добавлять туда при вызове throw
}
/*
@param expr Условие, которое проверяет указанное условие на true, если true, то вызов указанного исключения.
@param exception Параметр, определяющий исключение для вызова при верном указанным условием.
@brief Функция проверяет, верно ли указанное условие, если да, то вызывает указанное исключение, если нет -- вызов пропускается

@return Возвращает указанное условие для дальнейшей проверки.
*/
inline bool assert(bool expr, Exception exception) {
	if (expr == false) return expr;

	if (!Exception_isValidException(exception)) {
		throw(Exception_fromError(INVALID_ARGUMENT_ERROR, Exception_messageFromString("An invalid exception was passed.")));

		return expr;
	}

	throw(exception);

	return expr;
}

#endif