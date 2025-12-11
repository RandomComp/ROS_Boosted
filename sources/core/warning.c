#include "core/warning.h"

#include "core/types.h"

#include "core/std.h"

#include "core/time.h"

#include "drivers/high-level/pit.h"

#include "drivers/high-level/speaker.h"

#include "charset/colors.h"

extern uint32 foregroundColor;

int8* getIronicWarningDescription(WarningType warningType) {
	int8* ironicWarningMessages[] = {
		[USBBabbleDetectedWarning] = 					"What? One more time. I don't understand what you're mumbling. \n\nMy friend taught me how to talk to my USB port, so now I have to mess with it for days without understanding it...",
		[AllGlyphsAreReservedWarning] = 				"Dude, everything is booked, what can we do, we'll come tomorrow :(",
		[RequiredNumberOfArgumentsNotReachedWarning] = 	"So wait, where's everything else?!"
	};

	if (warningType >= 0 && warningType < sizeof(ironicWarningMessages) / sizeof(int8*))
		return ironicWarningMessages[warningType];

	return "Oh fuck, we don't know anything about this warning, sorry! ( Unknown warning type )";
}

int8* getFormalWarningDescription(WarningType warningType) {
	int8* formalWarningMessages[] = {
		[USBBabbleDetectedWarning] = 					"An unwanted USB device mumbling has been detected.",
		[AllGlyphsAreReservedWarning] = 				"The UGSM encoding is full, so it cannot add the requested glyph.",
		[RequiredNumberOfArgumentsNotReachedWarning] = 	"The required number of arguments in the function was not reached."
	};

	if (warningType >= 0 && warningType < sizeof(formalWarningMessages) / sizeof(int8*))
		return formalWarningMessages[warningType];

	return "There are no words. ( Unknown warning type )";
}

void warn(WarningType warningType) {
	TimeInit();

	uint16 tempForegroundColor = foregroundColor;

	foregroundColor = 0xffff00;

	UGSMASCIIputString(getIronicWarningDescription(warningType));

	UGSMASCIIputString("\n\n");

	UGSMASCIIputString(getFormalWarningDescription(warningType));

	foregroundColor = tempForegroundColor;

	swap();

	for (uint8 i = 0; i < 5; i++) {
		makeSound(100);

		sleepMilliseconds(500);

		makeSound(500);

		sleepMilliseconds(500);
	}

	stopSound();
}