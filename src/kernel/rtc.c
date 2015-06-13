
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

int getSeconds() {
	out(0x70, 0);
	return convertBCD(in(0x71));
}

int getMinutes() {
	out(0x70, 0x02);
	return convertBCD(in(0x71));
}

int getHours() {
	out(0x70, 0x04);
	return convertBCD(in(0x71));
}

int getDay() {
	out(0x70, 0x07);
	return convertBCD(in(0x71));
}

int getMonth() {
	out(0x70, 0x08);
	return convertBCD(in(0x71));
}

int getYear() {
	out(0x70, 0x09);
	return convertBCD(in(0x71));
}