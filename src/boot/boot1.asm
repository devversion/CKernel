[BITS 32]
[EXTERN initKernel]
[EXTERN callKeyboard]
[EXTERN idtp]

global _start
global irq1
global idt_load

_start:
	call initKernel

	jmp $
	RET

idt_load:
	lidt [idtp]
	RET

; ##### IRQS ####
irq1:
	call callKeyboard
	mov al, 0x20
	out 0x20, al
	iret