#ifndef _BCD_H
#define _BCD_H

#include "core/types.h"

#include "core/time.h"

#define ByteBase 1024

// TODO: Написать единую функцию для преобразования числа в строку, включая дробные.

inline uint32 BitsToBytes(uint32 bits) {
    return bits / 8;
}

inline uint32 KBToMB(uint32 KB) {
    return KB / ByteBase;
}

inline uint32 MBToGB(uint32 MB) {
    return MB / ByteBase;
}

inline uint32 BytesToBits(uint32 bytes) {
    return bytes * 8;
}

inline uint32 KBToBytes(uint32 KB) {
    return KB * ByteBase;
}

inline uint32 MBToKB(uint32 MB) {
    return KBToBytes(MB * ByteBase);
}

inline uint32 GBToMB(uint32 GB) {
    return MBToKB(GB * ByteBase);
}

inline uint32 MBToBytes(uint32 MB) {
    return KBToBytes(MBToKB(MB));
}

inline uint32 GBToBytes(uint32 GB) {
    return MBToBytes(GBToMB(GB));
}

inline uint32 BytesToKB(uint32 bytes) {
    return bytes / ByteBase;
}

inline uint32 BytesToMB(uint32 bytes) {
    return KBToMB(BytesToKB(bytes));
}

inline uint32 BytesToGB(uint32 bytes) {
    return MBToGB(BytesToMB(bytes));
}

uint32 toBCD(uint32 num);

uint32 fromBCD(uint32 num);

Hour hourToBCD(Hour hour);

Hour hourFromBCD(Hour hour);

inline uint32 bitIndexToMask(uint8 bitIndex) {
    return 1U << bitIndex;
}

inline void enableBit(uint32* value, uint8 bitIndex) {
    if (bitIndex >= 32); // TODO: Handle error

    *value |= bitIndexToMask(bitIndex);
}

inline void disableBit(uint32* value, uint8 bitIndex) {
    if (bitIndex >= 32); // TODO: Handle error

    *value &= ~bitIndexToMask(bitIndex);
}

inline uint32 checkBit(uint32 value, uint8 bitIndex) {
    if (bitIndex >= 32); // TODO: Handle error

    return value & bitIndexToMask(bitIndex);
}

inline uint8 getByteIndex(uint32 value) {
    return value / 8;
}

inline uint8 getBitIndex(uint32 value) {
    return value % 8;
}

#endif