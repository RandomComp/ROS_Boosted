#include "drivers/hid/keyboardps2.h"

#include "drivers/syscall/idt.h"

#include "tasks/events/event.h"

#include "drivers/io/io.h"

static KeyState keyStates[128] = 		{ KEY_FREE };

static KeyState oldKeyStates[128] = 	{ KEY_FREE };

static Scancode updatedKeys[256] = { SCANCODE_NULL };

static size_t updatedKeysIndex = 0;

static Event* keyboardEvent;

static bool isKeyboardPS2Initialized = false;

void KeyboardPS2_Init(void) {
	if (isKeyboardPS2Initialized) return;

	IDTIRQInstallHandler(1, &KeyboardPS2_ISR);

	keyboardEvent = Event_new();

	isKeyboardPS2Initialized = true;
}

void KeyboardPS2_ISR(struct Registers* regs) {
	bool bIsActive = in8(KEYBOARD_PS2_COMMAND_PORT) & 1;

	if (bIsActive) {
		Scancode scancode = in8(KEYBOARD_PS2_DATA_PORT);

		bool bIsReleased = scancode & 0x80;

		scancode &= 0x7f;

		if (keyStates[scancode] == KEY_FREE) {
			keyStates[scancode] = KEY_PRESSED;
		}

		if (bIsReleased)
			keyStates[scancode] = KEY_RELEASED; // released

		else if (oldKeyStates[scancode] == KEY_RELEASED)
			keyStates[scancode] = KEY_PRESSED; // pressed

		else if (oldKeyStates[scancode] == KEY_PRESSED)
			keyStates[scancode] = KEY_HOLDED; // holded

		Keyboard_EventInfo info = (Keyboard_EventInfo) { 
			.keyState = keyStates[scancode],
			.scancode = scancode
		};
		
		Event_invoke(keyboardEvent, &info);

		oldKeyStates[scancode] = keyStates[scancode];

		updatedKeys[updatedKeysIndex] = scancode;

		updatedKeysIndex++;
	}
}

KeyState getKeyState(Scancode scancode) {
	if ()

	return keyStates[scancode];
}