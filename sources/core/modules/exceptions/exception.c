#include "exceptions/exception.h"

#include "exceptions/exception_types.h"

#include "exceptions/warnings/warning.h"

#include "exceptions/errors/error.h"

#include "core/basic_types.h"

#include "drivers/memory/ram.h"

static bool Exception_isValid(Exception ex) {
	if (ex.message.moduleName == 0 || ex.message.why == 0)
		return false;
	
	switch (ex.type) {
		case EXCEPTION_TYPE_ERROR:
			if (ex.value.error >= ERROR_FIRST)
				return false;
		
		case EXCEPTION_TYPE_WARNING:
			if (ex.value.warning >= WARNING_FIRST)
				return false;
			
		default: return false;
	}

	return true;
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
void assert(bool expr, Exception ex) {
	if (expr == true) return;

	throw(ex);

	for (;;);
}