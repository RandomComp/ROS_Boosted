#ifndef _RANDOM_OS_EXCEPTION_TYPES_H
#define _RANDOM_OS_EXCEPTION_TYPES_H

#include "core/basic_types.h"

#include "exceptions/warnings/warning_types.h"

#include "exceptions/errors/error_types.h"

#define EXCEPTION_FIRST_TYPE EXCEPTION_TYPE_WARNING

#define EXCEPTION_LAST_TYPE EXCEPTION_TYPE_ERROR

typedef enum ExceptionType {
	EXCEPTION_TYPE_WARNING,
	EXCEPTION_TYPE_ERROR
} ExceptionType;

typedef struct Exception {
	ExceptionType type;

	union {
		Warning warning;
		Error error;
	} value;

	ExceptionMessage message;
} Exception;

typedef struct ExceptionMessage {
	c_str moduleName;
	uint32 line;
	c_str why;
} ExceptionMessage;

#endif