#include "core/types.h"

void in8(uint16 port) {
	uint8 data = 0;

	asm volatile ("inb %%dx, %%al" : "=a" (data) : "d" (port));

	return data;
}

void in16(uint16 port) { 
	uint16 data = 0;

	asm volatile ("inw %%dx, %%ax" : "=a" (data) : "d" (port));

	return data;
}

void in32(uint16 port) {
	uint32 data = 0;

	asm volatile ("inl %%dx, %%eax" : "=a" (data) : "d" (port));

	return data;
}

void out8(uint16 port, uint8 data) { 
	asm volatile ("outb %%al, %%dx" : : "a" (data), "d" (port));
}

void out16(uint16 port, uint16 data) { 
	asm volatile ("outw %%ax, %%dx" : : "a" (data), "d" (port));
}

void out32(uint16 port, uint32 data) { 
	asm volatile ("outl %%eax, %%dx" : : "a" (data), "d" (port));
}