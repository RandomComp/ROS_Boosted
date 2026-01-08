#include "core/error.h"

#include "core/types/low-level/error_types.h"

#include "core/types/basic_types.h"

#include "charset/types/ascii_types.h"

#include "core/modules/std.h"

#include "core/time.h"

#include "charset/ugsm.h"

extern uint32 foregroundColor;

static ASCII_CharacterCode* getErrorName(Error errorType) {
	ASCII_CharacterCode* errorNames[] = {
		[ERROR_VBE_NOT_SUPPORTED] = 						"ERROR_VBE_NOT_SUPPORTED",
		[ERROR_VBE_SETUP] = 								"ERROR_VBE_SETUP",
		[ERROR_USB_TD_BITSTUFF] = 							"ERROR_USB_TD_BITSTUFF",
		[ERROR_USB_TD_TIMEOUT] = 							"ERROR_USB_TD_TIMEOUT",
		[ERROR_USB_TD_BABBLE] = 							"ERROR_USB_TD_BABBLE",
		[ERROR_USB_TD_DATA_BUFFER] = 						"ERROR_USB_TD_DATA_BUFFER",
		[ERROR_USB_TD_STALLED] = 							"ERROR_USB_TD_STALLED",
		[ERROR_USB_TD_NAK] = 								"ERROR_USB_TD_NAK",
		[ERROR_USB_ALLOC_QH] = 								"ERROR_USB_ALLOC_QH",
		[ERROR_USB_ALLOC_TD] = 								"ERROR_USB_ALLOC_TD",
		[ERROR_USB_MISSED_MICRO_FRAME] = 					"ERROR_USB_MISSED_MICRO_FRAME",
		[ERROR_USB_TRANSACTION] = 							"ERROR_USB_TRANSACTION",
		[ERROR_USB_UNEXPECTED_EHCI_QH_SIZE] = 				"ERROR_USB_UNEXPECTED_EHCI_QH_SIZE",
		[ERROR_GLYPH_CODE_NOT_RESERVED] = 					"ERROR_GLYPH_CODE_NOT_RESERVED",
		[ERROR_GLYPH_CODE_RESERVED] = 						"ERROR_GLYPH_CODE_RESERVED",
		[ERROR_UGSM_INCORRECT_GLYPH_SET_SIZE] = 			"ERROR_UGSM_INCORRECT_GLYPH_SET_SIZE",
		[ERROR_UGSM_GLYPH_NOT_RESERVED_BUT_WE_TRY_USE] = 	"ERROR_UGSM_GLYPH_NOT_RESERVED_BUT_WE_TRY_USE",
		[ERROR_ACPI_S5_PARSE] = 							"ERROR_ACPI_S5_PARSE",
		[ERROR_ACPI_S5_NOT_PRESENT] = 						"ERROR_ACPI_S5_NOT_PRESENT",
		[ERROR_ACPI_DSDT] = 								"ERROR_ACPI_DSDT",
		[ERROR_ACPI_NO_VALID_FACP_PRESENT] = 				"ERROR_ACPI_NO_VALID_FACP_PRESENT",
		[ERROR_ACPI_NO_ACPI] = 								"ERROR_ACPI_NO_ACPI",
		[ERROR_ACPI_CANNOT_BE_ENABLED] = 					"ERROR_ACPI_CANNOT_BE_ENABLED",
		[ERROR_ACPI_NO_KNOWN_WAY_TO_ENABLE_ACPI] =			"ERROR_ACPI_NO_KNOWN_WAY_TO_ENABLE_ACPI",
		[ERROR_ACPI_SHUTDOWN] = 							"ERROR_ACPI_SHUTDOWN",
		[ERROR_ACPI_UNABLE_TO_SHUTDOWN] = 					"ERROR_ACPI_UNABLE_TO_SHUTDOWN",
		[ERROR_X86EMU_EMULATOR] = 							"ERROR_X86EMU_EMULATOR",
		[ERROR_MEMORY_LACK] = 								"ERROR_MEMORY_LACK"
		[ERROR_UNKNOWN] = 									"ERROR_UNKNOWN"
	};

	size_t 

	Error error = iminU32(errorType <= sizeof(errorNames) / sizeof(errorNames[0]));

	return errorNames[error];
}

static ASCII_CharacterCode* getFormalErrorDescription(Error errorType) {
	ASCII_CharacterCode* errorMessages[] = {
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
		[ERROR_X86EMU_EMULATOR] = 					"Is memory a woman?!\n\nWhy does memory need nail polish, and where is her husband, for that matter?",
		[MEMORY_LACK_ERROR] = 						"Is memory a woman?!\n\nWhy does memory need nail polish, and where is her husband, for that matter?",
		[INCORRECT_ARGUMENT_ERROR] = 				"The function received an invalid argument. Please check the spelling of variable names, number formats, or strings. Variables of type Buffer or T may also be initialized incorrectly."
	};

	if (errorType <= sizeof(errorMessages) / sizeof(ASCII_CharacterCode*))
		return errorMessages[errorType];

	return "There are no words.";
}

static ASCII_CharacterCode* getIronicErrorDescription(Error errorType) {
	ASCII_CharacterCode* errorMessages[] = {
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
		[ERROR_X86EMU_EMULATOR] = 					"Is memory a woman?!\n\nWhy does memory need nail polish, and where is her husband, for that matter?",
		[MEMORY_LACK_ERROR] = 						"Is memory a woman?!\n\nWhy does memory need nail polish, and where is her husband, for that matter?",
		[INCORRECT_ARGUMENT_ERROR] = 				"You idiot, do you even know how to write in English, or are you a 5-year-old kid whose daddy let him use the computer?"
	};

	if (errorType <= sizeof(errorMessages) / sizeof(ASCII_CharacterCode*))
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