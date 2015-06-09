#include "display.h"

const unsigned char* VGA_ADDRESS = (unsigned char*) 0xB8000;
const unsigned int VGA_WIDTH = 80;
const unsigned int VGA_HEIGHT = 25;
const unsigned int CURSOR_OFFSET = 0x3D4;
const unsigned int CURSOR_DATA = 0x3D5;

void setCursorPositon(const int position) {
	out(CURSOR_OFFSET, 14);
	out(CURSOR_DATA, position >> 8);
	out(CURSOR_OFFSET, 15);
	out(CURSOR_DATA, position);
}

short getCursorPosition() {
	short offset;
	out(CURSOR_OFFSET, 14);
	offset = in(CURSOR_DATA) << 8;
	out(CURSOR_OFFSET, 15);
	offset |= in(CURSOR_DATA);
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

void printChar(unsigned char c) {
	char array[1];
	array[0] = c;
	printString(array);
}

void printString(const char* _message) {
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

void printLine(const char* _message) {
	printString(_message);

	unsigned short offset = getCursorPosition();
	short subtract = VGA_WIDTH - (offset % VGA_WIDTH);
	setCursorPositon(offset + subtract);
}