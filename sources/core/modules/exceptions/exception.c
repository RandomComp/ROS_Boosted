#include "exceptions/exception.h"

#include "core/basic_types.h"

#include "exceptions/exception_types.h"

#include "exceptions/warnings/warning.h"

#include "exceptions/errors/error.h"

#include "math/math.h"

#include "std/std.h"

static bool Exception_isValid(Exception ex) {
	if (ex.message.file_name == nullptr || ex.message.func_name == nullptr || 
		ex.message.why == nullptr)
		return false;
	
	switch (ex.type) {
		case EXCEPTION_TYPE_ERROR:
			return INRANGE(ex.value.error, ERROR_FIRST, ERROR_LAST);
		
		case EXCEPTION_TYPE_WARNING:
			return INRANGE(ex.value.warning, WARNING_FIRST, WARNING_LAST);
	}

	return false;
}

void throw(Exception ex) {
	if (!Exception_isValid(ex)) {
		throw(Exception_errorInvalidArgument("An invalid exception was passed."));

		return;
	}
	
	switch (ex.type) {
		case EXCEPTION_TYPE_WARNING:
			Warning_throw(ex.value.warning, ex.message);
		break;

		case EXCEPTION_TYPE_ERROR:
			Error_throw(ex.value.error, ex.message);
		break;
	}

	// TODO: Сделать стэк Exception'ов, и добавлять туда при вызове throw
}

/*
@param expr Утверждение, которое проверяется на true, и если true, то вызов указанного исключения.
@param exception Параметр, определяющий исключение для вызова при верном указанным условием.
@brief Функция проверяет, верно ли указанное условие, если да, то вызывает указанное исключение, если нет -- вызов пропускается

@return Возвращает true если утверждение верно.
*/
void assert(bool expr, ExceptionMessage message) {
	if (expr == true) return;

	printf("Assertion failed!\n");

	printf("File: \"[value: c_str]\"\n", message.file_name);

	printf("Function: [value: c_str]\n", message.func_name);

	printf("Line [value: word]\n", message.line);

	printf("Why: [value: c_str]\n", message.why);

	for (;;);
}