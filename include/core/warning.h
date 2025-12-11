#ifndef _WARNING_H
#define _WARNING_H

#include "core/types.h"

typedef enum WarningType {
	USBBabbleDetectedWarning,

	AllGlyphsAreReservedWarning,

	RequiredNumberOfArgumentsNotReachedWarning
} WarningType;

int8* getIronicWarningDescription(WarningType warningType);

int8* getFormalWarningDescription(WarningType warningType);

void warn(WarningType warningType);

#endif