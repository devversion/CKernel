#include "idt.h"

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