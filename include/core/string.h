#ifndef _RANDOM_OS_STRING_H
#define _RANDOM_OS_STRING_H

#include "core/types.h"

#include "core/T.h"

#include "drivers/low-level/base/ram.h"

typedef struct String {
	uint32 length;

	MemoryRegion* region;
} String;

inline String charToString(Char ch) {
	String result = newString(1);

	setCharToString(&result, 0, ch);

	return result;
}

inline void setCharToString(String* str, uint32 index, Char ch) {
	assert(!isValidStr(str), Exception_fromError(INVALID_ARGUMENT_ERROR, Exception_messageFromString("Cannot set a character in an invalid string (for example, the string length is <= 0, or the pointer to the memory under the string is null)")));

	Char* charArray = getCharArrayFromString(*str);

	charArray[index] = ch;
}

inline Char getCharFromString(String* str, uint32 index) {
	assert(!isValidStr(str), Exception_fromError(INVALID_ARGUMENT_ERROR, Exception_messageFromString("It is not possible to get a character from an invalid string (for example, the string's length is <= 0 or the pointer to the memory location to which the string refers is null)")));

	Char* charArray = getCharArrayFromString(*str);

	return charArray[index];
}

inline bool isValidStr(String* str) {
	return isValidAndActiveMemoryRegion(str->region) && str->length > 0;
}

inline void freeString(String* str) {
	assert(!isValidStr(str), Exception_fromError(INVALID_ARGUMENT_ERROR, Exception_messageFromString("")));

	free(str->region);

	str->region = null;
}

inline String newString(uint32 length) {
	assert(length == 0, Exception_fromError(INVALID_ARGUMENT_ERROR, Exception_newMessage(__FILE__, __LINE__, "Zero argument is not allowed.")));
	
	MemoryRegion* charMem = malloc(sizeof(Char) * length, MEMORY_STATUS_READABLE | MEMORY_STATUS_WRITABLE);
	
	return (String){.length = length, .region = charMem};
}

inline String newStringFromCP437(CP437_CharacterCode* str) {
	assert(str == 0, Exception_fromError(INVALID_ARGUMENT_ERROR, Exception_newMessage(__FILE__, __LINE__, "A null pointer to a string argument is not allowed.")));

	uint32 length = CP437getLength(str);

	String result = newString(length);

	memcpy(result.region->memory, str, length);
	
	return result;
}

inline String newStringFromUGSM(UGSMGlyphCode* str) {
	uint32 length = UGSMgetLength(str);

	String result = newString(length);

	memcpy(result.region->memory, str, length);
	
	return result;
}

inline String substr(String x, uint32 start, uint32 end) {
	assert(isValidAndActiveMemoryRegion(*x.region), UETFromError(INVALID_ARGUMENT_ERROR), "");
	
	uint32 minLength = iminU32(end - start, x.length);

	String result = newString(minLength);

	memcpy(result.region->memory, x.region->memory + start, minLength);

	return result;
}

String sintToString(sint x);
String uintToString(uint x);

String int32ToString(int32 x);
String uint32ToString(uint32 x);

String stringConcatenate(String a, String b); // Конкатенирует две строки
String stringFromT(T x);

#endif