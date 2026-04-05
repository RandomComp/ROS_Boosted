#ifndef _R_OS_ISR_ERROR_H
#define _R_OS_ISR_ERROR_H

#include "exceptions/isr_errors/isr_error_types.h"

void ISR_throw(ISR_Error errorType, const c_str why);

#endif