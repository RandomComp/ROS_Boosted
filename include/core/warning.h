#ifndef _RANDOM_OS_WARNING_H
#define _RANDOM_OS_WARNING_H

#include "core/types.h"

#include "charset/cp437.h"

typedef enum Warning {
	USB_BABBLE_DETECTED_WARNING,
	ALL_GLYPHS_ARE_RESERVED_WARNING,
	REQUIRED_NUMBER_OF_ARGUMENTS_NOT_REACHED_WARNING,
	UNKNOWN_T_TYPE_WARNING,
	FUNCTION_NOT_IMPLEMENTED_WARNING,
	INVALID_ARGUMENT_WARNING,
	UNKNOWN_WARNING
} Warning;

void Warning_warn(Warning warningType, ExceptionMessage message);

#endif