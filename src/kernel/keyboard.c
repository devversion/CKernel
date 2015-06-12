unsigned char qwertylow[128] = {
	0, // NULL
	27, // ESC
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',
	'0',
	'-',
	'=',
	'\b', // BACKSPACE
	'\t', // TAB
	'q',
	'w',
	'e',
	'r',
	't',
	'y',
	'u',
	'i',
	'o',
	'p',
	'[',
	']',
	'\n', // ENTER
	0, // LEFT CONTROL
	'a',
	's',
	'd',
	'f',
	'g',
	'h',
	'j',
	'k',
	'l',
	';',
	'\'',
	'`',
	0, // LEFT SHIFT
	'\\',
	'z',
	'x',
	'c',
	'v',
	'b',
	'n',
	'm',
	',',
	'.',
	'/',
	0, // RIGHT SHIFT
	'*',
	0, // LEFT ALT
	' ',
	0, // CAPS LOCK
	0, // F1
	0, // F2
	0, // F3
	0, // F4
	0, // F5
	0, // F6
	0, // F7
	0, // F8
	0, // F9
	0, // F10
	0, // NUM LOCK
	0, // SCROLL LOCK
	0, // KEYPAD 7
	0, // KEYPAD 8
	0, // KEYPAD 9
	0, // KEYPAD -
	0, // KEYPAD 4
	0, // KEYPAD 5
	0, // KEYPAD 6
	0, // KEYPAD +
	0, // KEYPAD 1
	0, // KEYPAD 2
	0, // KEYPAD 3
	0, // KEYPAD 0
	0, // KEYPAD .
	0, // EMPTY
	0, // EMPTY
	0, // EMPTY
	0, // F11
	0, // F12
};


unsigned char getLowerChar(unsigned char scancode) {
	return qwertylow[scancode];
}

unsigned char getUpperChar(unsigned char scancode) {
	//TODO CREATE UPPER CHAR KEYMAP
	return qwertylow[scancode];
}

void callKeyboard() {
	unsigned char scancode = in(0x60);

	if (!(scancode & 0x80)) {
		printChar(getLowerChar(scancode));
	}
}