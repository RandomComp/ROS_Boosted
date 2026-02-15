#include "exceptions/errors/error.h"

#include "core/basic_types.h"

#include "std/std.h"

#include "exceptions/exception_types.h"

#include "time/time.h"

#include "math/math.h"

#include "charset/ugsm/ugsm_types.h"

static const c_str getErrorName(Error errorType) {
	const c_str errorNames[] = {
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

	Error error = minU32(ERROR_LAST, errorType);

	return errorNames[error];
}

static const c_str getFormalErrorDescription(Error errorType) {
	const c_str errorMessages[] = {
		[ERROR_VBE_NOT_SUPPORTED] = 						"Your video card does not support VBE 2.0 ( go fuck yourself, it's not our fault here :) )",
		[ERROR_VBE_SETUP] = 								"And now we've fucked up, I'm sorry, but you know, fuck you!",
		[ERROR_USB_TD_BITSTUFF] = 							"You broke the USB again, HOW MUCH CAN you DO? I'VE ALREADY STARTED PAYING FOR IT.",
		[ERROR_USB_TD_TIMEOUT] = 							"The free period of your USB is over, will you pay for the subscription?",
		[ERROR_USB_TD_BABBLE] = 							"Why did you stick gum to my USB?!",
		[ERROR_USB_TD_DATA_BUFFER] = 						"What are you doing?! have you lost the USB information?! COME HERE, YOU BASTARD!!!",
		[ERROR_USB_TD_STALLED] = 							"Well, it's all over for us, the USB CAUGHT FIRE!!!",
		[ERROR_USB_TD_NAK] = 								"Wait, what did you do? How did you teach my USB to speak?!",
		[ERROR_USB_ALLOC_QH] = 								"Why did you BREAK MY USB?!?!?!",
		[ERROR_USB_ALLOC_TD] = 								"I don't know what funny mistakes to make anymore, I'm sorry. :( in short -- USB 1.1 allocation TD error",
		[ERROR_USB_MISSED_MICRO_FRAME] = 					"OH FUCK!",
		[ERROR_USB_TRANSACTION] = 							"A forbidden joke, in short USBTransactionError!",
		[ERROR_USB_UNEXPECTED_EHCI_QH_SIZE] = 				"This is a big USB device! Not big like this message :)",
		[ERROR_GLYPH_CODE_NOT_RESERVED] = 					"What? What other crab is not reserved?",
		[ERROR_GLYPH_CODE_RESERVED] = 						"Everything seems to be OK, or not...",
		[ERROR_UGSM_INCORRECT_GLYPH_SET_SIZE] = 			"Why are there so many of your crabs?! Now it's my turn :)",
		[ERROR_UGSM_GLYPH_NOT_RESERVED_BUT_WE_TRY_USE] = 	"Hey, there's nothing there!",
		[ERROR_ACPI_S5_PARSE] = 							"Why parse samsung s5? Really dumb?",
		[ERROR_ACPI_S5_NOT_PRESENT] = 						"What kind of junk is this?\n\nWhat did you give me?\n\nNo matter what, I'll throw it away better than I'll use it.",
		[ERROR_ACPI_DSDT] = 								"What?\n\nWhat kind of obscenity is this?",
		[ERROR_ACPI_NO_VALID_FACP_PRESENT] = 				"What's it? We don't have a hospital here, we have an operating system here! Get out!",
		[ERROR_ACPI_NO_ACPI] = 								"Wait, WHAT?!",
		[ERROR_ACPI_CANNOT_BE_ENABLED] = 					"No way, I hid the ACPI power button with tape :)",
		[ERROR_ACPI_NO_KNOWN_WAY_TO_ENABLE_ACPI] =			"What, how the fuck do I turn this on?",
		[ERROR_ACPI_SHUTDOWN] = 							"Oh, come on, I glued the fucking off button!",
		[ERROR_ACPI_UNABLE_TO_SHUTDOWN] = 					"Fuck, what the hell is wrong with the power button?",
		[ERROR_X86EMU_EMULATOR] = 							"Is memory a woman?!\n\nWhy does memory need nail polish, and where is her husband, for that matter?",
		[ERROR_MEMORY_LACK] = 								"Is memory a woman?!\n\nWhy does memory need nail polish, and where is her husband, for that matter?",
		[ERROR_UNKNOWN] = 									"The function received an invalid argument. Please check the spelling of variable names, number formats, or strings. Variables of type Buffer or T may also be initialized incorrectly."
	};

	Error error = minU32(ERROR_LAST, errorType);

	return errorMessages[error];
}

static const c_str getIronicErrorDescription(Error errorType) {
	const c_str errorMessages[] = {
		[ERROR_VBE_NOT_SUPPORTED] = 						"Your video card does not support VBE 2.0 ( go fuck yourself, it's not our fault here :) )",
		[ERROR_VBE_SETUP] = 								"And now we've fucked up, I'm sorry, but you know, fuck you!",
		[ERROR_USB_TD_BITSTUFF] = 							"You broke the USB again, HOW MUCH CAN you DO? I'VE ALREADY STARTED PAYING FOR IT.",
		[ERROR_USB_TD_TIMEOUT] = 							"The free period of your USB is over, will you pay for the subscription?",
		[ERROR_USB_TD_BABBLE] = 							"Why did you stick gum to my USB?!",
		[ERROR_USB_TD_DATA_BUFFER] = 						"What are you doing?! have you lost the USB information?! COME HERE, YOU BASTARD!!!",
		[ERROR_USB_TD_STALLED] = 							"Well, it's all over for us, the USB CAUGHT FIRE!!!",
		[ERROR_USB_TD_NAK] = 								"Wait, what did you do? How did you teach my USB to speak?!",
		[ERROR_USB_ALLOC_QH] = 								"Why did you BREAK MY USB?!?!?!",
		[ERROR_USB_ALLOC_TD] = 								"I don't know what funny mistakes to make anymore, I'm sorry. :( in short -- USB 1.1 allocation TD error",
		[ERROR_USB_MISSED_MICRO_FRAME] = 					"OH FUCK!",
		[ERROR_USB_TRANSACTION] = 							"An unethical joke about a politician, in short USBTransactionError! ( P.S this joke about trade relations between Russia and the USA )",
		[ERROR_USB_UNEXPECTED_EHCI_QH_SIZE] = 				"This is a big USB device! Not big like this message :)",
		[ERROR_GLYPH_CODE_NOT_RESERVED] = 					"What? What other crab is not reserved?",
		[ERROR_GLYPH_CODE_RESERVED] = 						"Everything seems to be OK, or not...",
		[ERROR_UGSM_INCORRECT_GLYPH_SET_SIZE] = 			"Why are there so many of your crabs?! Now it's my turn :)",
		[ERROR_UGSM_GLYPH_NOT_RESERVED_BUT_WE_TRY_USE] = 	"Hey, there's nothing there!",
		[ERROR_ACPI_S5_PARSE] = 							"Why parse samsung s5? Really dumb?",
		[ERROR_ACPI_S5_NOT_PRESENT] = 						"What kind of junk is this?\n\nWhat did you give me?\n\nNo matter what, I'll throw it away better than I'll use it.",
		[ERROR_ACPI_DSDT] = 								"What?\n\nWhat kind of obscenity is this?",
		[ERROR_ACPI_NO_VALID_FACP_PRESENT] = 				"What's it? We don't have a hospital here, we have an operating system here! Get out!",
		[ERROR_ACPI_NO_ACPI] = 								"Wait, WHAT?!",
		[ERROR_ACPI_CANNOT_BE_ENABLED] = 					"No way, I hid the ACPI power button with tape :)",
		[ERROR_ACPI_NO_KNOWN_WAY_TO_ENABLE_ACPI] =			"What, how the fuck do I turn this on?",
		[ERROR_ACPI_SHUTDOWN] = 							"Oh, come on, I glued the fucking off button!",
		[ERROR_ACPI_UNABLE_TO_SHUTDOWN] = 					"Fuck, what the hell is wrong with the power button?",
		[ERROR_X86EMU_EMULATOR] = 							"Is memory a woman?!\n\nWhy does memory need nail polish, and where is her husband, for that matter?",
		[ERROR_MEMORY_LACK] = 								"Is memory a woman?!\n\nWhy does memory need nail polish, and where is her husband, for that matter?",
		[ERROR_UNKNOWN] = 									"Wait... Oh shit!"
	};

	Error error = minU32(ERROR_LAST, errorType);

	return errorMessages[error];
}

void Error_throw(Error errorType, ExceptionMessage message) {
	kprintf("[fg: red]Ironic error description:\n[value: c_str]\n\n", getIronicErrorDescription(errorType));

	kprintf("[fg: red]Formal error description:\n[value: c_str]\n\n", getFormalErrorDescription(errorType));

	kprintf("[fg: red]Error name: [value: c_str]\n", getErrorName(errorType));

	kprintf("Press any key to continue... ");

	swap();

	getch();
}