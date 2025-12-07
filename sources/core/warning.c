#include "core/warning.h"

#include "core/types.h"

#include "core/std.h"

#include "core/time.h"

#include "drivers/high-level/pit.h"

#include "drivers/high-level/speaker.h"

#include "charset/colors.h"

extern uint32 foregroundColor;

int8* getWarningDescription(WarningsType warningType) {
	int8* warningMessages[] = {
		[USBBabbleDetectedWarning] = 			"What? One more time. I don't understand what you're mumbling. \n\nMy friend taught me how to talk to my USB port, so now I have to mess with it for days without understanding it...\n\n",
		[AllGlyphsAreReservedWarning] = 		"Dude, everything is booked, what can we do, we'll come tomorrow :(\n\n",
		[RequiredNumberOfArgumentsNotReached] = "So wait, where's everything else?! ( The required number of arguments has not been reached )"
	};

	if (warningType < sizeof(warningMessages) / sizeof(int8*))
		return warningMessages[warningType];

	return "There are no words. ( Unknown warning type )\n\n";
}

void warn(WarningsType warningType) {
	TimeInit();

	uint16 tempForegroundColor = foregroundColor;

	foregroundColor = 0xffff00;

	UGSMASCIIputString(getWarningDescription(warningType));

	foregroundColor = tempForegroundColor;

	swap();

	for (uint8 i = 0; i < 4; i++) {
		makeSound(100);

		sleepMilliseconds(500);

		makeSound(500);

		sleepMilliseconds(500);
	}

	stopSound();
}