#include "core/types.h"

#include "core/math.h"

#define MAX_STEPS 15

double doubleFromDecimal(Decimal decimal) {
    return (double)decimal.numerator / (double)decimal.denominator;
}

Decimal doubleToDecimal(double x) {
    uint8 step = 0;

    double denominator = 1.0f;

    while (getNumberAfterDecimalPoint(x * denominator) != 0 && step < MAX_STEPS) {
        denominator *= 10.0f;

        step++;
    }

    return (Decimal){(int64)(x * denominator), (int64)denominator};
}