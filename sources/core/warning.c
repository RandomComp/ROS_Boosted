#include "core/warning.h"

#include "core/types.h"

#include "core/std.h"

#include "core/time.h"

#include "drivers/high-level/pit.h"

#include "drivers/high-level/speaker.h"

#include "charset/colors.h"

extern uint32 foregroundColor;

ASCIIGlyphCode* getWarningName(WarningType warningType) {
	ASCIIGlyphCode* warningNames[] = {
		[USB_BABBLE_DETECTED_WARNING] = 						"USB Babble detected warning.",
		[ALL_GLYPHS_ARE_RESERVED_WARNING] = 					"All Glyphs are reserved warning.",
		[REQUIRED_NUMBER_OF_ARGUMENTS_NOT_REACHED_WARNING] = 	"Required number of arguments not reached warning.",
		[UNKNOWN_T_TYPE_WARNING] = 								"Unknown T type warning."
	};

	if (warningType >= 0 && warningType < sizeof(warningNames) / sizeof(int8*))
		return warningNames[warningType];

	return "Unknown warning.";
}

ASCIIGlyphCode* getIronicWarningDescription(WarningType warningType) {
	ASCIIGlyphCode* ironicWarningMessages[] = {
		[USB_BABBLE_DETECTED_WARNING] = 						"What? One more time. I don't understand what you're mumbling. \n\nMy friend taught me how to talk to my USB port, so now I have to mess with it for days without understanding it...",
		[ALL_GLYPHS_ARE_RESERVED_WARNING] = 					"Dude, everything is booked, what can we do, we'll come tomorrow :(",
		[REQUIRED_NUMBER_OF_ARGUMENTS_NOT_REACHED_WARNING] = 	"So wait, where's everything else?!",
		[UNKNOWN_T_TYPE_WARNING] = 								"Fuck, man, what kind of type is this in T? I don't know shit!"
	};

	if (warningType >= 0 && warningType < sizeof(ironicWarningMessages) / sizeof(int8*))
		return ironicWarningMessages[warningType];

	return "Oh fuck, we don't know anything about this warning, sorry! ( Unknown warning type )";
}

ASCIIGlyphCode* getFormalWarningDescription(WarningType warningType) {
	ASCIIGlyphCode* formalWarningMessages[] = {
		[USB_BABBLE_DETECTED_WARNING] = 						"An unwanted USB device mumbling has been detected.",
		[ALL_GLYPHS_ARE_RESERVED_WARNING] = 					"The UGSM encoding is full, so it cannot add the requested glyph.",
		[REQUIRED_NUMBER_OF_ARGUMENTS_NOT_REACHED_WARNING] = 	"The required number of arguments in the function was not reached.",
		[UNKNOWN_T_TYPE_WARNING] = 								"Unknown type T, code execution will continue, but pay attention to this. Data corruption is possible."
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

	UGSMASCIIputString("\n\n");

	putString(newStringFromASCII("\n\n"));

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