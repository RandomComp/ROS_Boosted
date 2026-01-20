#include "core/decimal.h"

#include "core/basic_types.h"

double doubleFromDecimal(Decimal decimal) {
	return (double)decimal.numerator / (double)decimal.denominator;
}

Decimal doubleToDecimal(double x) {
	uint8 step = 0;

	double denominator = 1.0f;

	while (getFirstNumberAfterDecimalPoint(x * denominator) != 0 && step < MAX_DOUBLE_STEPS) {
		denominator *= 10.0f;

		step++;
	}

	return (Decimal){.numerator = (int32)(x * denominator), 
					 .denominator = (int32)denominator
					};
}