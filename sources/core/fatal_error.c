#include "core/fatal_error.h"

#include "core/types.h"

#include "core/std.h"

#include "charset/ugsm.h"

#include "charset/colors.h"

extern uint16 y;

extern uint32 foregroundColor;

int8* getFatalErrorDescription(FatalErrorsType errorType) {
	int8* errorMessages[] = {
		[DebugError] = 						"Where are we? in debugging.\n\n",
		[DivisionByZeroError] = 			"You has divided any number by zero, you get infinity and error to gift :).\n\n",
		[NonMaskableInterruptError] = 		"Hello non maskable interrupt, i've been looking for you!\n\n",
		[BreakPoint] = 						"Let's break everything, we're rich!\n\n",
		[StackOverflowError] = 				"Look what you've done, you've poured it all over...\n\n",
		[IndexOverpowered] = 				"Where are you going?! My memory!\n\n",
		[InvalidInstruction] = 				"Why did you break my brain?\n\n",
		[NoCoprocessorError] = 				"Only for the smart, dsjidjsdisidsudi, the dumb won't understand.\n\n",
		[DoubleFaultError] = 				"Monsieur, it seems to me that you and I have split up!\n\n",
		[CoprocessorSegmentOverflowError] = "You write incorrectly instead of \"CoprocessorSegmentOverflowError\" write \"StackOverflow\", give birth to idiots...\n\n",
		[StackError] = 						"The same mistake, STOP WRITING WITHOUT \"OVERFLOW\"!!!\n\n",
		[ProtectionError] = 				"Stop, it's the police, why are you breaking the law?\n\n",
		[PageError] = 						"Wait, where are you flipping through, you passed by our page!\n\n",
		[UnknownInterruptError] = 			"Wait, where are you rushing to, this is not our number.\n\n",
		[CoprocessorError] = 				"Stop being smart, I can't do that, I'm having a glitch!\n\n",
		[AlignmentError] = 					"Straighten up! We have an important matter!\n\n",
		[MachineCheckError] = 				"Careful... AHHH, IT HURTS!\n\n",
		[ReservedError] = 					"Go away, this place is reserved!\n\n",
		[ISRReservedError] = 				"Go away, ISR is reserved!\n\n"
	};

	if (errorType <= sizeof(errorMessages) / sizeof(int8*))
		return errorMessages[errorType];

	return "There are no words.\n\n";
}

void causeFatal(FatalErrorsType errorType) {
	uint16 tempForegroundColor = foregroundColor;

	foregroundColor = 0xff0000;

	UGSMASCIIputString(getFatalErrorDescription(errorType));

	foregroundColor = tempForegroundColor;

	swap();

	for (;;);
}