#ifndef _ERROR_H
#define _ERROR_H

#include "core/types.h"

typedef enum ErrorType {
	VBENotSupportedError,
	VBESetupError,
	USBTDBitstuffError,
	USBTDTimeoutError,
	USBTDBabbleError,
	USBTDDataBufferError,
	USBTDStalledError,
	USBTDNAKError,
	USBAllocQHError,
	USBAllocTDError,
	USBMissedMicroFrameError,
	USBTransactionError,
	USBUnexpectedEHCIQHSize,
	GlyphNotReservedError,
	GlyphReservedError,
	UGSMIncorrectGlyphSetSizeError,
	UGSMGlyphNotReservedButWeTryUse,
	X16BitEmulatorError,
	ACPIS5ParseError,
	ACPIS5NotPresentError,
	ACPIDSDTError,
	ACPINoValidFACPPresentError,
	ACPINoACPIError,
	ACPICannotBeEnabledError,
	ACPINoKnownWayToEnableACPIError,
	ACPIShutdownError,
	ACPIUnableToShutdownError,
	MemoryLackError
} ErrorType;

int8* getErrorDescription(enum ErrorType errorType);

void cause(enum ErrorType errorType);

#endif