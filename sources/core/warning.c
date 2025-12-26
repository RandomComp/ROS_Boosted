#include "core/warning.h"

#include "core/types.h"

#include "core/std.h"

#include "core/time.h"

#include "drivers/high-level/pit.h"

#include "drivers/high-level/speaker.h"

extern uint32 foregroundColor;

static const CP437_CharacterCode* getWarningName(Warning warningType) {
	CP437_CharacterCode* warningNames[] = {
		[USB_BABBLE_DETECTED_WARNING] = 						"USB_BABBLE_DETECTED_WARNING",
		[ALL_GLYPHS_ARE_RESERVED_WARNING] = 					"ALL_GLYPHS_ARE_RESERVED_WARNING",
		[REQUIRED_NUMBER_OF_ARGUMENTS_NOT_REACHED_WARNING] = 	"REQUIRED_NUMBER_OF_ARGUMENTS_NOT_REACHED_WARNING",
		[UNKNOWN_T_TYPE_WARNING] = 								"UNKNOWN_T_TYPE_WARNING",
		[FUNCTION_NOT_IMPLEMENTED_WARNING] = 					"FUNCTION_NOT_IMPLEMENTED_WARNING",
		[INVALID_ARGUMENT_WARNING] = 							"INCORRECT_ARGUMENT_WARNING",
	};

	if (warningType >= 0 && warningType < sizeof(warningNames) / sizeof(int8*))
		return warningNames[warningType];

	return "UNKNOWN_WARNING.";
}

static const ASCII_CharacterCode* getIronicWarningDescription(Warning warningType) {
	ASCII_CharacterCode* ironicWarningMessages[] = {
		[USB_BABBLE_DETECTED_WARNING] = 						"What? One more time. I don't understand what you're mumbling. \n\nMy friend taught me how to talk to my USB port, so now I have to mess with it for days without understanding it...",
		[ALL_GLYPHS_ARE_RESERVED_WARNING] = 					"Dude, everything is booked, what can we do, we'll come tomorrow :(",
		[REQUIRED_NUMBER_OF_ARGUMENTS_NOT_REACHED_WARNING] = 	"So wait, where's everything else?!",
		[UNKNOWN_T_TYPE_WARNING] = 								"Fuck, man, what kind of type is this in T? I don't know shit!"
		[FUNCTION_NOT_IMPLEMENTED_WARNING] = 					"Dude, what the fuck are you trying to call function? I don't have that function, so don't call it again until you get your head knocked off!",
		[INVALID_ARGUMENT_WARNING] = 							""
	};

	if (warningType >= 0 && warningType < sizeof(ironicWarningMessages) / sizeof(CP437_CharacterCode*))
		return ironicWarningMessages[warningType];

	return "Oh fuck, we don't know anything about this warning, sorry!";
}

static const CP437_CharacterCode* getFormalWarningDescription(Warning warningType) {
	CP437_CharacterCode* formalWarningMessages[] = {
		[USB_BABBLE_DETECTED_WARNING] = 						"An unwanted USB device mumbling has been detected.",
		[ALL_GLYPHS_ARE_RESERVED_WARNING] = 					"The UGSM encoding is full, so it cannot add the requested glyph.",
		[REQUIRED_NUMBER_OF_ARGUMENTS_NOT_REACHED_WARNING] = 	"The required number of arguments in the function was not reached.",
		[UNKNOWN_T_TYPE_WARNING] = 								"Unknown type T, code execution will continue, but pay attention to this. Data corruption is possible.",
		[FUNCTION_NOT_IMPLEMENTED_WARNING] = 					"The function you are trying to call is not implemented."
		[INVALID_ARGUMENT_WARNING] = 							""
	};

	if (warningType >= 0 && warningType < sizeof(formalWarningMessages) / sizeof(CP437_CharacterCode*))
		return formalWarningMessages[warningType];

	return "There are no words.";
}

void Warning_warn(Warning warningType, CP437_CharacterCode* details) {
	TimeInit();

	uint16 tempForegroundColor = foregroundColor;

	printf("[yellow]Ironic warning description: \n%s[white]\n\n", getIronicWarningDescription(warningType));

	printf("[yellow]Formal warning description: \n\n%s[white]\n", getFormalWarningDescription(warningType));

	printf("[yellow]Warning name: %s[white]\n", getWarningName(warningType));

	foregroundColor = tempForegroundColor;

	swap();
}