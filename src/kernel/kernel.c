#include "ports.h"
#include "idt.h"
#include "display.h"

void initKernel() {
	installIDT();
	clearScreen();

	printLine("Herzlich Willkommen auf dem C++ Kernel von PaulGap <3");
	printLine("Und das ist die zweite Zeile :D");
}