#include "core/fatal_error.h"

#include "core/types.h"

#include "core/std.h"

#include "charset/ugsm.h"

#include "charset/colors.h"

extern uint16 y;

extern uint32 foregroundColor;

int8* getIronicFatalErrorDescription(FatalErrorType errorType) {
	int8* errorMessages[] = {
		[DIVISION_BY_ZERO_FATAL_ERROR] = 				"You has divided any number by zero, you get infinity and error to gift :).\n\n",
		[DEBUG_FATAL_ERROR] = 							"Where are we? in debugging.",
		[NON_MASKABLE_INTERRUPT_FATAL_ERROR] = 			"Hello non maskable interrupt, i've been looking for you!\n\n",
		[BREAK_POINT_FATAL_ERROR] = 					"Let's break everything, we're rich!\n\n",
		[STACK_OVERFLOW_FATAL_ERROR] = 					"Look what you've done, you've poured it all over...\n\n",
		[INDEX_OVERPOWERED_FATAL_ERROR] = 				"Where are you going?! My memory!\n\n",
		[INVALID_INSTRUCTION_FATAL_ERROR] = 			"Why did you break my brain?\n\n",
		[NO_COPROCESSOR_FATAL_ERROR] = 					"Only for the smart, dsjidjsdisidsudi, the dumb won't understand.\n\n",
		[DOUBLE_FAULT_FATAL_ERROR] = 					"Monsieur, it seems to me that you and I have split up!\n\n",
		[COPROCESSOR_SEGMENT_OVERFLOW_FATAL_ERROR] = 	"You write incorrectly instead of \"CoprocessorSegmentOverflowError\" write \"StackOverflow\", give birth to idiots...\n\n",
		[STACK_FATAL_ERROR] = 							"The same mistake, STOP WRITING WITHOUT \"OVERFLOW\"!!!\n\n",
		[PROTECTION_FATAL_ERROR] = 						"Stop, it's the police, why are you breaking the law?\n\n",
		[PAGE_FATAL_ERROR] = 							"Wait, where are you flipping through, you passed by our page!\n\n",
		[UNKNOWN_INTERRUPT_FATAL_ERROR] = 				"Wait, where are you rushing to, this is not our number.\n\n",
		[COPROCESSOR_FATAL_ERROR] = 					"Stop being smart, I can't do that, I'm having a glitch!\n\n",
		[ALIGNMENT_FATAL_ERROR] = 						"Straighten up! We have an important matter!\n\n",
		[MACHINE_CHECK_FATAL_ERROR] = 					"Careful... AHHH, IT HURTS!\n\n",
		[RESERVED_FATAL_ERROR] = 						"Go away, this place is reserved!\n\n",
		[ISR_RESERVED_FATAL_ERROR] = 					"Go away, ISR is reserved!\n\n"
	};

	if (errorType <= sizeof(errorMessages) / sizeof(int8*))
		return errorMessages[errorType];

	return "There are no words.\n\n";
}

int8* getFormalFatalErrorDescription(FatalErrorType errorType) {
	int8* errorMessages[] = {
		[DIVISION_BY_ZERO_FATAL_ERROR] = 				"You has divided any number by zero, you get infinity and error to gift :).\n\n",
		[DEBUG_FATAL_ERROR] = 							"The kernel was stopped because a Debug label was set at the code execution point.",
		[NON_MASKABLE_INTERRUPT_FATAL_ERROR] = 			"Hello non maskable interrupt, i've been looking for you!\n\n",
		[BREAK_POINT_FATAL_ERROR] = 					"Let's break everything, we're rich!\n\n",
		[STACK_OVERFLOW_FATAL_ERROR] = 					"Look what you've done, you've poured it all over...\n\n",
		[INDEX_OVERPOWERED_FATAL_ERROR] = 				"Where are you going?! My memory!\n\n",
		[INVALID_INSTRUCTION_FATAL_ERROR] = 			"Why did you break my brain?\n\n",
		[NO_COPROCESSOR_FATAL_ERROR] = 					"Only for the smart, dsjidjsdisidsudi, the dumb won't understand.\n\n",
		[DOUBLE_FAULT_FATAL_ERROR] = 					"Monsieur, it seems to me that you and I have split up!\n\n",
		[COPROCESSOR_SEGMENT_OVERFLOW_FATAL_ERROR] = 	"You write incorrectly instead of \"CoprocessorSegmentOverflowError\" write \"StackOverflow\", give birth to idiots...\n\n",
		[STACK_FATAL_ERROR] = 							"The same mistake, STOP WRITING WITHOUT \"OVERFLOW\"!!!\n\n",
		[PROTECTION_FATAL_ERROR] = 						"Stop, it's the police, why are you breaking the law?\n\n",
		[PAGE_FATAL_ERROR] = 							"Wait, where are you flipping through, you passed by our page!\n\n",
		[UNKNOWN_INTERRUPT_FATAL_ERROR] = 				"Wait, where are you rushing to, this is not our number.\n\n",
		[COPROCESSOR_FATAL_ERROR] = 					"Stop being smart, I can't do that, I'm having a glitch!\n\n",
		[ALIGNMENT_FATAL_ERROR] = 						"Straighten up! We have an important matter!\n\n",
		[MACHINE_CHECK_FATAL_ERROR] = 					"Careful... AHHH, IT HURTS!\n\n",
		[RESERVED_FATAL_ERROR] = 						"Go away, this place is reserved!\n\n",
		[ISR_RESERVED_FATAL_ERROR] = 					"Go away, ISR is reserved!\n\n"
	};

	if (errorType <= sizeof(errorMessages) / sizeof(int8*))
		return errorMessages[errorType];

	return "There are no words.\n\n";
}

void causeFatalError(FatalErrorType errorType) {
	uint16 tempForegroundColor = foregroundColor;

	foregroundColor = 0xff0000;

	UGSMASCIIputString(getIronicFatalErrorDescription(errorType));

	UGSMASCIIputString("\n\n");

	UGSMASCIIputString(getFormalFatalErrorDescription(errorType));

	foregroundColor = tempForegroundColor;

	swap();

	for (;;);
}