#include "core/types.h"

#include "core/math.h"

uint32 toBCD(uint32 x) {
	if (x < 10) return x;

	uint32 result = 0;

	for (uint8 i = 0; x != 0; i++) {
		result += (x % 10) * pow(16, i); // x * (1 << (i * 4)) тоже самое что и pow(16, i), поскольку pow(16, i) это также pow(2, i * 4)

		x /= 10;
	}

	return result;
}

uint32 fromBCD(uint32 x) {
	uint32 result = 0;

	for (uint8 i = 0; x != 0; i++) {
		result += (x % 16) * pow(10, i);

		x /= 16;
	}

	return result;
}

uint64 toBCDU64(uint64 x) {
	if (x < 10) return x;

	uint64 result = 0;

	for (uint8 i = 0; x != 0; i++) {
		result += (x % 10) * pow(16, i); // x * (1 << (i * 4)) тоже самое что и pow(16, i), поскольку pow(16, i) это также pow(2, i * 4)

		x /= 10;
	}

	return result;
}

uint64 fromBCDU64(uint64 x) {
	uint64 result = 0;

	for (uint8 i = 0; x != 0; i++) {
		result += (x % 16) * pow(10, i);

		x /= 16;
	}

	return result;
}

Hour hourToBCD(Hour hour) {
	Hour result = 0;

	

	return result;
}

Hour hourFromBCD(Hour hour) {
	Hour result = 0;

	

	return result;
}