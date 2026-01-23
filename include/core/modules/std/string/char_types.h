#ifndef _RANDOM_OS_CHAR_TYPES_H
#define _RANDOM_OS_CHAR_TYPES_H

#include "charset/charset.h"

struct Char {
	Charset charset;

	CharUnion ch;
};

#endif