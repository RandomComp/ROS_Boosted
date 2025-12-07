#ifndef _WARNING_H
#define _WARNING_H

#include "core/types.h"

typedef enum WarningsType {
	USBBabbleDetectedWarning = 0,

	AllGlyphsAreReservedWarning = 1,

	RequiredNumberOfArgumentsNotReached = 2
} WarningsType;

int8* getWarningDescription(enum WarningsType warningType);

void warn(enum WarningsType warningType);

#endif