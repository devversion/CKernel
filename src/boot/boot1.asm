[BITS 32]
[EXTERN initKernel]

global _start
_start:
	call initKernel

	jmp $
	RET