void memset(void *addr, unsigned char value, unsigned int len) {
	char *end = addr + len;
	char *cur = (char *) addr;
	while (cur < end) {
		*cur = value;
		cur++;
	}
}

int convertBCD(int bcd) {
	return (((bcd & 0xF0) >> 4) * 10) + (bcd & 0x0F);
}

char *itoa(int num, char *str, int radix) {
	char sign = 0;
	char temp[17];
	int temp_loc = 0;
	int digit;
	int str_loc = 0;

	if (radix == 10 && num < 0) {
		sign = 1;
		num = -num;
	}

	do {
		digit = (unsigned int)num % radix;
		if (digit < 10) {
			temp[temp_loc++] = digit + '0';
		} else {
			temp[temp_loc++] = digit - 10 + 'A';
		}
		num = (((unsigned int)num) / radix);
	} while ((unsigned int) num > 0);

	if (radix == 10 && sign) {
		temp[temp_loc] = '-';
	} else {
		temp_loc--;
	}

    while (temp_loc >= 0) {
    	str[str_loc++] = temp[temp_loc--];    
    }
    str[str_loc] = 0;

    return str;
}