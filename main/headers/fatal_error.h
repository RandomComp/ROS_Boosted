#ifndef _ERROR_H
#define _ERROR_H

#include "../headers/types.h"

enum FatalErrorsType {
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

	BadTSError,

	SegmentTSNotFoundError,

	StackError,

	ProtectionError,

	PageError,

	UnknownInterruptError,

	CoprocessorError,

	AlignmentError,

	MachineCheckError,

	ReservedError
};

int8* getFatalErrorDescription(enum FatalErrorsType errorType);

void causeFatal(enum FatalErrorsType errorType);

#endif