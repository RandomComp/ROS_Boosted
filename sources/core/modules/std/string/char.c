#include "std/string/char.h"

#include "core/basic_types.h"

#include "std/string/char_types.h"

#include "exceptions/exception.h"

#include "drivers/memory/ram.h"

Char* Char_fromASCII(uint8 ch) {
	Char* result = Char_new(1);

	result->charset = CHARSET_ASCII;

	result->ch[0] = ch;

	return result;
}

Char* Char_fromUGSM(UGSM_Code ch) {
	Char* result = Char_new(1);

	if (result == nullptr) {
		throw(
			Exception_fromError(
				ERROR_MEMORY_LACK,
				"Char allocation from UGSM Code error, because Char_new returned nullptr (out of memory)"
			)
		);

		return nullptr;
	}

	result->charset = CHARSET_UGSM;

	result->ch[0] = ch;

	return result;
}

Char* Char_new(size_t bytes) {
	Char* result = malloc(sizeof(Char));

	if (result == nullptr) {
		throw(
			Exception_fromError(
				ERROR_MEMORY_LACK,
				"Char allocation error, because malloc for \"Char* result\" returned nullptr (out of memory)"
			)
		);

		return nullptr;
	}

	result->charset = CHARSET_UNKNOWN;

	result->bytes = bytes;
	
	result->ch = nullptr;

	if (bytes > 0) {
		result->ch = malloc(bytes);

		if (result->ch == nullptr) {
			throw(
				Exception_fromError(
					ERROR_MEMORY_LACK,
					"Char allocation error, because malloc for \"byte* ch\" returned nullptr (out of memory)"
				)
			);
		}
	}

	return result;
}