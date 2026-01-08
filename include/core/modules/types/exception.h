#ifndef _RANDOM_OS_EXCEPTION_H
#define _RANDOM_OS_EXCEPTION_H

#include "core/types/basic_types.h"

#include "core/types/low-level/warning_types.h"

#include "core/types/low-level/error_types.h"

#include "core/types/low-level/isr_error_types.h"

#include "core/types/high-level/exception_types.h"

#define Exception_messageFromString(why) (Exception_newMessage(__FILE__, __LINE__, why))
/// @brief 
/// @param moduleName 
/// @param line 
/// @param why 
/// @return 
static inline ExceptionMessage Exception_newMessage(const ASCII_CharacterCode* moduleName, uint32 line, const ASCII_CharacterCode* why) {
	return (ExceptionMessage){ .moduleName = moduleName, .line = line, .why = why };
}

static inline Exception Exception_fromWarning(Warning warning, ExceptionMessage message) {
	Exception result = { 0 };

	result.exceptionType = EXCEPTION_TYPE_WARNING;

	result.value.warning = warning;

	result.message = message;
	
	return result;
}

static inline Exception Exception_fromError(Error error, ExceptionMessage message) {
	assert();

	Exception result = { 0 };

	result.exceptionType = EXCEPTION_TYPE_ERROR;

	result.value.error = error;

	result.message = message;
	
	return result;
}

static inline void throw(Exception exception) {
	switch (exception.exceptionType) {
		case EXCEPTION_TYPE_WARNING:
			Warning_throw(exception.value.warning, exception.message);
		break;

		case EXCEPTION_TYPE_ERROR:
			Error_throw(exception.value.error, exception.message);
		break;
		
		default:
			Error_throw(ERROR_UNKNOWN, exception.message);
		break;
	}

	// TODO: Сделать стэк Exception'ов, и добавлять туда при вызове throw
}
static inline bool Exception_isValidExceptionType(ExceptionType exceptionType) {
	return exceptionType
}
static inline bool Exception_isValidException(Exception exception) {
	return exception.exceptionType
}
/*
@param expr Условие, которое проверяет указанное условие на true, если true, то вызов указанного исключения.
@param exception Параметр, определяющий исключение для вызова при верном указанным условием.
@brief Функция проверяет, верно ли указанное условие, если да, то вызывает указанное исключение, если нет -- вызов пропускается

@return Возвращает указанное условие для дальнейшей проверки.
*/
static inline bool assert(bool expr, Exception exception) {
	if (expr == true) return expr;

	if (!Exception_isValidException(exception)) {
		throw(Exception_fromError(ERROR_INVALID_ARGUMENT, Exception_messageFromString("An invalid exception was passed.")));

		return expr;
	}

	throw(exception);

	return expr;
}

#endif