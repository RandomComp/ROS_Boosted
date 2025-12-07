#include "core/error.h"

#include "core/types.h"

#include "core/std.h"

#include "core/time.h"

#include "core/math.h"

#include "drivers/high-level/pit.h"

#include "drivers/high-level/speaker.h"

#include "charset/ugsm.h"

#include "charset/colors.h"

extern uint32 foregroundColor;

int8* getErrorDescription(ErrorType errorType) {
	int8* errorMessages[] = {
		[VBENotSupportedError] = 			"Your video card does not support VBE 2.0 ( go fuck yourself, it's not our fault here :) )\n\n",
		[VBESetupError] = 					"And now we've fucked up, I'm sorry, but you know, fuck you!\n\n",
		[USBTDBitstuffError] = 				"You broke the USB again, HOW MUCH CAN you DO? I'VE ALREADY STARTED PAYING FOR IT.\n\n",
		[USBTDTimeoutError] = 				"The free period of your USB is over, will you pay for the subscription?\n\n",
		[USBTDBabbleError] = 				"Why did you stick gum to my USB?!\n\n",
		[USBTDDataBufferError] = 			"What are you doing?! have you lost the USB information?! COME HERE, YOU BASTARD!!!\n\n",
		[USBTDStalledError] = 				"Well, it's all over for us, the USB CAUGHT FIRE!!!\n\n",
		[USBTDNAKError] = 					"Wait, what did you do? How did you teach my USB to speak?!\n\n",
		[USBAllocQHError] = 				"Why did you BREAK MY USB?!?!?!\n\n",
		[USBAllocTDError] = 				"I don't know what funny mistakes to make anymore, I'm sorry. :( in short -- USB 1.1 allocation TD error\n\n",
		[USBMissedMicroFrameError] = 		"OH FUCK!",
		[USBTransactionError] = 			"A forbidden joke, in short USBTransactionError!\n\n",
		[USBUnexpectedEHCIQHSize] = 		"This is a big USB device! Not big like this message :)\n\n",
		[GlyphNotReservedError] = 			"What? What other crab is not reserved?\n\n",
		[GlyphReservedError] = 				"Everything seems to be OK, or not...\n\n",
		[UGSMIncorrectGlyphSetSizeError] = 	"Why are there so many of your crabs?! Now it's my turn :)\n\n",
		[UGSMGlyphNotReservedButWeTryUse] = "Hey, there's nothing there!\n\n",
		[ACPIS5ParseError] = 				"Why parse samsung s5? Really dumb?\n\n",
		[ACPIS5NotPresentError] = 			"What kind of junk is this?\n\nWhat did you give me?\n\nNo matter what, I'll throw it away better than I'll use it.\n\n",
		[ACPIDSDTError] = 					"What?\n\nWhat kind of obscenity is this?\n\n",
		[ACPINoValidFACPPresentError] = 	"What's it? We don't have a hospital here, we have an operating system here! Get out!\n\n",
		[ACPINoACPIError] = 				"Wait, WHAT?!\n\n",
		[ACPICannotBeEnabledError] = 		"No way, I hid the ACPI power button with tape :)\n\n",
		[ACPINoKnownWayToEnableACPIError] = "What, how the fuck do I turn this on?\n\n",
		[ACPIShutdownError] = 				"Oh, come on, I glued the fucking off button!",
		[ACPIUnableToShutdownError] = 		"Fuck, what the hell is wrong with the power button?",
		[MemoryLackError] = 				"Is memory a woman?!\n\nWhy does memory need nail polish, and where is her husband, for that matter?\n\n"
	};

	if (errorType <= sizeof(errorMessages) / sizeof(int8*))
		return errorMessages[errorType];

	return "There are no words.\n\n";
}

void cause(ErrorType errorType) {
	TimeInit();

	uint16 tempForegroundColor = foregroundColor;

	foregroundColor = 0xff0000;

	UGSMASCIIputString(getErrorDescription(errorType));

	foregroundColor = tempForegroundColor;

	swap();

	for (uint16 i = 0; i < 500; i++) {
		uint16 temp = (i % 100) * 10;

		makeSound(fabs(temp - 500) + 1000);

		sleepMilliseconds(10);
	}

	for (;;);
}