#ifndef _ERROR_H
#define _ERROR_H

#include "core/types.h"

typedef enum FatalErrorType {
	DebugError,
	DivisionByZeroError,
	NonMaskableInterruptError,
	BreakPoint,
	StackOverflowError,
	IndexOverpowered,
	InvalidInstruction,
	NoCoprocessorError,
	DoubleFaultError,
	CoprocessorSegmentOverflowError,
	StackError,
	ProtectionError,
	PageError,
	UnknownInterruptError,
	CoprocessorError,
	AlignmentError,
	MachineCheckError,
	ReservedError,
	ISRReservedError
} FatalErrorType;

int8* getFatalErrorDescription(FatalErrorType errorType);

void causeFatalError(FatalErrorType errorType);

#endif