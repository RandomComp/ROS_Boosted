#include "core/types.h"

#include "drivers/low-level/io/cmos.h"

uint32 toBCD(uint32 num) {
	if (num == 0) return 0x00;

	uint32 i = 0, result = 0;

	while (num != 0) {
		result += (num % 10) << (i * 4);

		i++;

		num /= 10;
	}

	return result;
}

Hour hourToBCD(Hour hour) {
	Hour result = 0;

	

	return result;
}

uint32 fromBCD(uint32 num) {
	return (num & 0x0F) + ((num / 16) * 10);
}

Hour hourFromBCD(Hour hour) {
	Hour result = 0;

	

	return result;
}