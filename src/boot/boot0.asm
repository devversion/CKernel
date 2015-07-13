[ORG 0x7C00]
[BITS 16]

global start
start:

	xor ax, ax
	mov es, ax
	mov ds, ax
	mov ds, ax
	mov ss, ax

	; CLEAR SCREEN
	mov ax, 0003h
	int 10h 

	; STACK POINT
	mov bp, 0x8000
	mov sp, bp

	; BOOT DRIVE
	mov [BOOT_DRIVE], dl
	mov dh, SECTORS
	mov bx, KERNEL_OFFSET

	LoadKernel:
		push dx

		mov ah, 0x02
		mov al, dh
		mov ch, 0
		mov cl, 2
		mov dh, 0
		int 0x13

		jc LoadKernel

		pop dx

		cmp al, dh
		jne LoadKernel

	call LoadGDT

	jmp $
	
	RET

; METHODS
LoadGDT:
	cli

	lgdt [gdt_desc]

	mov eax, cr0
	or eax, 1
	mov cr0, eax

	mov ax, DATA_SEG
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	jmp CODE_SEG:InitProtected

	RET

[BITS 32]
InitProtected:

	call KERNEL_OFFSET

	jmp $

	RET


; VARIABLES
BOOT_DRIVE: db 0
KERNEL_OFFSET equ 0x1000
SECTORS equ 15

; GDT
gdt:                
gdt_null:
    dd 0
    dd 0
gdt_cs:
    dw 0xffff
    dw 0
    db 0
    db 10011010b
    db 11001111b
    db 0
gdt_ds:
    dw 0xffff
    dw 0
    db 0
    db 10010010b
    db 11001111b
    db 0
gdt_end:

gdt_desc:
    dw gdt_end - gdt - 1
    dd gdt

CODE_SEG equ gdt_cs - gdt
DATA_SEG equ gdt_ds - gdt

times 510 -( $ - $$ ) db 0
dw 0xAA55