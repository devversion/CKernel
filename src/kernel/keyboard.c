unsigned char qwertylow[128] = { 0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
unsigned char qwertyup[128] = {
	0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b', '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"'
}

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