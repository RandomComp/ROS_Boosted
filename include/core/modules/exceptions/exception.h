#ifndef _RANDOM_OS_EXCEPTION_H
#define _RANDOM_OS_EXCEPTION_H

#include "core/basic_types.h"

#include "exceptions/exception_types.h"

#include "exceptions/warnings/warning_types.h"

#include "exceptions/errors/error_types.h"

#define Exception_fromWarning(warn, whyMsg) ((Exception) { \
	.type = EXCEPTION_TYPE_WARNING, \
	.value.warning = (warn), \
	.message.moduleName = (__FILE__), \
	.message.line = (__LINE__), \
	.message.why = (whyMsg) } \
)

#define Exception_fromError(err, whyMsg) ((Exception) { \
	.type = EXCEPTION_TYPE_ERROR, \
	.value.error = (err), \
	.message.moduleName = (__FILE__), \
	.message.line = (__LINE__), \
	.message.why = (whyMsg) } \
)

#define Exception_warningInvalidArgument(msg) (Exception_fromWarning(WARNING_INVALID_ARGUMENT, msg))

#define Exception_errorInvalidArgument(msg) (Exception_fromError(ERROR_INVALID_ARGUMENT, msg))

void throw(Exception exception);

void assert(bool expr, Exception exception);

#endif