#include "langs/RMAL/lexer.h"

#include "core/basic_types.h"

#include "std/std.h"

#include "builtins/mem.h"

#include "charset/cp437/cp437.h"

#include "exceptions/warnings/warning.h"

#include "exceptions/errors/error.h"

const c_str instructionsName[] = {
	"NOP",
	"MOV",
	"PUSH",
	"POP",
	"ADD",
	"SUB",
	"MUL",
	"DIV",
	"INC",
	"DEC",
	"INX8",
	"INX16",
	"INX32",
	"OUTX8",
	"OUTX16",
	"OUTX32",
	"RET"
};

const c_str registersName[] = {
	"EAX",
	"ECX",
	"EDX",
	"EBX",
	"ESP",
	"EBP",
	"ESI",
	"EDI"
};

static void addToken(RMAL_Lexer* self, RMAL_Token token) {
	
}

void RMALTokenize(RMAL_Lexer* self) {
	while (self->pos < self->code_length) {
		UGSM_Code current = RMALPeek(self, 0);

		if (UGSMGlyphIsLetter(current)) RMALTokenizeWord();

		else if (UGSMGlyphIsDigit(current)) RMALTokenizeNumber();

		else if (current == CP437_CHAR_PLUS_SIGN || current == CP437_CHAR_MINUS_SIGN)
			RMALTokenizeSignNumber(self);

		else if (current == 15) {
			RMALTokens[tokenPos].type = RMAL_TOKEN_VALUE_TYPE_COMMA;

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

RMAL_InstructionType findInstructionByName(UGSM_Code name[6]) {
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

RMAL_Register findRegisterByName(UGSM_Code name[6]) {
	uint16 i = 0;

	for (uint16 i = 0; i < 8; i++) {
		checkLength = 0;

		for (uint16 j = 0; j < 3; j++) {
			if (registersName[i][j] == name[j]) checkLength++;
		}

		if (checkLength == 3) break;

		strncmp();
	}

	return UNKNOWN_REGISTER;
}

void RMALTokenizeWord(RMAL_Lexer* self) {
	UGSM_Code name[6] = { 0 };

	uint16 tempPos = 0;

	UGSM_Code current = UGSMGlyphToLowerCase(RMALPeek(0));

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

void RMALTokenizeNumber(RMAL_Lexer* self) {
	int32 number = 0;

	bool bMinus = RMALPeek(0) == UGSM_CHAR_MINUS_SIGN;

	UGSM_Code current = RMALNext();

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

void RMALTokenizeComment(RMAL_Lexer* self) {
	UGSM_Code current = RMALNext();

	while (current != 30) {
		current = RMALNext();
	}

	RMALNext();
}

UGSM_Code RMALNext(RMAL_Lexer* self) {
	RMALPos++;

	UGSM_Code result = RMALPeek(0);

	if (result == 1) {
		RMALPosy++;

		RMALPosx = 1;
	}

	else RMALPosx++;

	return result;
}

UGSM_Code RMALPeek(RMAL_Lexer* self, int32 relativePosition) {
	int32 position = RMALPos + relativePosition;

	if (position >= RMALLength) return 0;

	else if (position < 0) position = 0;

	return RMALCode[position];
}

void RMALTokensView(RMAL_Lexer* self) {
	for (uint16 i = 0; i < tokenPos; i++) {
		RMAL_Token token = RMALTokens[i];

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