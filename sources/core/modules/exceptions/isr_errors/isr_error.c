#include "core/isr_error.h"

#include "core/basic_types.h"

#include "core/console.h"

#include "charset/ascii.h"

#include "charset/cp437_types.h"

static CP437_CharacterCode* getFatalErrorName(ISR_Error errorType) {
	CP437_CharacterCode* errorMessages[] = {
		[DIVISION_BY_ZERO_FATAL_ERROR] = 				"DIVISION_BY_ZERO_FATAL_ERROR",
		[NON_MASKABLE_INTERRUPT_FATAL_ERROR] = 			"NON_MASKABLE_INTERRUPT_FATAL_ERROR",
		[BREAK_POINT_FATAL_ERROR] = 					"BREAK_POINT_FATAL_ERROR",
		[STACK_OVERFLOW_FATAL_ERROR] = 					"STACK_OVERFLOW_FATAL_ERROR",
		[INDEX_OVERPOWERED_FATAL_ERROR] = 				"INDEX_OVERPOWERED_FATAL_ERROR",
		[INVALID_INSTRUCTION_FATAL_ERROR] = 			"INVALID_INSTRUCTION_FATAL_ERROR",
		[NO_COPROCESSOR_FATAL_ERROR] = 					"NO_COPROCESSOR_FATAL_ERROR",
		[DOUBLE_FATAL_ERROR] = 							"DOUBLE_FATAL_ERROR",
		[COPROCESSOR_SEGMENT_OVERRUN_FATAL_ERROR] = 	"COPROCESSOR_SEGMENT_OVERRUN_FATAL_ERROR",
		[INVALID_TSS_FATAL_ERROR] = 					"INVALID_TSS_FATAL_ERROR",
		[SEGMENT_PRESENT_FATAL_ERROR] = 				"SEGMENT_PRESENT_FATAL_ERROR",
		[STACK_SEGMENT_FATAL_ERROR] = 					"STACK_SEGMENT_FATAL_ERROR",
		[GENERAL_PROTECTION_FATAL_ERROR] = 				"GENERAL_PROTECTION_FATAL_ERROR",
		[PAGE_FATAL_ERROR] = 							"PAGE_FATAL_ERROR",
		[X87_FPU_FATAL_ERROR] = 						"X87_FPU_FATAL_ERROR",
		[ALIGNMENT_CHECK_FATAL_ERROR] = 				"ALIGNMENT_CHECK_FATAL_ERROR",
		[MACHINE_CHECK_FATAL_ERROR] = 					"MACHINE_CHECK_FATAL_ERROR",
		[SIMD_FLOAT_FATAL_ERROR] = 						"SIMD_FLOAT_FATAL_ERROR",
		[IRQ_KERNEL_UNUSED_FATAL_ERROR] = 				"IRQ_KERNEL_UNUSED_FATAL_ERROR"
	};

	if (errorType <= sizeof(errorMessages) / sizeof(CP437_CharacterCode*))
		return errorMessages[errorType];

	return "UNKNOWN_FATAL_ERROR";
}

static CP437_CharacterCode* getIronicFatalErrorDescription(ISR_Error errorType) {
	CP437_CharacterCode* errorMessages[] = {
		[DIVISION_BY_ZERO_FATAL_ERROR] = 				"You has divided any number by zero, you get infinity and error to gift :).",
		[NON_MASKABLE_INTERRUPT_FATAL_ERROR] = 			"Hello non maskable interrupt, i've been looking for you!",
		[BREAK_POINT_FATAL_ERROR] = 					"Let's break everything, we're rich!",
		[STACK_OVERFLOW_FATAL_ERROR] = 					"Look what you've done, you've poured it all over...",
		[INDEX_OVERPOWERED_FATAL_ERROR] = 				"Where are you going?! My memory!",
		[INVALID_INSTRUCTION_FATAL_ERROR] = 			"Why did you break my brain?",
		[NO_COPROCESSOR_FATAL_ERROR] = 					"Only for the smart, dsjidjsdisidsudi, the dumb won't understand.",
		[DOUBLE_FATAL_ERROR] = 							"Monsieur, it seems to me that you and I have split up!",
		[COPROCESSOR_SEGMENT_OVERRUN_FATAL_ERROR] = 	"You write incorrectly instead of \"CoprocessorSegmentOverflowError\" write \"StackOverflow\", give birth to idiots...",
		[INVALID_TSS_FATAL_ERROR] = 					"You write incorrectly instead of \"CoprocessorSegmentOverflowError\" write \"StackOverflow\", give birth to idiots...",
		[SEGMENT_PRESENT_FATAL_ERROR] = 				"The same mistake, STOP WRITING WITHOUT \"OVERFLOW\"!!!",
		[STACK_SEGMENT_FATAL_ERROR] = 					"The same mistake, STOP WRITING WITHOUT \"OVERFLOW\"!!!",
		[GENERAL_PROTECTION_FATAL_ERROR] = 				"Stop, it's the police, why are you breaking the law?",
		[PAGE_FATAL_ERROR] = 							"Wait, where are you flipping through, you passed by our page!",
		[X87_FPU_FATAL_ERROR] = 						"Stop being smart, I can't do that, I'm having a glitch!",
		[ALIGNMENT_CHECK_FATAL_ERROR] = 				"Straighten up! We have an important matter!",
		[MACHINE_CHECK_FATAL_ERROR] = 					"Careful... AHHH, IT HURTS!",
		[SIMD_FLOAT_FATAL_ERROR] = 						"Careful... AHHH, IT HURTS!",
		[IRQ_KERNEL_UNUSED_FATAL_ERROR] = 				"Go away, IRQ/ISR is reserved!"
	};

	if (errorType <= sizeof(errorMessages) / sizeof(CP437_CharacterCode*))
		return errorMessages[errorType];

	return "There are no words.";
}

static CP437_CharacterCode* getFormalFatalErrorDescription(ISR_Error errorType) {
	CP437_CharacterCode* errorMessages[] = {
		[DIVISION_BY_ZERO_FATAL_ERROR] = 				"You has divided any number by zero, you get infinity and error to gift :).",
		[NON_MASKABLE_INTERRUPT_FATAL_ERROR] = 			"Hello non maskable interrupt, i've been looking for you!",
		[BREAK_POINT_FATAL_ERROR] = 					"The kernel was stopped because a Debug label was set at the code execution point.",
		[STACK_OVERFLOW_FATAL_ERROR] = 					"Look what you've done, you've poured it all over...",
		[INDEX_OVERPOWERED_FATAL_ERROR] = 				"Where are you going?! My memory!",
		[INVALID_INSTRUCTION_FATAL_ERROR] = 			"Why did you break my brain?",
		[NO_COPROCESSOR_FATAL_ERROR] = 					"Only for the smart, dsjidjsdisidsudi, the dumb won't understand.",
		[DOUBLE_FATAL_ERROR] = 							"Monsieur, it seems to me that you and I have split up!",
		[COPROCESSOR_SEGMENT_OVERRUN_FATAL_ERROR] = 	"You write incorrectly instead of \"CoprocessorSegmentOverflowError\" write \"StackOverflow\", give birth to idiots...",
		[INVALID_TSS_FATAL_ERROR] = 					"You write incorrectly instead of \"CoprocessorSegmentOverflowError\" write \"StackOverflow\", give birth to idiots...",
		[SEGMENT_PRESENT_FATAL_ERROR] = 				"The same mistake, STOP WRITING WITHOUT \"OVERFLOW\"!!!",
		[STACK_SEGMENT_FATAL_ERROR] = 					"The same mistake, STOP WRITING WITHOUT \"OVERFLOW\"!!!",
		[GENERAL_PROTECTION_FATAL_ERROR] = 				"Stop, it's the police, why are you breaking the law?",
		[PAGE_FATAL_ERROR] = 							"Wait, where are you flipping through, you passed by our page!",
		[X87_FPU_FATAL_ERROR] = 						"Stop being smart, I can't do that, I'm having a glitch!",
		[ALIGNMENT_CHECK_FATAL_ERROR] = 				"Straighten up! We have an important matter!",
		[MACHINE_CHECK_FATAL_ERROR] = 					"Careful... AHHH, IT HURTS!",
		[SIMD_FLOAT_FATAL_ERROR] = 						"Careful... AHHH, IT HURTS!",
		[IRQ_KERNEL_UNUSED_FATAL_ERROR] = 				"Go away, motherfucker, ISR is reserved!"
	};

	if (errorType <= sizeof(errorMessages) / sizeof(CP437_CharacterCode*))
		return errorMessages[errorType];

	return "There are no words.";
}

void FATAL_ERROR_throw(ISR_Error errorType, CP437_CharacterCode* why) {
	ASCII_putString("[red]Ironic fatal error description:\n");

	ASCII_putString(getIronicFatalErrorDescription(errorType));

	ASCII_putString("\n\nFormal fatal error description:\n");

	ASCII_putString(getFormalFatalErrorDescription(errorType));

	ASCII_putString("\n\nFatal error name: ");

	ASCII_putString(getFatalErrorName(errorType));

	ASCII_putString("\n\nDetails:\n");

	CP437_putString(details);

	ASCII_putString("\n[white]");

	swap();
}