#include "drivers/high-level/keyboardps2.h"

#include "drivers/low-level/base/idt.h"

#include "charset/ugsm.h"

#include "charset/abc.h"

#include "core/std.h"

#include "drivers/low-level/io/io.h"

extern uint32 foregroundColor;

bool bKeyboardPS2Initialized = false;

bool bKeyboardPS2Available = false;

bool bKeyboardPS2Updated = false;

bool bKeyboardPS2CapsLock = false;

bool bKeyboardPS2Shift = false;

const UGSMGlyphCode QWERTY[] = {
	[SCANCODE_1]						= UGSM_CHAR_1,
	[SCANCODE_2]						= UGSM_CHAR_2,
	[SCANCODE_3]						= UGSM_CHAR_3,
	[SCANCODE_4]						= UGSM_CHAR_4,
	[SCANCODE_5]						= UGSM_CHAR_5,
	[SCANCODE_6]						= UGSM_CHAR_6,
	[SCANCODE_7]						= UGSM_CHAR_7,
	[SCANCODE_8]						= UGSM_CHAR_8,
	[SCANCODE_9]						= UGSM_CHAR_9,
	[SCANCODE_0]						= UGSM_CHAR_0,
	[SCANCODE_MINUS_SIGN] 				= UGSM_CHAR_MINUS_SIGN,
	[SCANCODE_EQUAL] 					= UGSM_CHAR_EQUAL_SIGN,
	[SCANCODE_BACKSPACE]				= UGSM_CHAR_BACKSPACE,
	[SCANCODE_TAB]						= UGSM_CHAR_TAB,
	[SCANCODE_Q]						= UGSM_CHAR_Q,
	[SCANCODE_W]						= UGSM_CHAR_W,
	[SCANCODE_E]						= UGSM_CHAR_E,
	[SCANCODE_R]						= UGSM_CHAR_R,
	[SCANCODE_T]						= UGSM_CHAR_T,
	[SCANCODE_Y]						= UGSM_CHAR_Y,
	[SCANCODE_U]						= UGSM_CHAR_U,
	[SCANCODE_I]						= UGSM_CHAR_I,
	[SCANCODE_O]						= UGSM_CHAR_O,
	[SCANCODE_P]						= UGSM_CHAR_P,
	[SCANCODE_LEFT_BRACKET]				= UGSM_CHAR_LEFT_BRACKET,
	[SCANCODE_RIGHT_BRACKET] 			= UGSM_CHAR_RIGHT_BRACKET,
	[SCANCODE_ENTER]					= UGSM_CHAR_NEW_LINE,
	[SCANCODE_A]						= UGSM_CHAR_A,
	[SCANCODE_S]						= UGSM_CHAR_S,
	[SCANCODE_D]						= UGSM_CHAR_D,
	[SCANCODE_F]						= UGSM_CHAR_F,
	[SCANCODE_G]						= UGSM_CHAR_G,
	[SCANCODE_H]						= UGSM_CHAR_H,
	[SCANCODE_J]						= UGSM_CHAR_J,
	[SCANCODE_K]						= UGSM_CHAR_K,
	[SCANCODE_L]						= UGSM_CHAR_L,
	[SCANCODE_SEMICOLON]				= UGSM_CHAR_SEMICOLON,
	[SCANCODE_QUOTE]					= UGSM_CHAR_QUOTE,
	[SCANCODE_BACK_TICK]				= UGSM_CHAR_BACK_TICK,
	[SCANCODE_BACKSLASH]				= UGSM_CHAR_BACKSLASH,
	[SCANCODE_Z]						= UGSM_CHAR_Z,
	[SCANCODE_X]						= UGSM_CHAR_X,
	[SCANCODE_C]						= UGSM_CHAR_C,
	[SCANCODE_V]						= UGSM_CHAR_V,
	[SCANCODE_B]						= UGSM_CHAR_B,
	[SCANCODE_N]						= UGSM_CHAR_N,
	[SCANCODE_M]						= UGSM_CHAR_M,
	[SCANCODE_COMMA]					= UGSM_CHAR_COMMA,
	[SCANCODE_DOT]						= UGSM_CHAR_DOT,
	[SCANCODE_SLASH]					= UGSM_CHAR_SLASH,
	[SCANCODE_NUMBER_PAD_ASTERISK]		= UGSM_CHAR_ASTERISK,
	[SCANCODE_SPACE]					= UGSM_CHAR_SPACE,
	[SCANCODE_NUMBER_PAD_7]				= UGSM_CHAR_7,
	[SCANCODE_NUMBER_PAD_8]				= UGSM_CHAR_8,
	[SCANCODE_NUMBER_PAD_9]				= UGSM_CHAR_9,
	[SCANCODE_NUMBER_PAD_MINUS_SIGN]	= UGSM_CHAR_MINUS_SIGN,
	[SCANCODE_NUMBER_PAD_4]				= UGSM_CHAR_4,
	[SCANCODE_NUMBER_PAD_5]				= UGSM_CHAR_5,
	[SCANCODE_NUMBER_PAD_6]				= UGSM_CHAR_6,
	[SCANCODE_NUMBER_PAD_PLUS_SIGN] 	= UGSM_CHAR_PLUS_SIGN,
	[SCANCODE_NUMBER_PAD_1]				= UGSM_CHAR_1,
	[SCANCODE_NUMBER_PAD_2]				= UGSM_CHAR_2,
	[SCANCODE_NUMBER_PAD_3]				= UGSM_CHAR_3,
	[SCANCODE_NUMBER_PAD_0]				= UGSM_CHAR_0,
	[SCANCODE_NUMBER_PAD_DOT]			= UGSM_CHAR_DOT
};

UGSMGlyphCode QWERTYToShiftQWERTY[] = {
	[UGSM_CHAR_1] = 			UGSM_CHAR_EXCLAMATION_MARK,
	[UGSM_CHAR_2] = 			UGSM_CHAR_AT_SIGN,
	[UGSM_CHAR_3] = 			UGSM_CHAR_NUMBER_SIGN,
	[UGSM_CHAR_4] = 			UGSM_CHAR_DOLLAR_SIGN,
	[UGSM_CHAR_5] = 			UGSM_CHAR_PERCENT_SIGN,
	[UGSM_CHAR_6] = 			UGSM_CHAR_CIRCUMFLEX,
	[UGSM_CHAR_7] = 			UGSM_CHAR_AMPERSAND,
	[UGSM_CHAR_8] = 			UGSM_CHAR_ASTERISK,
	[UGSM_CHAR_9] = 			UGSM_CHAR_LEFT_PAREN,
	[UGSM_CHAR_0] = 			UGSM_CHAR_RIGHT_PAREN,
	[UGSM_CHAR_MINUS_SIGN] = 	UGSM_CHAR_UNDERSCORE,
	[UGSM_CHAR_EQUAL_SIGN] = 	UGSM_CHAR_PLUS_SIGN,
	[UGSM_CHAR_Q] = 			UGSM_CHAR_BIG_Q,
	[UGSM_CHAR_W] = 			UGSM_CHAR_BIG_W,
	[UGSM_CHAR_E] = 			UGSM_CHAR_BIG_E,
	[UGSM_CHAR_R] = 			UGSM_CHAR_BIG_R,
	[UGSM_CHAR_T] = 			UGSM_CHAR_BIG_T,
	[UGSM_CHAR_Y] = 			UGSM_CHAR_BIG_Y,
	[UGSM_CHAR_U] = 			UGSM_CHAR_BIG_U,
	[UGSM_CHAR_I] = 			UGSM_CHAR_BIG_I,
	[UGSM_CHAR_O] = 			UGSM_CHAR_BIG_O,
	[UGSM_CHAR_P] = 			UGSM_CHAR_BIG_P,
	[UGSM_CHAR_LEFT_BRACKET] = 	UGSM_CHAR_LEFT_BRACE,
	[UGSM_CHAR_RIGHT_BRACKET] = UGSM_CHAR_RIGHT_BRACE,
	[UGSM_CHAR_A] = 			UGSM_CHAR_BIG_A,
	[UGSM_CHAR_S] = 			UGSM_CHAR_BIG_S,
	[UGSM_CHAR_D] = 			UGSM_CHAR_BIG_D,
	[UGSM_CHAR_F] = 			UGSM_CHAR_BIG_F,
	[UGSM_CHAR_G] = 			UGSM_CHAR_BIG_G,
	[UGSM_CHAR_H] = 			UGSM_CHAR_BIG_H,
	[UGSM_CHAR_J] = 			UGSM_CHAR_BIG_J,
	[UGSM_CHAR_K] = 			UGSM_CHAR_BIG_K,
	[UGSM_CHAR_L] = 			UGSM_CHAR_BIG_L,
	[UGSM_CHAR_SEMICOLON] = 	UGSM_CHAR_COLON,
	[UGSM_CHAR_QUOTE] = 		UGSM_CHAR_DOUBLE_QUOTES,
	[UGSM_CHAR_BACK_TICK] = 	UGSM_CHAR_TILDE,
	[UGSM_CHAR_BACKSLASH] = 	UGSM_CHAR_VERTICAL_LINE,
	[UGSM_CHAR_Z] = 			UGSM_CHAR_BIG_Z,
	[UGSM_CHAR_X] = 			UGSM_CHAR_BIG_X,
	[UGSM_CHAR_C] = 			UGSM_CHAR_BIG_C,
	[UGSM_CHAR_V] = 			UGSM_CHAR_BIG_V,
	[UGSM_CHAR_B] = 			UGSM_CHAR_BIG_B,
	[UGSM_CHAR_N] = 			UGSM_CHAR_BIG_N,
	[UGSM_CHAR_M] = 			UGSM_CHAR_BIG_M,
	[UGSM_CHAR_COMMA] = 		UGSM_CHAR_LESS_SIGN,
	[UGSM_CHAR_DOT] = 			UGSM_CHAR_BIG_SIGN,
	[UGSM_CHAR_SLASH] = 		UGSM_CHAR_QUESTION_MARK
};

KeyState keyStates[128] = { KEY_FREE };

KeyState oldKeyStates[128] = { KEY_FREE };

Scancode updatedKey = SCANCODE_NULL;

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

UGSMGlyphCode scancodeToUGSM(Scancode key) {
	UGSMGlyphCode result = QWERTY[key];

	if (bKeyboardPS2Shift) {
		result = QWERTYToShiftQWERTY[result];

		if (bKeyboardPS2CapsLock)
			result = UGSMGlyphToLowerCase(result);
	}

	else if (bKeyboardPS2CapsLock)
		result = UGSMGlyphToUpperCase(result);

	return result;
}