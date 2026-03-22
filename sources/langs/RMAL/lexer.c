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

static void addToken(RMAL_Lexer* this, RMAL_Token token) {
	if (this->tokenPos >= 128) return;

	this->tokens[this->tokenPos] = token;
}

void RMALTokenize(RMAL_Lexer* this) {
	while (this->pos < this->code_length) {
		UGSM_Code current = RMALPeek(this, 0);

		if (UGSMGlyphIsLetter(current)) RMALTokenizeWord(this);

		else if (UGSMGlyphIsDigit(current)) RMALTokenizeNumber(this);

		else if (current == CP437_PLUS_SIGN || current == CP437_MINUS_SIGN)
			RMALTokenizeSignNumber(this);

		else if (current == 15) {
			this->tokens[this->tokenPos].type = RMAL_COMMA;

			this->tokenPos++;

			RMALNext(this);
		}

		else if (current == 62) {
			this->tokens[this->tokenPos].type = RMAL_LEFT_BRACKET;

			this->tokenPos++;

			RMALNext(this);
		}

		else if (current == 64) {
			this->tokens[this->tokenPos].type = RMAL_RIGHT_BRACKET;

			this->tokenPos++;

			RMALNext();
		}

		else if (current == 29) {
			this->tokens[this->tokenPos].type = RMAL_COLON;

			this->tokenPos++;

			RMALNext();
		}

		else if (current == 30) {
			RMALTokenizeComment(this);
		}

		else RMALNext(this); // ignore spaces
	}

	this->tokens[this->tokenPos].type = RMAL_EOF;

	this->tokenPos++;
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

	return (checkLength == length) ? i : RMAL_INSTRUCTION_UNKNOWN;
}

RMAL_Register findRegisterByName(UGSM_Code* name) {
	for (size_t i = 0; i < sizeof(registersName) / sizeof(registersName[0]); i++) {
		if (strncmp(registersName[i], name, 3) == 0)
			return i;
	}

	return RMAL_REGISTER_UNKNOWN;
}

void RMALTokenizeWord(RMAL_Lexer* this) {
	UGSM_Code* name = { 0 };

	uint16 tempPos = 0;

	UGSM_Code current = UGSMGlyphToLowerCase(RMALPeek(0));

	while (UGSMGlyphIsLetterOrDigit(current) && tempPos < 6 && this->pos < this->code_length) {
		name[tempPos] = current;

		tempPos++;

		current = UGSMGlyphToLowerCase(RMALNext(this));
	}

	if (nameIsInstructionName(name)) {
		this->tokens[this->tokenPos].type = RMAL_INSTRUCTION;

		this->tokens[this->tokenPos].value.instruction = findInstructionByName(name);
	}

	else if (nameIsRegisterName(name)) {
		this->tokens[this->tokenPos].type = RMAL_REGISTER;

		this->tokens[this->tokenPos].value.reg = findRegisterByName(name);
	}

	this->tokenPos++;
}

void RMALTokenizeNumber(RMAL_Lexer* this) {
	int32 number = 0;

	bool bMinus = RMALPeek(0) == UGSM_CHAR_MINUS_SIGN;

	UGSM_Code current = RMALNext();

	while (UGSMGlyphIsDigit(current)) {
		number *= 10;

		number += (int32)(current - 19);

		current = RMALNext();
	}

	if (bMinus) number = -number;

	this->tokens[this->tokenPos].type = RMAL_TOKEN_VALUE_TYPE_NUMBER;

	this->tokens[this->tokenPos].value.signNumber = number;

	this->tokenPos++;
}

void RMALTokenizeComment(RMAL_Lexer* this) {
	UGSM_Code current = RMALNext();

	while (current != 30) {
		current = RMALNext();
	}

	RMALNext();
}

UGSM_Code RMALNext(RMAL_Lexer* this) {
	RMALPos++;

	UGSM_Code result = RMALPeek(0);

	if (result == 1) {
		RMALPosy++;

		RMALPosx = 1;
	}

	else RMALPosx++;

	return result;
}

UGSM_Code RMALPeek(RMAL_Lexer* this, int32 relativePosition) {
	int32 position = RMALPos + relativePosition;

	if (position >= RMALLength) return 0;

	else if (position < 0) position = 0;

	return RMALCode[position];
}

void RMALTokensView(RMAL_Lexer* this) {
	for (uint16 i = 0; i < this->tokenPos; i++) {
		RMAL_Token token = this->tokens[i];

		switch (token.type) {
			case RMAL_INSTRUCTION:
				putString(instructionsName[token.value.instruction]);
			break;

			case RMAL_REGISTER:
				putString(registersName[token.value.reg]);
			break;

			case RMAL_NUMBER:
				putString(token.value.number);
			break;

			case RMAL_SIGN_NUMBER:
				putX32Integer(token.value.signNumber);
			break;

			case RMAL_COMMA:
				putChar(UGSM_CHAR_COMMA);
			break;

			case RMAL_COLON:
				putChar(UGSM_CHAR_COLON);
			break;

			case RMAL_LEFT_BRACKET:
				putChar(UGSM_CHAR_LEFT_BRACKET);
			break;

			case RMAL_RIGHT_BRACKET:
				putChar(UGSM_CHAR_RIGHT_BRACKET);
			break;
		}

		putChar(UGSM_CHAR_SPACE);
	}
}