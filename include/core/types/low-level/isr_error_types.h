#ifndef _RANDOM_OS_ISR_ERROR_TYPES_H
#define _RANDOM_OS_ISR_ERROR_TYPES_H

typedef enum ISR_Error {
	ISR_DIVISION_BY_ZERO_ERROR = 0, 		// Ошибка деления на ноль.
	// Reserved ISR 1, 0x1
	ISR_NON_MASKABLE_INTERRUPT_ERROR = 2,	// NMI, вызывается даже при cli ( CLEAR INTERRUPT FLAG ), нельзя обработать через блок try.
	ISR_BREAK_POINT_ERROR,					// Этот ISR вызывается при выполнение в коде инструкции с точкой останова, может обрабатываться через блок try.
	ISR_STACK_OVERFLOW_ERROR,				// Этот ISR вызывается при переполнении стэка. Нельзя обработать через блок try.
	ISR_INDEX_OVERPOWERED_ERROR,			// Этот ISR вызывается при доступе к запрещенной/незарезервированной памяти, можно обработать через блок try.
	ISR_INVALID_INSTRUCTION_ERROR,			// Этот ISR вызывается при попытке выполнения кода процессором с некорректной инструкцией. Нельзя обработать через блок try.
	ISR_NO_COPROCESSOR_ERROR,				// Этот ISR вызывается при неудачной попытке доступа к сопроцессору, например, при попытки поделить одно дробное число на другое. Можно обработать через блок try.
	ISR_DOUBLE_ERROR,						// Этот ISR вызывается при ISR ошибки в ISR ошибке, крайне редкая ошибка, если она все таки произошла, то стоит пранализировать стэк вызовов.
	ISR_COPROCESSOR_SEGMENT_OVERRUN_ERROR,
	ISR_INVALID_TSS_ERROR,					// 
	ISR_SEGMENT_PRESENT_ERROR,
	ISR_STACK_SEGMENT_ERROR,
	ISR_GENERAL_PROTECTION_ERROR,
	ISR_PAGE_ERROR,
	// Reserved ISR 15, 0xF
	ISR_X87_FPU_ERROR = 16,
	ISR_ALIGNMENT_CHECK_ERROR,
	ISR_MACHINE_CHECK_ERROR,
	ISR_SIMD_FLOAT_ERROR,
	// Reserved ISR 20-31, 0x14-0x1F
	ISR_KERNEL_USE_ERROR = 0x20, // KERNEL DEFINABLE 32-255, ISR 0x20-0xFF,

	ISR_UNKNOWN_ERROR = 256
} ISR_Error;

#endif