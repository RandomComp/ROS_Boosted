#ifndef _RANDOM_OS_EXCEPTION_TYPES_H
#define _RANDOM_OS_EXCEPTION_TYPES_H

#include "core/types/basic_types.h"

#include "core/types/low-level/warning_types.h"

#include "core/types/low-level/error_types.h"

#include "core/modules/types/exception.h"

#include "charset/types/ascii_types.h"

#define EXCEPTION_FIRST_TYPE EXCEPTION_TYPE_WARNING

#define EXCEPTION_LAST_TYPE EXCEPTION_TYPE_ERROR

typedef enum ExceptionType {
	EXCEPTION_TYPE_WARNING,
	EXCEPTION_TYPE_ERROR
} ExceptionType;

typedef struct Exception {
	ExceptionType exceptionType;

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

#endif