#pragma once
#include "../bridge/ports.h"
#include "../utils/util.h"
#include "keyboard.h"

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

// #### VARS #####
struct idt_entry idt[256];
struct idt_pointer idtp;

//## EXTERN METHODS ###
extern void idt_load();
extern void irq1();

void setISR(unsigned char int_num, unsigned long base, unsigned short sel, unsigned char flags);
void remapIRQ();
void initIDT();