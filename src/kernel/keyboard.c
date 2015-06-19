#include "keyboard.h"

unsigned char getLowerChar(unsigned char scancode) {
	return qwertylow[scancode];
}

unsigned char getUpperChar(unsigned char scancode) {
	return qwertyup[scancode];
}

void callKeyboard() {
	unsigned char scancode = in(0x60);

	// HANDLE UPPERCASE
	if ((scancode & 0x80)) {
		if (scancode == 0xAA || scancode == 0xB6) {
			uppercase = 0;
		}
	} else {
		if (scancode == 0x36 || scancode == 0x2A) {
			uppercase = 1;
			return;
		}
	}

	// PRINT CHAR
	if (!(scancode & 0x80)) {
		unsigned char c = (uppercase ? getUpperChar(scancode) : getLowerChar(scancode));

		if (c == '\b') {
			short pos = getCursorPosition() - 1;
			setChar(pos, ' ');
			setCursorPositon(pos);
			return;
		}

		printChar(c);
	}
}