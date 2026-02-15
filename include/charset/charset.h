#ifndef _RANDOM_OS_CHARSET_H
#define _RANDOM_OS_CHARSET_H

#include "core/basic_types.h"

#include "charset/ugsm/ugsm_types.h"

#include "charset/cp437/cp437_types.h"

typedef enum Charset {
	CHARSET_UNKNOWN,
	CHARSET_ASCII,
	CHARSET_UGSM,
} Charset;

#endif