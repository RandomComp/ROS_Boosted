#ifndef _RANDOM_OS_STRING_H
#define _RANDOM_OS_STRING_H

#include "core/basic_types.h"

#include "core/types/high-level/T_types.h"

#include "drivers/low-level/base/ram.h"

static inline String charToString(Char ch) {
	String result = newString(1);

	setCharToString(&result, 0, ch);

	return result;
}

static inline void setCharToString(String* str, uint32 index, Char ch) {
	assert(!isValidStr(str), Exception_fromError(INVALID_ARGUMENT_ERROR, Exception_fromString("Cannot set a character in an invalid string (for example, the string length is <= 0, or the pointer to the memory under the string is null)")));

	Char* charArray = getCharArrayFromString(*str);

	charArray[index] = ch;
}

static inline Char getCharFromString(String* str, uint32 index) {
	assert(!isValidStr(str), Exception_fromError(INVALID_ARGUMENT_ERROR, Exception_fromString("It is not possible to get a character from an invalid string (for example, the string's length is <= 0 or the pointer to the memory location to which the string refers is null)")));

	Char* charArray = getCharArrayFromString(*str);

	return charArray[index];
}

static inline bool isValidStr(String* str) {
	return isValidMemoryRegion(str->region) && str->length > 0;
}

static inline void freeString(String* str) {
	assert(!isValidStr(str), Exception_fromError(INVALID_ARGUMENT_ERROR, Exception_fromString("")));

	free(str->region);

	str->region = null;
}

static inline String newString(uint32 length) {
	assert(length == 0, Exception_fromError(INVALID_ARGUMENT_ERROR, Exception_fromString("Zero argument is not allowed.")));
	
	void* charMem = malloc(sizeof(Char) * length, MEMORY_STATUS_READABLE | MEMORY_STATUS_WRITABLE);
	
	return (String){.length = length, .region = charMem};
}

static inline String newStringFromCP437(CP437_CharacterCode* str) {
	assert(str == 0, Exception_fromError(INVALID_ARGUMENT_ERROR, Exception_fromString("A null pointer to a string argument is not allowed.")));

	uint32 length = CP437getLength(str);

	String result = newString(length);

	memcpy(result.region->memory, str, length);
	
	return result;
}
/// @brief Преобразует переданную строку 
/// @param str 
/// @return 
static inline String* newStringFromUGSM(UGSM_CharacterCode* str) {
	uint32 length = UGSMgetLength(str);

	String result = newString(length);

	memcpy(result.region->memory, str, length);
	
	return &result;
}

static inline void substr(String* _result, String* x, uint32 start, uint32 end) {
	assert(!isValidMemoryRegion(x->region), Exception_fromError(INVALID_ARGUMENT_ERROR, Exception_fromString("Cannot cut a substring from a incorrect string.")));
	
	assert(end > x->length, Exception_fromError(INVALID_ARGUMENT_ERROR, Exception_fromString("The specified size is greater than the string size=%i to the end=%i, the code execution will continue, but it is necessary to check the correctness of the arguments.", x->length, end)));

	uint32 minLength = iminU32(end, x->length);

	String* result = newString(minLength);

	memcpy(result->region->memory, x->region->memory + start, minLength);

	_result = &result;
}

String sintToString(sint x);
String uintToString(uint x);

String int32ToString(int32 x);
String uint32ToString(uint32 x);

void stringConcatenate(String* result, String a, String b); // Конкатенирует две строки
void getStringFromT(String* result, T x);

#endif