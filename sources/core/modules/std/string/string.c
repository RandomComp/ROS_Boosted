#include "std/string/string.h"

#include "std/string/string_types.h"

#include "std/string/char.h"

#include "std/string/char_types.h"

#include "core/basic_types.h"

#include "exceptions/exception.h"

String String_fromChar(Char ch) {
	String result = newString(1);

	String_setChar(&result, 0, ch);

	return result;
}

ErrorCode String_setChar(String* str, uint32 index, Char ch) {
	if (!isValidStr(str)) {
		throw(
			Exception_errorInvalidArgument(
				"Cannot set a character in an invalid string "
				"(for example, the string length is <= 0, or the pointer "
				"to the memory under the string is null)"
			)
		);

		return;
	}

	Char* charArray = str->data;

	charArray[index] = ch;
}

Char* String_getChar(String* str, size_t index) {
	if (!isValidStr(str)) {
		throw(
			Exception_errorInvalidArgument(
				"It is not possible to get a character from an invalid string "
				"(for example, the string's length is <= 0 or the pointer "
				"to the memory location to which the string refers is null)"
			)
		);

		return ;
	}

	Char* charArray = str->data;

	return &charArray[index];
}

bool isValidStr(String* str) {
	return str->data != nullptr && str->length > 0;
}

ErrorCode freeString(String* str) {
	if (!isValidStr(str)) {
		throw(
			Exception_errorInvalidArgument(
				""
			)
		);

		return CODE_FAIL;
	}

	free(str->data);

	str->data = null;

	return CODE_OK;
}

String newString(uint32 length) {
	assert(length == 0, Exception_fromError(INVALID_ARGUMENT_ERROR, Exception_fromString("Zero argument is not allowed.")));
	
	void* charMem = malloc(sizeof(Char) * length, MEMORY_STATUS_READABLE | MEMORY_STATUS_WRITABLE);
	
	return (String){.length = length, .data = charMem};
}

String newStringFromCP437(CP437_CharacterCode* str) {
	assert(str == 0, Exception_fromError(INVALID_ARGUMENT_ERROR, Exception_fromString("A null pointer to a string argument is not allowed.")));

	uint32 length = CP437getLength(str);

	String result = newString(length);

	memcpy(result.data->memory, str, length);
	
	return result;
}
/// @brief Преобразует переданную строку 
/// @param str 
/// @return 
String* newStringFromUGSM(UGSM_CharacterCode* str) {
	uint32 length = UGSMgetLength(str);

	String result = newString(length);

	memcpy(result.data->memory, str, length);
	
	return &result;
}

void substr(String* _result, String* x, uint32 start, uint32 end) {
	assert(!isValidMemoryRegion(x->data), Exception_fromError(INVALID_ARGUMENT_ERROR, Exception_fromString("Cannot cut a substring from a incorrect string.")));
	
	assert(end > x->length, Exception_fromError(INVALID_ARGUMENT_ERROR, Exception_fromString("The specified size is greater than the string size=%i to the end=%i, the code execution will continue, but it is necessary to check the correctness of the arguments.", x->length, end)));

	uint32 minLength = iminU32(end, x->length);

	String* result = newString(minLength);

	memcpy(result->data->memory, x->data->memory + start, minLength);

	_result = &result;
}

String int64ToString(int64 x) {
	String result = newString(getNumberOfDigits64(x));

	String_setChar(&result, 0, newCharFromUGSM(UGSM_CHAR_0));

	uint32 index = 0;

	while (x != 0) {
		Char ch = digitToChar(getFirstNumber64(x));

		String_setChar(&result, result.length - index, ch);

		x /= 10;

		index++;
	}

	return result;
}

String uint64ToString(uint64 x) {
	String result = newString(getNumberOfDigitsU64(x));

	String_setChar(&result, 0, newCharFromUGSM(UGSM_CHAR_0));

	uint32 index = 0;

	while (x != 0) {
		Char ch = digitToChar(getFirstNumberU64(x));

		String_setChar(&result, result.length - index, ch);

		x /= 10;

		index++;
	}

	return result;
}

String String_fromU32(uint32 x) {
	

	return result;
}

bool String_isValid(String* str) {
	return 	str != nullptr && 
			str->data != nullptr && 
			str->length > 0;
}

void String_free(String* str) {
	if (str == nullptr) return;

	free(str->data);

	free(str);
}

void String_cat(String* a, String* b) {
	
}