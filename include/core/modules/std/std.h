#ifndef _R_OS_STD_H
#define _R_OS_STD_H

#include "core/basic_types.h"

#include "std/string/string_fwd.h"

#include "drivers/memory/ram.h"
#include "builtins/mem.h"

typedef enum LogSeverity {
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR,
	LOG_CRITICAL
} LogSeverity;

void STD_Init();

void print_str(const String* str);

void printf_str(const String* str, ...);

void print(const c_str str);

void printf(const c_str str, ...);

void kmsg(const c_str str, ...); // Выводит текст напрямую в лог ядра

void klog(LogSeverity severity, const c_str str, ...); // Выводит текст напрямую в лог ядра

c_char getch();

#endif