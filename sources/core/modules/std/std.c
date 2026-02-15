#include "std/std.h"

#include "std/string/string_types.h"

#include "std/string/char_types.h"

#include "charset/cp437/cp437_types.h"

static bool bSTDInitialized = false;

void STD_Init() {
	if (bSTDInitialized) return;

	

	bSTDInitialized = true;
}

void print_str(const String* str) {
	
}

void printf_str(const String* str, ...) {
	
}

void print(const c_str str) {
	
}

void printf(const c_str str, ...) {
	
}

void kmsg(const c_str str) {
	
}

void klog(LogSeverity severity, const c_str str, ...) {
	if (severity == LOG_SEVERITY_INFO)
		kmsg("[INFO] ");
	else if (severity == LOG_SEVERITY_WARNING)
		kmsg("[WARN] ");
	else if (severity == LOG_SEVERITY_ERROR)
		kmsg("[ERROR] ");
	else if (severity == LOG_SEVERITY_CRITICAL)
		kmsg("[FATAL] ");
	
	if (str) kmsg(str);
	
	else kmsg("message not provided.");
}

c_char getch() {
	
}