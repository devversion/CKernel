void memset(void *addr, unsigned char value, unsigned int len) {
	char *end = addr + len;
	char *cur = (char *) addr;
	while (cur < end) {
		*cur = value;
		cur++;
	}
}