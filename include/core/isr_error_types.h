#ifndef _RANDOM_OS_ISR_ERROR_TYPES_H
#define _RANDOM_OS_ISR_ERROR_TYPES_H

typedef enum ISR_ErrorTypes {
	ISR_DIVISION_BY_ZERO = 0, 			// Ошибка деления на ноль.
	// Reserved ISR 1, 0x1
	ISR_NON_MASKABLE_INTERRUPT = 2,		// NMI, вызывается даже при cli ( CLEAR INTERRUPT FLAG ), нельзя обработать через блок try.
	ISR_BREAK_POINT,					// Вызвался Break Point в этой строке, обрабатывается через блок try.
	ISR_STACK_OVERFLOW,					// Этот ISR вызывается при переполнении стэка. Нельзя обработать через блок try.
	ISR_INDEX_OVERPOWERED,				// Этот ISR вызывается при доступе к запрещенной/незарезервированной памяти, можно обработать через блок try.
	ISR_INVALID_INSTRUCTION,
	ISR_NO_COPROCESSOR,
	ISR_DOUBLE,
	ISR_COPROCESSOR_SEGMENT_OVERRUN,
	ISR_INVALID_TSS,
	ISR_SEGMENT_PRESENT,
	ISR_STACK_SEGMENT,
	ISR_GENERAL_PROTECTION,
	ISR_PAGE,
	// Reserved ISR 15, 0xF
	ISR_X87_FPU = 16,
	ISR_ALIGNMENT_CHECK,
	ISR_MACHINE_CHECK,
	ISR_SIMD_FLOAT,
	// Reserved ISR 20-31, 0x14-0x1F
	ISR_IRQ_KERNEL_USE = 20, // KERNEL DEFINABLE 32-255, ISR 0x20-0xFF,

	ISR_UNKNOWN = 256
} ISR_ErrorTypes;

#endif