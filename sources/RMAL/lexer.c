#include "RMAL/lexer.h"

#include "core/types.h"

#include "core/std.h"

#include "charset/ugsm.h"

#include "charset/abc.h"

#include "core/warning.h"

#include "core/error.h"

UGSMGlyphCode RMALCode[384];

RMALToken RMALTokens[128];

uint16 tokenPos = 0;

int16 RMALPos = 0, RMALPosx = 1, RMALPosy = 1, RMALLength = 0;

UGSMGlyphCode instructionsName[17][6] = {
    { UGSM_CHAR_N, UGSM_CHAR_O, UGSM_CHAR_P, 0, 0, 0 },

    { UGSM_CHAR_M, UGSM_CHAR_O, UGSM_CHAR_V, 0, 0, 0 },

    { UGSM_CHAR_P, UGSM_CHAR_U, UGSM_CHAR_S, UGSM_CHAR_H, 0, 0 },

    { UGSM_CHAR_P, UGSM_CHAR_O, UGSM_CHAR_P, 0, 0, 0 },

    { UGSM_CHAR_A, UGSM_CHAR_D, UGSM_CHAR_D, 0, 0, 0 },

    { UGSM_CHAR_S, UGSM_CHAR_U, UGSM_CHAR_B, 0, 0, 0 },

    { UGSM_CHAR_M, UGSM_CHAR_U, UGSM_CHAR_L, 0, 0, 0 },

    { UGSM_CHAR_D, UGSM_CHAR_I, UGSM_CHAR_V, 0, 0, 0 },

    { UGSM_CHAR_I, UGSM_CHAR_N, UGSM_CHAR_C, 0, 0, 0 },

    { UGSM_CHAR_D, UGSM_CHAR_E, UGSM_CHAR_C, 0, 0, 0 },

    { UGSM_CHAR_I, UGSM_CHAR_N, UGSM_CHAR_X, UGSM_CHAR_8, 0, 0 },

    { UGSM_CHAR_I, UGSM_CHAR_N, UGSM_CHAR_X, UGSM_CHAR_1, UGSM_CHAR_6, 0 },

    { UGSM_CHAR_I, UGSM_CHAR_N, UGSM_CHAR_X, UGSM_CHAR_3, UGSM_CHAR_2, 0 },

    { UGSM_CHAR_O, UGSM_CHAR_U, UGSM_CHAR_T, UGSM_CHAR_X, UGSM_CHAR_8, 0 },

    { UGSM_CHAR_O, UGSM_CHAR_U, UGSM_CHAR_T, UGSM_CHAR_X, UGSM_CHAR_1, UGSM_CHAR_6 },

    { UGSM_CHAR_O, UGSM_CHAR_U, UGSM_CHAR_T, UGSM_CHAR_X, UGSM_CHAR_3, UGSM_CHAR_2 },

    { UGSM_CHAR_R, UGSM_CHAR_E, UGSM_CHAR_T, 0, 0, 0 }
};


UGSMGlyphCode registersName[][3] = {
    { UGSM_CHAR_E, UGSM_CHAR_A, UGSM_CHAR_X },

    { UGSM_CHAR_E, UGSM_CHAR_B, UGSM_CHAR_X },

    { UGSM_CHAR_E, UGSM_CHAR_C, UGSM_CHAR_X },

    { UGSM_CHAR_E, UGSM_CHAR_D, UGSM_CHAR_X },

    { UGSM_CHAR_E, UGSM_CHAR_S, UGSM_CHAR_P },

    { UGSM_CHAR_E, UGSM_CHAR_B, UGSM_CHAR_P },

    { UGSM_CHAR_E, UGSM_CHAR_S, UGSM_CHAR_I },

    { UGSM_CHAR_E, UGSM_CHAR_D, UGSM_CHAR_I }
};

void RMALTokenize(UGSMGlyphCode argRMALCode[384]) {
	tokenPos = 0;

	RMALPos = 0;

	RMALPosx = 1;

	RMALPosy = 1;

	RMALLength = 0;

	for (; argRMALCode[RMALLength]; RMALLength++)
		RMALCode[RMALLength] = argRMALCode[RMALLength];

	for (uint16 i = 0; i < 127; i++) {
		RMALTokens[i].type = INSTRUCTION;

		RMALTokens[i].instruction = RMAL_INSTRUCTION_NOP;
	}

	while (RMALPos < RMALLength) {
		UGSMGlyphCode current = RMALPeek(0);

		if (UGSMGlyphIsLetter(current)) RMALTokenizeWord();

		else if (UGSMGlyphIsDigit(current)) RMALTokenizeNumber();

		else if (current == 14 || current == 16) RMALTokenizeSignNumber();

		else if (current == 15) {
			RMALTokens[tokenPos].type = RMALCOMMA;

			tokenPos++;

			RMALNext();
		}

		else if (current == 62) {
			RMALTokens[tokenPos].type = RMALLBRACKET;

			tokenPos++;

			RMALNext();
		}

		else if (current == 64) {
			RMALTokens[tokenPos].type = RMALRBRACKET;

			tokenPos++;

			RMALNext();
		}

		else if (current == 29) {
			RMALTokens[tokenPos].type = RMALCOLON;

			tokenPos++;

			RMALNext();
		}

		else if (current == 30) {
			RMALTokenizeComment();
		}

		else RMALNext(); // We just ignore spaces or other nonsense
	}

	RMALTokens[tokenPos].type = RMALEOF;

	tokenPos++;
}

enum RMALInstructions findInstructionByName(UGSMGlyphCode name[6]) {
	uint16 i = 0, length = 0, checkLength = 0;

	for (; i < 18; i++) {
		checkLength = 0;

		for (length = 0; instructionsName[length]; length++) {
			if (length >= 6) break;
		}

		for (uint16 j = 0; j < 6; j++) {
			if (instructionsName[i][j] == name[j]) checkLength++;
		}

		if (checkLength == length) break;
	}

	return (checkLength == length) ? i : UNKNOWN_INSTRUCTION;
}

enum RMALRegisters findRegisterByName(UGSMGlyphCode name[6]) {
	uint16 i = 0, checkLength = 0;

	for (; i < 8; i++) {
		checkLength = 0;

		for (uint16 j = 0; j < 3; j++) {
			if (registersName[i][j] == name[j]) checkLength++;
		}

		if (checkLength == 3) break;
	}

	return (checkLength == 3) ? i : UNKNOWN_REGISTER;
}

bool nameIsInstructionName(UGSMGlyphCode name[6]) {
	uint16 i = 0, length = 0, checkLength = 0;

	for (; i < 18; i++) {
		checkLength = 0;

		for (length = 0; instructionsName[length]; length++) {
			if (length >= 6) break;
		}

		for (uint16 j = 0; j < 6; j++) {
			if (instructionsName[i][j] == name[j]) checkLength++;
		}

		if (checkLength == length) break;
	}

	return checkLength == length;
}

bool nameIsRegisterName(UGSMGlyphCode name[6]) {
	uint16 i = 0, checkLength = 0;

	for (; i < 8; i++) {
		checkLength = 0;

		for (uint16 j = 0; j < 3; j++) {
			if (registersName[i][j] == name[j]) checkLength++;
		}

		if (checkLength == 3) break;
	}

	return checkLength == 3;
}

void RMALTokenizeWord(void) {
	UGSMGlyphCode name[6] = { 0 };

	uint16 tempPos = 0;

	UGSMGlyphCode current = UGSMGlyphToLowerCase(RMALPeek(0));

	while (UGSMGlyphIsLetterOrDigit(current) && tempPos < 6 && RMALPos < RMALLength) {
		name[tempPos] = current;

		tempPos++;

		current = UGSMGlyphToLowerCase(RMALNext());
	}

	if (nameIsInstructionName(name)) {
		RMALTokens[tokenPos].type = INSTRUCTION;

		RMALTokens[tokenPos].instruction = findInstructionByName(name);
	}

	else if (nameIsRegisterName(name)) {
		RMALTokens[tokenPos].type = REGISTER;

		RMALTokens[tokenPos].value.reg = findRegisterByName(name);
	}

	else {
		RMALTokens[tokenPos].type = RMALLABELNAME;

		for (uint16 i = 0; i < 6; i++) {
			RMALTokens[tokenPos].labelName[i] = name[i];
		}
	}

	tokenPos++;
}

void RMALTokenizeNumber(void) {
	int32 number = 0;

	bool bMinus = RMALPeek(0) == UGSM_CHAR_MINUS_SIGN;

	UGSMGlyphCode current = RMALNext();

	while (UGSMGlyphIsDigit(current)) {
		number *= 10;

		number += (int32)(current - 19);

		current = RMALNext();
	}

	if (bMinus) number = -number;

	RMALTokens[tokenPos].type = RMAL_TOKEN_VALUE_TYPE_NUMBER;

	RMALTokens[tokenPos].value.signNumber = number;

	tokenPos++;
}

void RMALTokenizeComment(void) {
	UGSMGlyphCode current = RMALNext();

	while (current != 30) {
		current = RMALNext();
	}

	RMALNext();
}

UGSMGlyphCode RMALNext(void) {
	RMALPos++;

	UGSMGlyphCode result = RMALPeek(0);

	if (result == 1) {
		RMALPosy++;

		RMALPosx = 1;
	}

	else RMALPosx++;

	return result;
}

UGSMGlyphCode RMALPeek(int32 relativePosition) {
	int32 position = RMALPos + relativePosition;

	if (position >= RMALLength) return 0;

	else if (position < 0) position = 0;

	return RMALCode[position];
}

void RMALTokensView() {
	for (uint16 i = 0; i < tokenPos; i++) {
		RMALToken token = RMALTokens[i];

		switch (token.type) {
			case RMAL_TOKEN_VALUE_TYPE_INSTRUCTION:
				putString(instructionsName[token.value.instruction]);
			break;

			case RMAL_TOKEN_VALUE_TYPE_REGISTER:
				putString(registersName[token.value.reg]);
			break;

			case RMAL_TOKEN_VALUE_TYPE_NUMBER:
				putString(token.value.number);
			break;

			case RMAL_TOKEN_VALUE_TYPE_SIGN_NUMBER:
				putX32Integer(token.value.signNumber);
			break;

			case RMAL_TOKEN_VALUE_TYPE_COMMA:
				putChar(UGSM_CHAR_COMMA);
			break;

			case RMAL_TOKEN_VALUE_TYPE_LABEL_NAME:
				putString(token.label.labelName);
			break;

			case RMAL_TOKEN_VALUE_TYPE_COLON:
				putChar(UGSM_CHAR_COLON);
			break;

			case RMAL_TOKEN_VALUE_TYPE_LEFT_BRACKET:
				putChar(UGSM_CHAR_LEFT_BRACKET);
			break;

			case RMAL_TOKEN_VALUE_TYPE_RIGHT_BRACKET:
				putChar(UGSM_CHAR_RIGHT_BRACKET);
			break;
		}

		putChar(UGSM_CHAR_SPACE);
	}
}