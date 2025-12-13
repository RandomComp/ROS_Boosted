#ifndef _IO_H
#define _IO_H

#include "core/types.h"

inline uint8 in8(uint16 port) {
	uint8 data = 0;

	asm volatile ("inb %%dx, %%al" : "=a" (data) : "d" (port));

	return data;
}

inline uint16 in16(uint16 port) { 
	uint16 data = 0;

	asm volatile ("inw %%dx, %%ax" : "=a" (data) : "d" (port));

	return data;
}

inline uint32 in32(uint16 port) {
	uint32 data = 0;

	asm volatile ("inl %%dx, %%eax" : "=a" (data) : "d" (port));

	return data;
}

inline void out8(uint16 port, uint8 data) { 
	asm volatile ("outb %%al, %%dx" : : "a" (data), "d" (port));
}

inline void out16(uint16 port, uint16 data) { 
	asm volatile ("outw %%ax, %%dx" : : "a" (data), "d" (port));
}

inline void out32(uint16 port, uint32 data) { 
	asm volatile ("outl %%eax, %%dx" : : "a" (data), "d" (port));
}

#endif