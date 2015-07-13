#include "bridge/ports.h"
#include "drivers/idt.h"
#include "graphics/display.h"
#include "drivers/rtc.h"

void initKernel() {
	printLine("--- START KERNEL INITIALIZATION ---");
	printLine("GDT: Computer running in Portected Mode.");
	printLine("SYS: Running with 32-Bit architecture.");

	initIDT();
	initRTC();

	printLine("--- END KERNEL INITIALIZATION ---");

	/*char buffer[10];
	itoa(getDay(), buffer, 10);

	printLine(buffer);
*/
}