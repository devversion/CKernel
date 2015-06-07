; ##########################
; 		    STAGE 2
; ##########################
[BITS 16]
[ORG 0x1000]

; ##########################
;          REAL MODE
; ##########################
global RealMode
RealMode:
	
	; INIT
	mov ah, 0x00
	mov al, 3h
	int 10h

	; ENABLE A20
	mov al, 2
	out 0x92, al

	; LOAD GDT
	cli

	mov ax, cs
	mov ds, ax
	mov ss, ax
	mov fs, ax
	mov gs, ax

	lgdt [gdtr]

	; ENABLE GDT

	mov ah, 0x00
	int 16h

	mov eax, cr0
	or al, 1
	mov cr0, eax

	jmp codesel:ProtectedMode

	RET

; ##########################
; 		  GDT
; ##########################

gdtr:
   dw gdt_end - gdt - 1
   dd gdt
gdt:
   dd 0, 0
codesel equ $-gdt
   dw 0xFFFF
   dw 0x0000
   db 0x00
   db 0x9A
   db 0xCF
   db 0x00
datasel equ $-gdt
   dw 0xFFFF
   dw 0x0000
   db 0x00
   db 0x92
   db 0xCF
   db 0x00
gdt_end:

; ##########################
;		PROTECTED MODE
; ##########################
[BITS 32]
ProtectedMode:

	mov ax, datasel
	mov ds, ax
	mov ss, ax
	mov esp, 0x90000

	jmp $

	RET

; ##########################
;	      SIGNATURE
; ##########################
TIMES 512 - ($ - $$) db 0