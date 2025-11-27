#include "../headers/types.h"

uint32 pow(uint8 a, uint8 b) {
    uint32 result = 1;

    while (b--) result *= a;

    return result;
}