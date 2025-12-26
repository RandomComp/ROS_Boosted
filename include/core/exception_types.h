#ifndef _RANDOM_OS_EXCEPTION_TYPES_H
#define _RANDOM_OS_EXCEPTION_TYPES_H

#include "charset/ascii_types.h"

#define Exception_messageFromString(why) (Exception_newMessage(__FILE__, __LINE__, why))

typedef struct Exception {
	enum {
		EXCEPTION_TYPE_WARNING,
		EXCEPTION_TYPE_ERROR
	} exceptionType;

	union {
		Warning warning;
		Error error;
	} value;

	ExceptionMessage message;
} Exception;

typedef struct ExceptionMessage {
	const ASCII_CharacterCode* moduleName;
	uint32 line;
	const ASCII_CharacterCode* why;
} ExceptionMessage;

inline ExceptionMessage Exception_newMessage(CP437_CharacterCode* moduleName, uint32 line, CP437_CharacterCode* why) {
	return (ExceptionMessage){ .moduleName = moduleName, .line = line, .why = why };
}

inline Exception Exception_fromWarning(Warning warning, ExceptionMessage message) {
	Exception result = { 0 };

	result.exceptionType = EXCEPTION_TYPE_WARNING;

	result.value.warning = warning;

	result.message = message;
	
	return result;
}

inline Exception Exception_fromError(Error error, ExceptionMessage message) {
	Exception result = { 0 };

	result.exceptionType = EXCEPTION_TYPE_ERROR;

	result.value.error = error;

	result.message = message;
	
	return result;
}

#endif