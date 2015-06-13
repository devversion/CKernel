
const unsigned int RTC_ADRESS = 0x70;
const unsigned int RTC_DATA = 0x71;

void initRTC() {
	printLine("RTC: Starting initialization...");

	out(RTC_ADRESS, 10);
	char data = in(RTC_DATA);
	
	if (data == 0x80) {
		printLine("RTC: Update running. Retrying...");
		initRTC();
	} else {
		printLine("RTC: No update running. Continuing...");
	}
	
	printLine("RTC: Initialization completed.");
}