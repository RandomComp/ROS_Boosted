#include "exceptions/isr_errors/isr_error.h"

#include "core/basic_types.h"

#include "math/math.h"

#include "std/std.h"

static const c_str getFatalErrorName(ISR_Error errorType) {
	const c_str errorMessages[] = {
		[ISR_DIVISION_BY_ZERO_ERROR] = 				"ISR_DIVISION_BY_ZERO_ERROR",
		[ISR_NON_MASKABLE_INTERRUPT_ERROR] = 		"ISR_NON_MASKABLE_INTERRUPT_ERROR",
		[ISR_BREAK_POINT_ERROR] = 					"ISR_BREAK_POINT_ERROR",
		[ISR_STACK_OVERFLOW_ERROR] = 				"ISR_STACK_OVERFLOW_ERROR",
		[ISR_INDEX_OVERPOWERED_ERROR] = 			"ISR_INDEX_OVERPOWERED_ERROR",
		[ISR_INVALID_INSTRUCTION_ERROR] = 			"ISR_INVALID_INSTRUCTION_ERROR",
		[ISR_NO_COPROCESSOR_ERROR] = 				"ISR_NO_COPROCESSOR_ERROR",
		[ISR_DOUBLE_ERROR] = 						"ISR_DOUBLE_ERROR",
		[ISR_COPROCESSOR_SEGMENT_OVERRUN_ERROR] = 	"ISR_COPROCESSOR_SEGMENT_OVERRUN_ERROR",
		[ISR_INVALID_TSS_ERROR] = 					"ISR_INVALID_TSS_ERROR",
		[ISR_SEGMENT_PRESENT_ERROR] = 				"ISR_SEGMENT_PRESENT_ERROR",
		[ISR_STACK_SEGMENT_ERROR] = 				"ISR_STACK_SEGMENT_ERROR",
		[ISR_GENERAL_PROTECTION_ERROR] = 			"ISR_GENERAL_PROTECTION_ERROR",
		[ISR_PAGE_ERROR] = 							"ISR_PAGE_ERROR",
		[ISR_X87_FPU_ERROR] = 						"ISR_X87_FPU_ERROR",
		[ISR_ALIGNMENT_CHECK_ERROR] = 				"ISR_ALIGNMENT_CHECK_ERROR",
		[ISR_MACHINE_CHECK_ERROR] = 				"ISR_MACHINE_CHECK_ERROR",
		[ISR_SIMD_FLOAT_ERROR] = 					"ISR_SIMD_FLOAT_ERROR",
		[ISR_KERNEL_USE_ERROR] = 					"ISR_KERNEL_USE_ERROR"
	};

	if (inRangeU32(errorType, ISR_FIRST_ERROR, ISR_LAST_ERROR))
		return errorMessages[errorType];

	return "UNKNOWN_FATAL_ERROR";
}

static const c_str getIronicFatalErrorDescription(ISR_Error errorType) {
	const c_str errorMessages[] = {
		[ISR_DIVISION_BY_ZERO_ERROR] = 				"You has divided any number by zero, you get infinity and error to gift :).",
		[ISR_NON_MASKABLE_INTERRUPT_ERROR] = 		"Hello non maskable interrupt, i've been looking for you!",
		[ISR_BREAK_POINT_ERROR] = 					"Let's break everything, we're rich!",
		[ISR_STACK_OVERFLOW_ERROR] = 				"Look what you've done, you've poured it all over...",
		[ISR_INDEX_OVERPOWERED_ERROR] = 			"Where are you going?! My memory!",
		[ISR_INVALID_INSTRUCTION_ERROR] = 			"Why did you break my brain?",
		[ISR_NO_COPROCESSOR_ERROR] = 				"Only for the smart, dsjidjsdisidsudi, the dumb won't understand.",
		[ISR_DOUBLE_ERROR] = 						"Monsieur, it seems to me that you and I have split up!",
		[ISR_COPROCESSOR_SEGMENT_OVERRUN_ERROR] = 	"You write incorrectly instead of \"CoprocessorSegmentOverflowError\" write \"StackOverflow\", give birth to idiots...",
		[ISR_INVALID_TSS_ERROR] = 					"You write incorrectly instead of \"CoprocessorSegmentOverflowError\" write \"StackOverflow\", give birth to idiots...",
		[ISR_SEGMENT_PRESENT_ERROR] = 				"The same mistake, STOP WRITING WITHOUT \"OVERFLOW\"!!!",
		[ISR_STACK_SEGMENT_ERROR] = 				"The same mistake, STOP WRITING WITHOUT \"OVERFLOW\"!!!",
		[ISR_GENERAL_PROTECTION_ERROR] = 			"Stop, it's the police, why are you breaking the law?",
		[ISR_PAGE_ERROR] = 							"Wait, where are you flipping through, you passed by our page!",
		[ISR_X87_FPU_ERROR] = 						"Stop being smart, I can't do that, I'm having a glitch!",
		[ISR_ALIGNMENT_CHECK_ERROR] = 				"Straighten up! We have an important matter!",
		[ISR_MACHINE_CHECK_ERROR] = 				"Careful... AHHH, IT HURTS!",
		[ISR_SIMD_FLOAT_ERROR] = 					"Careful... AHHH, IT HURTS!",
		[ISR_KERNEL_USE_ERROR] = 					"Go away, ISR is reserved!"
	};

	if (inRangeU32(errorType, ISR_FIRST_ERROR, ISR_LAST_ERROR))
		return errorMessages[errorType];

	return "There are no words.";
}

static const c_str getFormalFatalErrorDescription(ISR_Error errorType) {
	const c_str errorMessages[] = {
		[ISR_DIVISION_BY_ZERO_ERROR] = 				"You has divided any number by zero, you get infinity and error to gift :).",
		[ISR_NON_MASKABLE_INTERRUPT_ERROR] = 		"Hello non maskable interrupt, i've been looking for you!",
		[ISR_BREAK_POINT_ERROR] = 					"The kernel was stopped because a Debug label was set at the code execution point.",
		[ISR_STACK_OVERFLOW_ERROR] = 				"Look what you've done, you've poured it all over...",
		[ISR_INDEX_OVERPOWERED_ERROR] = 			"Where are you going?! My memory!",
		[ISR_INVALID_INSTRUCTION_ERROR] = 			"Why did you break my brain?",
		[ISR_NO_COPROCESSOR_ERROR] = 				"Only for the smart, dsjidjsdisidsudi, the dumb won't understand.",
		[ISR_DOUBLE_ERROR] = 						"Monsieur, it seems to me that you and I have split up!",
		[ISR_COPROCESSOR_SEGMENT_OVERRUN_ERROR] = 	"You write incorrectly instead of \"CoprocessorSegmentOverflowError\" write \"StackOverflow\", give birth to idiots...",
		[ISR_INVALID_TSS_ERROR] = 					"You write incorrectly instead of \"CoprocessorSegmentOverflowError\" write \"StackOverflow\", give birth to idiots...",
		[ISR_SEGMENT_PRESENT_ERROR] = 				"The same mistake, STOP WRITING WITHOUT \"OVERFLOW\"!!!",
		[ISR_STACK_SEGMENT_ERROR] = 				"The same mistake, STOP WRITING WITHOUT \"OVERFLOW\"!!!",
		[ISR_GENERAL_PROTECTION_ERROR] = 			"Stop, it's the police, why are you breaking the law?",
		[ISR_PAGE_ERROR] = 							"Wait, where are you flipping through, you passed by our page!",
		[ISR_X87_FPU_ERROR] = 						"Stop being smart, I can't do that, I'm having a glitch!",
		[ISR_ALIGNMENT_CHECK_ERROR] = 				"Straighten up! We have an important matter!",
		[ISR_MACHINE_CHECK_ERROR] = 				"Careful... AHHH, IT HURTS!",
		[ISR_SIMD_FLOAT_ERROR] = 					"Careful... AHHH, IT HURTS!",
		[ISR_KERNEL_USE_ERROR] = 					"Go away, motherfucker, ISR is reserved!"
	};

	if (inRangeU32(errorType, ISR_FIRST_ERROR, ISR_LAST_ERROR))
		return errorMessages[errorType];

	return "There are no words.";
}

void ISR_throw(ISR_Error errorType, const c_str why) {
	printf("[fg: red]Ironic fatal error description:\n[value: c_str]\n", getIronicFatalErrorDescription(errorType));

	printf("[fg: red]Formal fatal error description:\n[value: c_str]\n", getFormalFatalErrorDescription(errorType));

	printf("Fatal error name:\n[value: c_str]\n", getFatalErrorName(errorType));

	printf("Message: [value: c_str]\n", why);
}