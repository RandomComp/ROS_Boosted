#include "core/error.h"

#include "core/error_types.h"

#include "core/types.h"

#include "core/std.h"

#include "core/time.h"

#include "charset/ugsm.h"

extern uint32 foregroundColor;

static CP437_CharacterCode* getErrorName(Error errorType) {
	CP437_CharacterCode* errorNames[] = {
		[VBE_NOT_SUPPORTED_ERROR] = 				"VBE_NOT_SUPPORTED_ERROR",
		[VBE_SETUP_ERROR] = 						"VBE_SETUP_ERROR",
		[USB_TD_BITSTUFF_ERROR] = 					"USB_TD_BITSTUFF_ERROR",
		[USB_TD_TIMEOUT_ERROR] = 					"USB_TD_TIMEOUT_ERROR",
		[USB_TD_BABBLE_ERROR] = 					"USB_TD_BABBLE_ERROR",
		[USB_TD_DATA_BUFFER_ERROR] = 				"USB_TD_DATA_BUFFER_ERROR",
		[USB_TD_STALLED_ERROR] = 					"USB_TD_STALLED_ERROR",
		[USB_TD_NAK_ERROR] = 						"USB_TD_NAK_ERROR",
		[USB_ALLOC_QH_ERROR] = 						"USB_ALLOC_QH_ERROR",
		[USB_ALLOC_TD_ERROR] = 						"USB_ALLOC_TD_ERROR",
		[USB_MISSED_MICRO_FRAME_ERROR] = 			"USB_MISSED_MICRO_FRAME_ERROR",
		[USB_TRANSACTION_ERROR] = 					"USB_TRANSACTION_ERROR",
		[USB_UNEXPECTED_EHCI_QH_SIZE] = 			"USB_UNEXPECTED_EHCI_QH_SIZE",
		[GLYPH_CODE_NOT_RESERVED_ERROR] = 			"GLYPH_CODE_NOT_RESERVED_ERROR",
		[GLYPH_CODE_RESERVED_ERROR] = 				"GLYPH_CODE_RESERVED_ERROR",
		[UGSM_INCORRECT_GLYPH_SET_SIZE_ERROR] = 	"UGSM_INCORRECT_GLYPH_SET_SIZE_ERROR",
		[UGSM_GLYPH_NOT_RESERVED_BUT_WE_TRY_USE] = 	"UGSM_GLYPH_NOT_RESERVED_BUT_WE_TRY_USE",
		[ACPI_S5_PARSE_ERROR] = 					"ACPI_S5_PARSE_ERROR",
		[ACPI_S5_NOT_PRESENT_ERROR] = 				"ACPI_S5_NOT_PRESENT_ERROR",
		[ACPI_DSDT_ERROR] = 						"ACPI_DSDT_ERROR",
		[ACPI_NO_VALID_FACP_PRESENT_ERROR] = 		"ACPI_NO_VALID_FACP_PRESENT_ERROR",
		[ACPI_NO_ACPI_ERROR] = 						"ACPI_NO_ACPI_ERROR",
		[ACPI_CANNOT_BE_ENABLED_ERROR] = 			"ACPI_CANNOT_BE_ENABLED_ERROR",
		[ACPI_NO_KNOWN_WAY_TO_ENABLE_ACPI_ERROR] =	"ACPI_NO_KNOWN_WAY_TO_ENABLE_ACPI_ERROR",
		[ACPI_SHUTDOWN_ERROR] = 					"ACPI_SHUTDOWN_ERROR",
		[ACPI_UNABLE_TO_SHUTDOWN_ERROR] = 			"ACPI_UNABLE_TO_SHUTDOWN_ERROR",
		[X16_BIT_EMULATOR_ERROR] = 					"X16_BIT_EMULATOR_ERROR",
		[MEMORY_LACK_ERROR] = 						"MEMORY_LACK_ERROR"
	};

	if (errorType <= sizeof(errorNames) / sizeof(CP437_CharacterCode*))
		return errorNames[errorType];

	return "UNKNOWN_ERROR";
}

static CP437_CharacterCode* getFormalErrorDescription(Error errorType) {
	CP437_CharacterCode* errorMessages[] = {
		[VBE_NOT_SUPPORTED_ERROR] = 				"Your video card does not support VBE 2.0 ( go fuck yourself, it's not our fault here :) )",
		[VBE_SETUP_ERROR] = 						"And now we've fucked up, I'm sorry, but you know, fuck you!",
		[USB_TD_BITSTUFF_ERROR] = 					"You broke the USB again, HOW MUCH CAN you DO? I'VE ALREADY STARTED PAYING FOR IT.",
		[USB_TD_TIMEOUT_ERROR] = 					"The free period of your USB is over, will you pay for the subscription?",
		[USB_TD_BABBLE_ERROR] = 					"Why did you stick gum to my USB?!",
		[USB_TD_DATA_BUFFER_ERROR] = 				"What are you doing?! have you lost the USB information?! COME HERE, YOU BASTARD!!!",
		[USB_TD_STALLED_ERROR] = 					"Well, it's all over for us, the USB CAUGHT FIRE!!!",
		[USB_TD_NAK_ERROR] = 						"Wait, what did you do? How did you teach my USB to speak?!",
		[USB_ALLOC_QH_ERROR] = 						"Why did you BREAK MY USB?!?!?!",
		[USB_ALLOC_TD_ERROR] = 						"I don't know what funny mistakes to make anymore, I'm sorry. :( in short -- USB 1.1 allocation TD error",
		[USB_MISSED_MICRO_FRAME_ERROR] = 			"OH FUCK!",
		[USB_TRANSACTION_ERROR] = 					"A forbidden joke, in short USBTransactionError!",
		[USB_UNEXPECTED_EHCI_QH_SIZE] = 			"This is a big USB device! Not big like this message :)",
		[GLYPH_CODE_NOT_RESERVED_ERROR] = 			"What? What other crab is not reserved?",
		[GLYPH_CODE_RESERVED_ERROR] = 				"Everything seems to be OK, or not...",
		[UGSM_INCORRECT_GLYPH_SET_SIZE_ERROR] = 	"Why are there so many of your crabs?! Now it's my turn :)",
		[UGSM_GLYPH_NOT_RESERVED_BUT_WE_TRY_USE] = 	"Hey, there's nothing there!",
		[ACPI_S5_PARSE_ERROR] = 					"Why parse samsung s5? Really dumb?",
		[ACPI_S5_NOT_PRESENT_ERROR] = 				"What kind of junk is this?\n\nWhat did you give me?\n\nNo matter what, I'll throw it away better than I'll use it.",
		[ACPI_DSDT_ERROR] = 						"What?\n\nWhat kind of obscenity is this?",
		[ACPI_NO_VALID_FACP_PRESENT_ERROR] = 		"What's it? We don't have a hospital here, we have an operating system here! Get out!",
		[ACPI_NO_ACPI_ERROR] = 						"Wait, WHAT?!",
		[ACPI_CANNOT_BE_ENABLED_ERROR] = 			"No way, I hid the ACPI power button with tape :)",
		[ACPI_NO_KNOWN_WAY_TO_ENABLE_ACPI_ERROR] =	"What, how the fuck do I turn this on?",
		[ACPI_SHUTDOWN_ERROR] = 					"Oh, come on, I glued the fucking off button!",
		[ACPI_UNABLE_TO_SHUTDOWN_ERROR] = 			"Fuck, what the hell is wrong with the power button?",
		[X16_BIT_EMULATOR_ERROR] = 					"Is memory a woman?!\n\nWhy does memory need nail polish, and where is her husband, for that matter?",
		[MEMORY_LACK_ERROR] = 						"Is memory a woman?!\n\nWhy does memory need nail polish, and where is her husband, for that matter?",
		[INCORRECT_ARGUMENT_ERROR] = 				"The function received an invalid argument. Please check the spelling of variable names, number formats, or strings. Variables of type Buffer or T may also be initialized incorrectly."
	};

	if (errorType <= sizeof(errorMessages) / sizeof(CP437_CharacterCode*))
		return errorMessages[errorType];

	return "There are no words.";
}

static CP437_CharacterCode* getIronicErrorDescription(Error errorType) {
	CP437_CharacterCode* errorMessages[] = {
		[VBE_NOT_SUPPORTED_ERROR] = 				"Your video card does not support VBE 2.0 ( go fuck yourself, it's not our fault here :) )",
		[VBE_SETUP_ERROR] = 						"And now we've fucked up, I'm sorry, but you know, fuck you!",
		[USB_TD_BITSTUFF_ERROR] = 					"You broke the USB again, HOW MUCH CAN you DO? I'VE ALREADY STARTED PAYING FOR IT.",
		[USB_TD_TIMEOUT_ERROR] = 					"The free period of your USB is over, will you pay for the subscription?",
		[USB_TD_BABBLE_ERROR] = 					"Why did you stick gum to my USB?!",
		[USB_TD_DATA_BUFFER_ERROR] = 				"What are you doing?! have you lost the USB information?! COME HERE, YOU BASTARD!!!",
		[USB_TD_STALLED_ERROR] = 					"Well, it's all over for us, the USB CAUGHT FIRE!!!",
		[USB_TD_NAK_ERROR] = 						"Wait, what did you do? How did you teach my USB to speak?!",
		[USB_ALLOC_QH_ERROR] = 						"Why did you BREAK MY USB?!?!?!",
		[USB_ALLOC_TD_ERROR] = 						"I don't know what funny mistakes to make anymore, I'm sorry. :( in short -- USB 1.1 allocation TD error",
		[USB_MISSED_MICRO_FRAME_ERROR] = 			"OH FUCK!",
		[USB_TRANSACTION_ERROR] = 					"An unethical joke about a politician, in short USBTransactionError! ( P.S this joke about trade relations between Russia and the USA )",
		[USB_UNEXPECTED_EHCI_QH_SIZE] = 			"This is a big USB device! Not big like this message :)",
		[GLYPH_CODE_NOT_RESERVED_ERROR] = 			"What? What other crab is not reserved?",
		[GLYPH_CODE_RESERVED_ERROR] = 				"Everything seems to be OK, or not...",
		[UGSM_INCORRECT_GLYPH_SET_SIZE_ERROR] = 	"Why are there so many of your crabs?! Now it's my turn :)",
		[UGSM_GLYPH_NOT_RESERVED_BUT_WE_TRY_USE] = 	"Hey, there's nothing there!",
		[ACPI_S5_PARSE_ERROR] = 					"Why parse samsung s5? Really dumb?",
		[ACPI_S5_NOT_PRESENT_ERROR] = 				"What kind of junk is this?\n\nWhat did you give me?\n\nNo matter what, I'll throw it away better than I'll use it.",
		[ACPI_DSDT_ERROR] = 						"What?\n\nWhat kind of obscenity is this?",
		[ACPI_NO_VALID_FACP_PRESENT_ERROR] = 		"What's it? We don't have a hospital here, we have an operating system here! Get out!",
		[ACPI_NO_ACPI_ERROR] = 						"Wait, WHAT?!",
		[ACPI_CANNOT_BE_ENABLED_ERROR] = 			"No way, I hid the ACPI power button with tape :)",
		[ACPI_NO_KNOWN_WAY_TO_ENABLE_ACPI_ERROR] =	"What, how the fuck do I turn this on?",
		[ACPI_SHUTDOWN_ERROR] = 					"Oh, come on, I glued the fucking off button!",
		[ACPI_UNABLE_TO_SHUTDOWN_ERROR] = 			"Fuck, what the hell is wrong with the power button?",
		[X16_BIT_EMULATOR_ERROR] = 					"Is memory a woman?!\n\nWhy does memory need nail polish, and where is her husband, for that matter?",
		[MEMORY_LACK_ERROR] = 						"Is memory a woman?!\n\nWhy does memory need nail polish, and where is her husband, for that matter?",
		[INCORRECT_ARGUMENT_ERROR] = 				"You idiot, do you even know how to write in English, or are you a 5-year-old kid whose daddy let him use the computer?"
	};

	if (errorType <= sizeof(errorMessages) / sizeof(CP437_CharacterCode*))
		return errorMessages[errorType];

	return "Wait... Oh shit!";
}

void Error_throw(Error errorType, ExceptionMessage message) {
	TimeInit();

	uint16 tempForegroundColor = foregroundColor;

	UGSMASCIIputString("[red]Ironic error description:\n");

	UGSMASCIIputString(getIronicErrorDescription(errorType));

	UGSMASCIIputString("\n\nFormal error description:\n");

	UGSMASCIIputString(getFormalErrorDescription(errorType));

	UGSMASCIIputString("\n\nError name:\n");

	UGSMASCIIputString(getErrorName(errorType));

	UGSMASCIIputString("\n[white]");

	foregroundColor = tempForegroundColor;

	UGSMASCIIputString("Press any key to continue... ");

	swap();

	getch();
}