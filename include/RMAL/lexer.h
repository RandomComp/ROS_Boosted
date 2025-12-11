#ifndef _RMAL_LEXER_H
#define _RMAL_LEXER_H

// Lexer of RMAL ( Random minimal assembly language )

#include "core/types.h"

#include "charset/ugsm.h"

typedef enum RMALTokenValueType {
	RMAL_TOKEN_VALUE_TYPE_INSTRUCTION,		// Инструкция для процессора
	RMAL_TOKEN_VALUE_TYPE_REGISTER,			// Регистр памяти процессора
	RMAL_TOKEN_VALUE_TYPE_NUMBER,			// Число
	RMAL_TOKEN_VALUE_TYPE_LABEL_NAME,		// Название метки
	RMAL_TOKEN_VALUE_TYPE_COMMA, 			// ,
	RMAL_TOKEN_VALUE_TYPE_COLON, 			// :
	RMAL_TOKEN_VALUE_TYPE_LEFT_BRACKET, 	// [
	RMAL_TOKEN_VALUE_TYPE_RIGHT_BRACKET, 	// ]
	RMAL_TOKEN_VALUE_TYPE_EOF 				// end of file
} RMALTokenValueType;

typedef enum RMALInstructions {
	RMAL_INSTRUCTION_NOP, // Ничего не делает
	RMAL_INSTRUCTION_MOV, // Перемещает информацию из регистра/памяти процессора в другой регистр/участок памяти процессораю
	RMAL_INSTRUCTION_PUSH, // Добавляет в конец стэка указанную информацию из регистра/памяти
	RMAL_INSTRUCTION_POP, // Вытаскивает из конца стэка информацию в указанный регистр/памяти.
	RMAL_INSTRUCTION_ADD, // Складывает 
	RMAL_INSTRUCTION_SUB,
	RMAL_INSTRUCTION_MUL,
	RMAL_INSTRUCTION_DIV,
	RMAL_INSTRUCTION_INC,
	RMAL_INSTRUCTION_DEC,
	RMAL_INSTRUCTION_INX8,
	RMAL_INSTRUCTION_INX16,
	RMAL_INSTRUCTION_INX32,
	RMAL_INSTRUCTION_OUTX8,
	RMAL_INSTRUCTION_OUTX16,
	RMAL_INSTRUCTION_OUTX32,
	RMAL_INSTRUCTION_JMP,
	RMAL_INSTRUCTION_RET,
	RMAL_INSTRUCTION_LABEL,
	RMAL_INSTRUCTION_EOF,

	RMAL_INSTRUCTION_UNKNOWN
} RMALInstructions;

typedef enum RMALRegisters {
	RMAL_REGISTER_EAX, 		// Accumulator
	RMAL_REGISTER_ECX, 		// Counter
	RMAL_REGISTER_EDX, 		// Data
	RMAL_REGISTER_EBX, 		// Base
	RMAL_REGISTER_ESP, 		// Stack pointer
	RMAL_REGISTER_EBP, 		// Base pointer
	RMAL_REGISTER_ESI, 		// Source index
	RMAL_REGISTER_EDI, 		// Destination index

	RMAL_REGISTER_UNKNOWN 	// Unrecognized register
} RMALRegisters;

typedef enum RMALInstructionArgumentType {
	RMAL_INSTRUCTION_ARGUMENT_TYPE_NULL,
	RMAL_INSTRUCTION_ARGUMENT_TYPE_REGISTER,
	RMAL_INSTRUCTION_ARGUMENT_TYPE_NUMBER,
	RMAL_INSTRUCTION_ARGUMENT_TYPE_SIGN_NUMBER,
	RMAL_INSTRUCTION_ARGUMENT_TYPE_ADDRESS,
	RMAL_INSTRUCTION_ARGUMENT_TYPE_LABEL
} RMALInstructionArgumentType;


typedef union RMALValue {
	RMALRegisters 		reg;
	uint32				number;
	int32				signNumber;
	RMALInstructions 	instruction;
} RMALValue;

typedef struct RMALLabel {
	UGSMGlyphCode labelName[6]; // Название метки

	uint8 labelLength; 			// Длина названия метки
} RMALLabel;

typedef struct RMALInstructionArgument {
	RMALInstructionArgumentType type;

	RMALValue value;

	bool hasSquareBrackets; // Флаг наличия квадратных скобок ( скобок индекса )

	RMALLabel label;
} RMALInstructionArgument;

typedef struct RMALInstruction {
	RMALInstructions type;

	RMALInstructionArgument arguments[2];

	uint16 argumentsNumber;

	RMALLabel label;
} RMALInstruction;

typedef struct RMALToken { // maybe instruction, register or number
	RMALTokenValueType type;

	RMALValue value;

	RMALLabel label;
} RMALToken;

void RMALTokenize(UGSMGlyphCode argCode[384]);

RMALInstructions findInstructionByName(UGSMGlyphCode name[6]);

RMALRegisters findRegisterByName(UGSMGlyphCode name[6]);

bool nameIsInstructionName(UGSMGlyphCode name[6]);

bool nameIsRegisterName(UGSMGlyphCode name[6]);

void RMALTokenizeWord();

void RMALTokenizeSignNumber();

void RMALTokenizeNumber();

void RMALTokenizeComment();

UGSMGlyphCode RMALNext();

UGSMGlyphCode RMALPeek(int32 relativePosition);

void RMALTokensView(void);

#endif