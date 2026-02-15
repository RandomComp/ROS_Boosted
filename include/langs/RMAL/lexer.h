#ifndef _RANDOM_OS_RMAL_LEXER_H
#define _RANDOM_OS_RMAL_LEXER_H

// Lexer of RMAL ( Random minimal assembly language )

#include "core/basic_types.h"

#include "charset/ugsm/ugsm_types.h"

typedef enum RMAL_InstructionType {
	RMAL_INSTRUCTION_UNKNOWN, // Неизвестная инструкция

	RMAL_INSTRUCTION_NOP, // Ничего не делает
	RMAL_INSTRUCTION_MOV, // Перемещает информацию из регистра/памяти процессора в другой регистр/участок памяти процессораю
	RMAL_INSTRUCTION_PUSH, // Добавляет в конец стэка указанную информацию из регистра/памяти
	RMAL_INSTRUCTION_POP, // Вытаскивает из конца стэка информацию в указанный регистр/памяти.
	RMAL_INSTRUCTION_ADD, // Складывает два значения из регистра/значение из указанной памяти, результат помещает в первый аргумент
	RMAL_INSTRUCTION_SUB, // Вычитает два значения из регистра/значение из указанной памяти, результат помещает в первый аргумент
	RMAL_INSTRUCTION_MUL, // Умножает eax на указанный аргумент и сохраняет в eax
	RMAL_INSTRUCTION_DIV, // 
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
} RMAL_InstructionType;

#define FIRST_RMAL_REGISTER (RMAL_REGISTER_EAX)

#define LAST_RMAL_REGISTER (RMAL_REGISTER_EDI)

#define COUNT_RMAL_REGISTER (LAST_RMAL_REGISTER - FIRST_RMAL_REGISTER)

typedef enum RMAL_Register {
	RMAL_REGISTER_EAX, 		// Accumulator
	RMAL_REGISTER_ECX, 		// Counter
	RMAL_REGISTER_EDX, 		// Data
	RMAL_REGISTER_EBX, 		// Base
	RMAL_REGISTER_ESP, 		// Stack pointer
	RMAL_REGISTER_EBP, 		// Base pointer
	RMAL_REGISTER_ESI, 		// Source index
	RMAL_REGISTER_EDI, 		// Destination index
	
	RMAL_REGISTER_UNKNOWN, 	// Unrecognized register
} RMAL_Register;

typedef enum RMAL_InstructionArgumentType {
	RMAL_INSTRUCTION_ARGUMENT_TYPE_NULL,
	RMAL_INSTRUCTION_ARGUMENT_TYPE_REGISTER,
	RMAL_INSTRUCTION_ARGUMENT_TYPE_NUMBER,
	RMAL_INSTRUCTION_ARGUMENT_TYPE_SIGN_NUMBER,
	RMAL_INSTRUCTION_ARGUMENT_TYPE_ADDRESS,
	RMAL_INSTRUCTION_ARGUMENT_TYPE_LABEL
} RMAL_InstructionArgumentType;

typedef struct RMAL_Label {
	c_str name;

	size_t length;
} RMAL_Label;

typedef struct RMAL_InstructionArgument {
	RMAL_InstructionArgumentType type;

	RMAL_Value value;

	bool hasSquareBrackets; // Флаг наличия квадратных скобок ( скобок индекса )

	RMAL_Label label;
} RMAL_InstructionArgument;

typedef struct RMAL_Instruction {
	RMAL_InstructionType type;

	RMAL_InstructionArgument arguments[2];

	size_t argumentCount;
} RMAL_Instruction;

typedef enum RMAL_TokenValueType {
	RMAL_EOF, 				// Конец файла
	RMAL_INSTRUCTION,		// Инструкция для процессора
	RMAL_REGISTER,			// Регистр памяти процессора
	RMAL_NUMBER,			// Число
	RMAL_LABEL_NAME,		// Название метки
	RMAL_COMMA, 			// ,
	RMAL_COLON, 			// :
	RMAL_LEFT_BRACKET, 		// [
	RMAL_RIGHT_BRACKET 	// ]
} RMAL_TokenValueType;

typedef union RMAL_Value {
	RMAL_Register 		reg;
	uint32				number;
	int32				signNumber;
	RMAL_InstructionType 	instruction;
} RMAL_Value;

typedef struct RMAL_Token {
	RMAL_TokenValueType type;

	RMAL_Value value;
} RMAL_Token;

typedef struct RMAL_Lexer {
	c_str code;

	size_t code_length;

	size_t pos;

	RMAL_Token tokens[128];

	size_t tokenPos;
} RMAL_Lexer;

void RMALTokenize(RMAL_Lexer* self);

RMAL_InstructionType findInstructionByName(c_str name);

RMAL_Register findRegisterByName(c_str name);

void RMALTokenizeWord(RMAL_Lexer* self);

void RMALTokenizeSignNumber(RMAL_Lexer* self);

void RMALTokenizeNumber(RMAL_Lexer* self);

void RMALTokenizeComment(RMAL_Lexer* self);

c_char RMALNext(RMAL_Lexer* self);

c_char RMALPeek(RMAL_Lexer* self, int32 rel);

void RMALTokensView(RMAL_Lexer* self);

#endif