#include "core/screen.h"

#include "core/types.h"

#include "drivers/high-level/vbe.h"

#include "drivers/low-level/base/mem.h"

#include "charset/ugsm.h"

// VBE variables

extern uint32 vidmemaddr; // Адрес видеопамяти выбранного видеорежима VBE.

extern uint32 vidmode; // Выбранный видеорежим VBE.

extern uint8 vidchannels; // Кол-во каналов выбранного видеорежима VBE.

const static uint32 screenResolutionSizeInbytes = width * height * 4; // Вычисление размера в байтах разрешения экрана.

static bool bScreenInitialized = false; // Флаг инициализации экрана.

static uint32 firstBuffer[screenResolutionSizeInbytes] = { 0 };

static uint32 secondBuffer[screenResolutionSizeInbytes] = { 0 };

static uint32* framebufferPtr = &firstBuffer;

static uint32* viewbufferPtr = &secondBuffer;

static bool bFirstBufferIsFrameBuffer = true;

uint32* getFrameBufferPtr() {
	return framebufferPtr;
}

void ScreenInit() {
	if (bScreenInitialized) return;

	if (VBESetup(width, height))
		VBESetMode(vidmode | 0x4000);

	bScreenInitialized = true;
}

void fastClear(uint8 backgroundColor) {
	memset(framebufferPtr, backgroundColor, screenResolutionSizeInbytes);
}

void clear(uint32 backgroundColor) {
	for (uint32 i = 0; i < screenResolutionSizeInbytes; i++) {
		framebufferPtr[i] = backgroundColor;
	}
}

void swap() {
	// TODO: Вызов VSYNC

	memcpy((uint8*)vidmemaddr, viewbufferPtr, screenResolutionSizeInbytes);

	framebufferPtr = bFirstBufferIsFrameBuffer ? secondBuffer : firstBuffer;

	viewbufferPtr = bFirstBufferIsFrameBuffer ? firstBuffer : secondBuffer;

	bFirstBufferIsFrameBuffer = !bFirstBufferIsFrameBuffer;
}