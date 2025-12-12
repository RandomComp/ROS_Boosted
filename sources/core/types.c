#include "core/types.h"

#include "core/math.h"

#define MAX_STEPS 15

String int64ToString(int64 x) {
    String result = newString();
}

String uint64ToString(uint64 x) {

}

String int32ToString(int32 x) {

}

String uint32ToString(uint32 x) {

}

String charToString(Char x) {

}

void stringConcatenate(String* a, String b) {

}

String stringFromT(T x) {
    switch (x.type) {
        case T_TYPE_INT8:   return int32ToString((int32)x.value.numX8);
        case T_TYPE_INT16:  return int32ToString((int32)x.value.numX16);
        case T_TYPE_INT32:  return int32ToString(x.value.numX32);
        
        case T_TYPE_UINT8:  return uint32ToString((uint32)x.value.numUX8);
        case T_TYPE_UINT16: return uint32ToString((uint32)x.value.numUX16);
        case T_TYPE_UINT32: return uint32ToString(x.value.numUX32);

        case T_TYPE_INT64:  return int64ToString(x.value.numX64);
        case T_TYPE_UINT64: return uint64ToString(x.value.numUX64);

        case T_TYPE_CHAR:   return charToString(x.value.ch);
        case T_TYPE_STRING: return x.value.str;
    }

    //warn(UNKNOWN_T_TYPE_WARNING);
}

T T_Add(T a, T b) {
    switch (a.type) {
        case T_TYPE_INT8: return addInt32WithT((int32)a.value.numX8, b);
        case T_TYPE_INT16: return addInt32WithT((int32)a.value.numX16, b);
        case T_TYPE_INT32: return addInt32WithT((int32)a.value.numX32, b);
        case T_TYPE_INT64: return addInt64WithT(a.value.numX64, b);
        
        case T_TYPE_UINT8: return addUInt32WithT((uint32)a.value.numUX8, b);
        case T_TYPE_UINT16: return addUInt32WithT((uint32)a.value.numUX16, b);
        case T_TYPE_UINT32: return addUInt32WithT((uint32)a.value.numUX32, b);
        case T_TYPE_UINT64: return addUInt64WithT(a.value.numUX64, b);

        case T_TYPE_CHAR: return addCharWithT(a.value.ch, b);
        case T_TYPE_STRING: return addStringWithT(a.value.str, b);
    }
} // Складывание a и b.

T T_Sub(T a, T b) {
    switch (a.type) {
        case T_TYPE_INT8: return;
        case T_TYPE_INT16: return;
        case T_TYPE_INT32: return;
        case T_TYPE_INT64: return;
        case T_TYPE_UINT8: return;
        case T_TYPE_UINT16: return;
        case T_TYPE_UINT32: return;
        case T_TYPE_UINT64: return;
        case T_TYPE_CHAR: return;
        case T_TYPE_STRING: return;
    }
} // Вычитание a и b.

T T_Mul(T a, T b) {
    switch (a.type) {
        case T_TYPE_INT8: return;
        case T_TYPE_INT16: return;
        case T_TYPE_INT32: return;
        case T_TYPE_INT64: return;
        case T_TYPE_UINT8: return;
        case T_TYPE_UINT16: return;
        case T_TYPE_UINT32: return;
        case T_TYPE_UINT64: return;
        case T_TYPE_CHAR: return;
        case T_TYPE_STRING: return;
    }
} // Умножение a и b.

T T_Div(T a, T b) {
    switch (a.type) {
        case T_TYPE_INT8: return;
        case T_TYPE_INT16: return;
        case T_TYPE_INT32: return;
        case T_TYPE_INT64: return;
        case T_TYPE_UINT8: return;
        case T_TYPE_UINT16: return;
        case T_TYPE_UINT32: return;
        case T_TYPE_UINT64: return;
        case T_TYPE_CHAR: return;
        case T_TYPE_STRING: return;
    }
} // Деление a и b.

T T_Mod(T a, T b) {
    switch (a.type) {
        case T_TYPE_INT8: return;
        case T_TYPE_INT16: return;
        case T_TYPE_INT32: return;
        case T_TYPE_INT64: return;
        case T_TYPE_UINT8: return;
        case T_TYPE_UINT16: return;
        case T_TYPE_UINT32: return;
        case T_TYPE_UINT64: return;
        case T_TYPE_CHAR: return;
        case T_TYPE_STRING: return;
    }
} // Взятие остатка от деления a и b.

T T_Preinc(T a, T b) {
    switch (a.type) {
        case T_TYPE_INT8: return;
        case T_TYPE_INT16: return;
        case T_TYPE_INT32: return;
        case T_TYPE_INT64: return;
        case T_TYPE_UINT8: return;
        case T_TYPE_UINT16: return;
        case T_TYPE_UINT32: return;
        case T_TYPE_UINT64: return;
        case T_TYPE_CHAR: return;
        case T_TYPE_STRING: return;
    }
} // Преинкремент, ++i, сначала увеличивает, потом возвращает.

T T_Postinc(T a, T b) {
    switch (a.type) {
        case T_TYPE_INT8: return;
        case T_TYPE_INT16: return;
        case T_TYPE_INT32: return;
        case T_TYPE_INT64: return;
        case T_TYPE_UINT8: return;
        case T_TYPE_UINT16: return;
        case T_TYPE_UINT32: return;
        case T_TYPE_UINT64: return;
        case T_TYPE_CHAR: return;
        case T_TYPE_STRING: return;
    }
} // Постинкремент, i++, сначала возвращает, потом увеличивает.

T T_Predec(T a, T b) {
    switch (a.type) {
        case T_TYPE_INT8: return;
        case T_TYPE_INT16: return;
        case T_TYPE_INT32: return;
        case T_TYPE_INT64: return;
        case T_TYPE_UINT8: return;
        case T_TYPE_UINT16: return;
        case T_TYPE_UINT32: return;
        case T_TYPE_UINT64: return;
        case T_TYPE_CHAR: return;
        case T_TYPE_STRING: return;
    }
} // Предекремент, --i, сначала уменьшает, потом возвращает.

T T_Postdec(T a, T b) {
    switch (a.type) {
        case T_TYPE_INT8: return;
        case T_TYPE_INT16: return;
        case T_TYPE_INT32: return;
        case T_TYPE_INT64: return;
        case T_TYPE_UINT8: return;
        case T_TYPE_UINT16: return;
        case T_TYPE_UINT32: return;
        case T_TYPE_UINT64: return;
        case T_TYPE_CHAR: return;
        case T_TYPE_STRING: return;
    }
} // Постдекремент, i--, сначала возвращает, потом уменьшает.

double doubleFromDecimal(Decimal decimal) {
    return (double)decimal.numerator / (double)decimal.denominator;
}

Decimal doubleToDecimal(double x) {
    uint8 step = 0;

    double denominator = 1.0f;

    while (getFirstNumberAfterDecimalPoint(x * denominator) != 0 && step < MAX_STEPS) {
        denominator *= 10.0f;

        step++;
    }

    return (Decimal){.numerator = (int32)(x * denominator), 
                     .denominator = (int32)denominator
                    };
}