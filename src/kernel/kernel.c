void initKernel() {
	char * vga = (char *) 0xb8000;
	*vga = 'N';
}