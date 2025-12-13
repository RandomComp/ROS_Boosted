#include "core/screen.h"

#include "core/types.h"

#include "drivers/high-level/vbe.h"

#include "drivers/low-level/base/mem.h"

#include "charset/ugsm.h"

#include "charset/abc.h"

// VBE variables

extern uint32 vidmemaddr; // Адрес видеопамяти выбранного видеорежима VBE.

extern uint32 vidmode; // Выбранный видеорежим VBE.

extern uint8 vidchannels; // Кол-во каналов выбранного видеорежима VBE.

const uint32 screenResolutionSizeInbytes = width * height * 4; // Вычисление размера в байтах разрешения экрана.

static bool bScreenInitialized = false; // Флаг инициализации экрана.

uint32 framebuffer[screenResolutionSizeInbytes] = { 0 };

uint32 viewbuffer[screenResolutionSizeInbytes] = { 0 };

void ScreenInit() {
	if (bScreenInitialized) return;

	if (VBESetup(width, height))
		VBESetMode(vidmode | 0x4000);

	bScreenInitialized = true;
}

void fastClear(uint8 backgroundColor) {
	memset(framebuffer, backgroundColor, screenResolutionSizeInbytes);
}

void clear(uint32 backgroundColor) {
	for (uint32 i = 0; i < screenResolutionSizeInbytes; i++) {
		framebuffer[i] = backgroundColor;
	}
}

void swap() {
	memcpy((uint8*)vidmemaddr, viewbuffer, screenResolutionSizeInbytes);

	memcpy(viewbuffer, framebuffer, screenResolutionSizeInbytes);
}