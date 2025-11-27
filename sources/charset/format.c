#include "core/types.h"

#include "core/time.h"

extern RegisterB registerB;

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
	Hour result = hour;

	if (!(registerB & 0x02) && hour >= 12) {
		result %= 12;
		
		result |= 0x80;
	}

	return (result % 10) | ((result / 10) << 4);
}

uint32 fromBCD(uint32 num) {
	return (num & 0x0F) + ((num / 16) * 10);
}

Hour hourFromBCD(Hour hour) {
	Hour result = ((hour & 0x0F) + (((hour & 0x70) / 16) * 10)) | (hour & 0x80);

	if (!(registerB & 0x02) && (result & 0x80))
		result = ((result & 0x7F) + 12) % 24;

	return result;
}