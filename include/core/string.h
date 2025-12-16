#ifndef _RANDOM_OS_STRING_H
#define _RANDOM_OS_STRING_H

#include "core/types.h"

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
	if (str == null); // TODO: handle error

	Char* charArray = getCharArrayFromString(*str);

	if (charArray == null); // TODO: handle error

	charArray[index] = ch;
}

inline Char getCharFromString(String* str, uint32 index) {
	if (str == null); // TODO: handle error

	Char* charArray = getCharArrayFromString(*str);

	if (charArray == null); // TODO: handle error

	return charArray[index];
}

inline void freeString(String* str) {
	if (str != null && str->region != null) {
		free(str->region);

		str->region = null;
	}

	// TODO: handle error
}

inline String newString(uint32 length) {
	MemoryRegion* charMem = malloc(sizeof(Char) * length, MEMORY_ACCESS_READ | MEMORY_ACCESS_WRITE);
	
	return (String){.length = length, .region = charMem};
}

inline String newStringFromASCII(ASCIIGlyphCode* str) {
	uint32 length = ASCIIgetLength(str);

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

String int64ToString(int64 x);
String uint64ToString(uint64 x);

String int32ToString(int32 x);
String uint32ToString(uint32 x);

String stringConcatenate(String a, String b); // Конкатенирует две строки
String stringFromT(T x);

#endif