#include "ports.h"
#include "idt.h"
#include "display.h"
#include "rtc.h"

void initKernel() {
	printLine("--- START KERNEL INITIALIZATION ---");

	initIDT();
	initRTC();

	printLine("--- END KERNEL INITIALIZATION ---");
}