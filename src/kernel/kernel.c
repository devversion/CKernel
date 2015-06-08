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

void println(const char* _message) {
	print(_message);

	unsigned short offset = getCursorPosition();
	short subtract = VGA_WIDTH - (offset % VGA_WIDTH);
	setCursorPositon(offset + subtract);
}

void memset(void *addr, unsigned char value, unsigned int len) {
	char *end = addr + len;
	char *cur = (char *) addr;
	while (cur < end) {
		*cur = value;
		cur++;
	}
}

// ###### INTERRUPT HANDLER ##########
struct idt_entry {
	unsigned short offset_low;
	unsigned short selector;
	unsigned char zero;
	unsigned char flags;
	unsigned short offset_high;
}__attribute((packed));

struct idt_pointer {
	unsigned short limit;
	unsigned int base;
}__attribute((packed));

struct idt_entry idt[256];
struct idt_pointer idtp;

extern void idt_load();
extern void irq1();

void setISR(unsigned char int_num, unsigned long base, unsigned short sel, unsigned char flags) {
    idt[int_num].offset_low = base & 0xFFFF;
    idt[int_num].offset_high = (base >> 16) & 0xFFFF;
    idt[int_num].selector = sel;
    idt[int_num].zero = 0;
    idt[int_num].flags = flags;
}

void remapIRQ() {
	out(0x20, 0x11);
	out(0xA0, 0x11);
	out(0x21, 0x20);
	out(0xA1, 0x28);
	out(0x21, 0x04);
	out(0xA1, 0x02);
	out(0x21, 0x01);
	out(0xA1, 0x01);
	out(0x21, 0x0);
	out(0xA1, 0x0);
}

void callKeyboard() {
	unsigned char scancode;
	scancode = in(0x60);

	print(" KEY ");
}

void installIDT() {
	idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
	idtp.base = (int) &idt;

	remapIRQ();

	memset(&idt, 0, 256);

	setISR(33, (unsigned) irq1, 0x08, 0x8E);

	idt_load();

	// ENABLE KEYBOARD IRQ1
	out(0x21 , 0xFD);
}

// ### END INTERRUPT HANDLER ###

void initKernel() {

	__asm__ volatile("sti");

	installIDT();
	clearScreen();

	println("Herzlich Willkommen auf dem C++ Kernel von PaulGap <3");
	println("Und das ist die zweite Zeile :D");
}