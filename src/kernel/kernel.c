const unsigned char* VGA_ADDRESS = (unsigned char*) 0xB8000;
const unsigned int VGA_WIDTH = 80;
const unsigned int VGA_HEIGHT = 25;

const unsigned int INDEX_REGISTER = 0x3D4;
const unsigned int DATA_REGISTER = 0x3D5;

// ASSEMBLY IMPLENTATION
unsigned char in(unsigned short _port) {
	unsigned char result;
	__asm__ ("in %%dx, %%al" : "=a" (result) : "d" (_port));
	return result;
}

void out(unsigned short _port, unsigned char _data) {
	__asm__ ("out %%al, %%dx" : : "a" (_data), "d" (_port));
}


// KERNEL FUNCTIONS

void setCursorPositon(const int position) {
	out(INDEX_REGISTER, 14);
	out(DATA_REGISTER, position >> 8);
	out(INDEX_REGISTER, 15);
	out(DATA_REGISTER, position);
}

short getCursorPosition() {
	short offset;
	out(INDEX_REGISTER, 14);
	offset = in(DATA_REGISTER) << 8;
	out(INDEX_REGISTER, 15);
	offset |= in(DATA_REGISTER);
	return offset;	
}

void clearScreen() {
	unsigned char* vidmem = (unsigned char*) VGA_ADDRESS;

	unsigned int i = 0;
	while (i < (VGA_HEIGHT * VGA_WIDTH)) {
		*vidmem++ = 0;
		*vidmem++ = 0x07;
		i++;
	}
	setCursorPositon(0);
}

void print(const char* _message) {
	unsigned char* vidmem = (unsigned char*) VGA_ADDRESS;
	unsigned short offset = getCursorPosition();
	unsigned long i = 0;

	vidmem += offset * 2;

	while (_message[i] != 0) {
		*vidmem++ = _message[i];
		*vidmem++ = 0x07;
		i++;
	}

	offset += i;
	setCursorPositon(offset);
}

void initKernel() {
	clearScreen();

	print("Herzlich Willkommen auf dem C++ Kernel von PaulGap <3");
}