#include "drivers/memory/ram.h"

#include "core/basic_types.h"

#include "drivers/multiboot/multiboot_types.h"

#include "std/std.h"

#include "math/bit_math.h"

#include "math/math.h"

#include "exceptions/exception.h"

#define TABLE_MAX_SIZE 32

static size_t ram_size = 0;

static bool initialized = false;

static size_t table[TABLE_MAX_SIZE] = { 0 }; // Таблица перехода

static byte reserve_table[TABLE_MAX_SIZE / 8] = { 0 }; // Таблица для проверки резервирования участков памяти в таблице перехода

static size_t table_size = 0; // Кол-во адресов в таблице

static size_t last_addr = 0;

void RAM_init(multibootInfo* info) {
	if (initialized) return;

	ram_size = 0;

	for (uint32 i = 0; i < info->mmap_length; i += sizeof(struct multibootMMapEntry)) {
		multibootMMapEntry* mapEntry = (struct multibootMMapEntry*)(info->mmap_addr + i);
		
		if (mapEntry->type != MULTIBOOT_MEMORY_AVAILABLE) continue;

		ram_size += mapEntry->len_low;

		if (table_size < TABLE_MAX_SIZE)
			table[table_size++] = mapEntry->addr_low;
	}

	initialized = true;
}

size_t RAM_getSize() {
	return ram_size;
}

static MemoryHeader* getHeader(void* _mem) {
	byte* mem = _mem;

	if (mem <= sizeof(MemoryHeader)) return nullptr;
	
	return mem - sizeof(MemoryHeader);
}

static MemoryHeader* getNextRegion(void* mem) {
	if (mem == nullptr) return nullptr;

	MemoryHeader* header = getHeader(mem);

	if (header == nullptr) return nullptr;

	return mem + header->size;
}

static MemoryHeader* getNextFreeRegion(MemoryHeader* header) {
	if (header == nullptr) return nullptr;

	while (!(header->status & MEMORY_STATUS_FREE) &&
			header->status != MEMORY_STATUS_UNUSED &&
			header->size != 0) {
		header += header->size;
	}

	return header;
}

static MemoryHeader* getFreeRegion(size_t size) {
	if (size == 0) return nullptr;

	size_t i = 0, next_reg_addr = last_addr;

	for (; i < table_size; i++) {
		next_reg_addr = (i + 1) >= table_size ? ram_size : table[i + 1];

		byte bits = reserve_table[i / 8];

		if (!checkBitU8(bits, i % 8)) break;
	}

	MemoryHeader* header = (MemoryHeader*)table[i];

	header = getNextFreeRegion(header);

	return header;
}

void* malloc(size_t size) {
	if (size == 0) return nullptr;

	MemoryStatus status = MEMORY_STATUS_ACTIVE;
	
	MemoryHeader* header = getFreeRegion(size);

	if (header == nullptr) return nullptr;

	void* result = header + sizeof(MemoryHeader);

	return result;
}

void* calloc(size_t cnt, size_t elem_size) {
	size_t size = cnt * elem_size;

	void* result = malloc(size);

	if (result == nullptr) return nullptr;

	memset(result, 0, size);

	return result;
}

void* realloc(void* mem, size_t size) {
	if (mem == nullptr) {
		if (size == 0) {
			free(mem);

			return nullptr;
		}

		return malloc(size);
	}

	MemoryHeader* header = getHeader(mem);

	if (header->size == size) return mem;
}

void free(void* mem) {
	if (mem == nullptr) return;

	MemoryHeader* header = getHeader(mem);

	if (header == nullptr) return;

	header->status = MEMORY_STATUS_FREE;
}

bool RAM_isValidMemory(void* addr) {
	if (addr <= sizeof(MemoryHeader)) return false;

	MemoryHeader* header = addr - sizeof(MemoryHeader);

	return header->size > 0 && 
			header->status & MEMORY_STATUS_ACTIVE;
}