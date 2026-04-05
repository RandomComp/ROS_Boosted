#ifndef _R_OS_EXCEPTION_ERROR_H
#define _R_OS_EXCEPTION_ERROR_H

#include "exceptions/errors/error_types.h"

#include "exceptions/exception_types.h"

void Error_throw(Error errorType, ExceptionMessage message);

#endif