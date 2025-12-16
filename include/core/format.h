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

inline uint32 bitIndexToMaskU32(uint8 bitIndex) {
    return 1U << (uint32)bitIndex;
}

inline uint64 bitIndexToMaskU64(uint8 bitIndex) {
    return 1ULL << (uint64)bitIndex;
}

inline void enableBitU32(uint32* value, uint8 bitIndex) {
    if (bitIndex >= 32); // TODO: Handle error

    *value |= bitIndexToMaskU32(bitIndex);
}

inline void disableBitU32(uint32* value, uint8 bitIndex) {
    if (bitIndex >= 32); // TODO: Handle error

    *value &= ~bitIndexToMaskU32(bitIndex);
}

inline uint32 checkBitU32(uint32 value, uint8 bitIndex) {
    if (bitIndex >= 32); // TODO: Handle error

    return (value >> bitIndex) & 1;
}

inline void enableBitU64(uint64* value, uint8 bitIndex) {
    if (bitIndex >= 64); // TODO: Handle error

    *value |= bitIndexToMaskU64(bitIndex);
}

inline void disableBitU64(uint64* value, uint8 bitIndex) {
    if (bitIndex >= 64); // TODO: Handle error

    *value &= ~bitIndexToMaskU64(bitIndex);
}

inline bool checkBitU64(uint64 value, uint8 bitIndex) {
    if (bitIndex >= 64); // TODO: Handle error

    return (value >> bitIndex) & 1;
}

inline void enableBitU128(uint128* value, uint8 bitIndex) {
    if (bitIndex >= 128); // TODO: Handle error

    if (bitIndex >= 64) value->hi &= ~bitIndexToMaskU64(bitIndex - 64);

    else                value->lo &= ~bitIndexToMaskU64(bitIndex);
}

inline void disableBitU128(uint128* value, uint8 bitIndex) {
    if (bitIndex >= 128); // TODO: Handle error

    *value &= ~bitIndexToMaskU64(bitIndex); // hi = 0000000000000000000000000000000000000000000000000000000001111011 lo = 0000000000000000000000000000000000000000000000000000000111001000
}

inline bool checkBitU128(uint128 value, uint8 bitIndex) {
    if (bitIndex >= 128); // TODO: Handle error

    return rshUInt128(value, bitIndex) & 1;
}

inline uint8 getByteIndex(uint32 value) {
    return value / 8;
}

inline uint8 getBitIndex(uint32 value) {
    return value % 8;
}

#endif