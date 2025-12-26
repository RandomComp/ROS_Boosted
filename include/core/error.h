#ifndef _RANDOM_OS_ERROR_H
#define _RANDOM_OS_ERROR_H

#include "core/types.h"

#include "core/exception_types.h"

#include "core/error_types.h"

void Error_throw(Error errorType, ExceptionMessage message);

#endif