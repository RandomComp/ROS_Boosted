#ifndef _RANDOM_OS_WARNING_H
#define _RANDOM_OS_WARNING_H

#include "core/types.h"

typedef enum WarningType {
	USB_BABBLE_DETECTED_WARNING,

	ALL_GLYPHS_ARE_RESERVED_WARNING,

	REQUIRED_NUMBER_OF_ARGUMENTS_NOT_REACHED_WARNING,

	UNKNOWN_T_TYPE_WARNING
} WarningType;

int8* getIronicWarningDescription(WarningType warningType);

int8* getFormalWarningDescription(WarningType warningType);

void warn(WarningType warningType);

#endif