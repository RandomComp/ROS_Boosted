#ifndef _RANDOM_OS_EXCEPTION_H
#define _RANDOM_OS_EXCEPTION_H

#include "core/basic_types.h"

#include "exceptions/exception_types.h"

#include "exceptions/warnings/warning_types.h"

#include "exceptions/errors/error_types.h"

#define Exception_fromInfo(infoType, infoMsg) ((Exception) { \
	.type = EXCEPTION_TYPE_INFO, \
	.value.info = (infoType), \
	.message.file_name = (__FILE__), \
	.message.func_name = (__func__), \
	.message.line = (__LINE__), \
	.message.why = (infoMsg) } \
)

#define Exception_fromWarning(warn, whyMsg) ((Exception) { \
	.type = EXCEPTION_TYPE_WARNING, \
	.value.warning = (warn), \
	.message.file_name = (__FILE__), \
	.message.func_name = (__func__), \
	.message.line = (__LINE__), \
	.message.why = (whyMsg) } \
)

#define Exception_fromError(err, whyMsg) ((Exception) { \
	.type = EXCEPTION_TYPE_ERROR, \
	.value.error = (err), \
	.message.file_name = (__FILE__), \
	.message.func_name = (__func__), \
	.message.line = (__LINE__), \
	.message.why = (whyMsg) } \
)

#define Exception_warningInvalidArgument(msg) (Exception_fromWarning(WARNING_INVALID_ARGUMENT, msg))

#define Exception_errorInvalidArgument(msg) (Exception_fromError(ERROR_INVALID_ARGUMENT, msg))

void throw(Exception exception);

void assert(bool expr);

#endif