#ifndef _RANDOM_OS_DECIMAL_H
#define _RANDOM_OS_DECIMAL_H

#include "core/types.h"

typedef struct Decimal {
	int32 numerator;

	int32 denominator;
} Decimal;

double doubleFromDecimal(Decimal decimal);

Decimal doubleToDecimal(double x);

#endif