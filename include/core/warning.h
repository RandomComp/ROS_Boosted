#ifndef _WARNING_H
#define _WARNING_H

#include "core/types.h"

typedef enum WarningsType {
	USBBabbleDetectedWarning,

	AllGlyphsAreReservedWarning,

	RequiredNumberOfArgumentsNotReached
} WarningsType;

int8* getWarningDescription(WarningsType warningType);

void warn(WarningsType warningType);

#endif