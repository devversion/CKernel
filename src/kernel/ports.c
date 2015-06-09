unsigned char in(unsigned short _port) {
	unsigned char result;
	__asm__ ("in %%dx, %%al" : "=a" (result) : "d" (_port));
	return result;
}

void out(unsigned short _port, unsigned char _data) {
	__asm__ ("out %%al, %%dx" : : "a" (_data), "d" (_port));
}