#include "exceptions/warnings/warning.h"

#include "exceptions/warnings/warning_types.h"

#include "core/basic_types.h"

#include "std/std.h"

#include "time/time.h"

#include "math/math.h"

#include "drivers/time/pit.h"

#include "drivers/sound/speaker.h"

extern uint32 foregroundColor;

static c_str getWarningName(Warning warningType) {
	const c_str warningNames[] = {
		[WARNING_USB_BABBLE_DETECTED] = 						"WARNING_USB_BABBLE_DETECTED",
		[WARNING_ALL_GLYPHS_ARE_RESERVED] = 					"WARNING_ALL_GLYPHS_ARE_RESERVED",
		[WARNING_REQUIRED_NUMBER_OF_ARGUMENTS_NOT_REACHED] = 	"WARNING_REQUIRED_NUMBER_OF_ARGUMENTS_NOT_REACHED",
		[WARNING_UNKNOWN_T_TYPE] = 								"WARNING_UNKNOWN_T_TYPE",
		[WARNING_FUNCTION_NOT_IMPLEMENTED] = 					"WARNING_FUNCTION_NOT_IMPLEMENTED",
		[WARNING_INVALID_ARGUMENT] = 							"WARNING_INVALID_ARGUMENT",
	};

	if (warningType >= 0 && warningType < sizeof(warningNames) / sizeof(int8*))
		return warningNames[warningType];

	return "WARNING_UNKNOWN";
}

static c_str getIronicWarningDescription(Warning warningType) {
	const c_str ironicWarningMessages[] = {
		[WARNING_USB_BABBLE_DETECTED] = 						"What? One more time. I don't understand what you're mumbling. \n\nMy friend taught me how to talk to my USB port, so now I have to mess with it for days without understanding it...",
		[WARNING_ALL_GLYPHS_ARE_RESERVED] = 					"Dude, everything is booked, what can we do, we'll come tomorrow :(",
		[WARNING_REQUIRED_NUMBER_OF_ARGUMENTS_NOT_REACHED] = 	"So wait, where's everything else?!",
		[WARNING_UNKNOWN_T_TYPE] = 								"Fuck, man, what kind of type is this in T? I don't know shit!"
		[WARNING_FUNCTION_NOT_IMPLEMENTED] = 					"Dude, what the fuck are you trying to call function? I don't have that function, so don't call it again until you get your head knocked off!",
		[WARNING_INVALID_ARGUMENT] = 							""
	};

	if (warningType >= 0 && warningType < sizeof(ironicWarningMessages) / sizeof(c_str))
		return ironicWarningMessages[warningType];

	return "Oh fuck, we don't know anything about this warning, sorry!";
}

static const c_str getFormalWarningDescription(Warning warningType) {
	const c_str formalWarningMessages[] = {
		[WARNING_USB_BABBLE_DETECTED] = 						"An unwanted USB device mumbling has been detected.",
		[WARNING_ALL_GLYPHS_ARE_RESERVED] = 					"The UGSM encoding is full, so it unable add the requested glyph.",
		[WARNING_REQUIRED_NUMBER_OF_ARGUMENTS_NOT_REACHED] = 	"The required number of arguments in the function was not reached.",
		[WARNING_UNKNOWN_T_TYPE] = 								"Unknown type T, code execution will continue, but pay attention to this. Data corruption is possible.",
		[WARNING_FUNCTION_NOT_IMPLEMENTED] = 					"The function you are trying to call is not implemented."
		[WARNING_INVALID_ARGUMENT] = 							""
	};

	if (inRangeU32(warningType, WARNING_FIRST, WARNING_LAST))
		return formalWarningMessages[warningType];

	return "There are no words.";
}

void Warning_warn(Warning warningType, c_str details) {
	if (!inRangeU32(warningType, WARNING_FIRST, WARNING_LAST))
		return formalWarningMessages[warningType];

	kprintf("[fg: yellow]Ironic warning description: \n[value: c_str]\n\n", getIronicWarningDescription(warningType));

	kprintf("[fg: yellow]Formal warning description: \n[value: c_str]\n\n", getFormalWarningDescription(warningType));

	kprintf("[fg: yellow]Warning name: [value: c_str]\n", getWarningName(warningType));

	swap();
}