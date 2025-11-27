#include "../headers/keyboardps2.h"

#include "../headers/idt.h"

#include "../headers/ugsm.h"

#include "../headers/abc.h"

#include "../headers/std.h"

#include "../headers/io.h"

extern UGSMGlyphSetCode ASCIIOffset;

extern uint32 foregroundColor;

bool bKeyboardPS2Initialized = false;

bool bKeyboardPS2Available = false;

bool bKeyboardPS2Updated = false;

bool bKeyboardPS2CapsLock = false;

bool bKeyboardPS2Shift = false;

// UGSMGlyphCode QWERTYToShiftQWERTY[47] = {
// 	[]
// }; // Сделать преобразование с помощью designated initializers

enum KeyState keyStates[128] = { KEY_FREE };

enum KeyState oldKeyStates[128] = { KEY_FREE };

enum Scancode updatedKey = SCANCODE_NULL;

void KeyboardPS2Init(void) {
	if (bKeyboardPS2Initialized) return;

	IDTIRQInstallHandler(1, &KeyboardPS2Event);

	bKeyboardPS2Initialized = true;
}

void KeyboardPS2Event(struct Registers* regs) {
	if (!bKeyboardPS2Available) {
		uint32 tempForegroundColor = foregroundColor;

		foregroundColor = 0x00ff00;

		UGSMASCIIputString("PS/2 keyboard is detected!\n");

		foregroundColor = tempForegroundColor;

		swap();

		bKeyboardPS2Available = true;
	}

	bool bIsActive = false;

	in8(0x64, &bIsActive);

	if (bIsActive) {
		enum Scancode scancode = 0;

		in8(0x60, &scancode);

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

		if (scancode == SCANCODE_CAPSLOCK && keyStates[scancode] == KEY_PRESSED) {
			bKeyboardPS2CapsLock = !bKeyboardPS2CapsLock;
		}

		else if (scancode == SCANCODE_LEFT_SHIFT && (keyStates[scancode] == KEY_PRESSED || keyStates[scancode] == KEY_RELEASED)) {
			bKeyboardPS2Shift = !bKeyboardPS2Shift;
		}

		oldKeyStates[scancode] = keyStates[scancode];

		updatedKey = scancode;

		bKeyboardPS2Updated = true;
	}
}

UGSMGlyphCode scancodeToUGSM(enum Scancode key) {
	UGSMGlyphCode result = 0;

	if (bKeyboardPS2CapsLock)
		result = UGSMGlyphToUpperCase(result);

	if (bKeyboardPS2Shift) {
		//result = QWERTYToShiftQWERTY[result];

		if (bKeyboardPS2CapsLock)
			result = UGSMGlyphToLowerCase(result);
	}

	return result;
}