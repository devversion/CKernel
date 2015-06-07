; ##########################
; 		     MBR
; ##########################
[ORG 0x7C00]
[BITS 16]

; ##########################
;			BOOT
; ##########################

jmp 0x0000:start

start:
	
	; CREATE STACK
	cli
	mov ax, 0x9000
	mov ss, ax
	mov sp, 0
	sti

	; INIT STACK
	mov ax, 0x0000
	mov es, ax
	mov ds, ax

	; CURRENT DEVICE
	mov [bootdrv], dl

	; LOAD KERNEL
	call LoadKernel

	; JUMP TO KERNEL
	mov ax, 0x1000
	mov es, ax
	mov ds, ax
	jmp 0x1000:0x000


; ##########################
;		    METHODS
; ##########################

LoadKernel:
	
	mov ax, 0
	mov dl, [bootdrv]
	int 13h
	jc LoadKernel

	FindSector:
		mov ax, 0x1000
		mov es, ax
		mov bx, 0

		mov ah, 2
		mov al, 5
		mov cx, 2
		mov dh, 0
		mov dl, [bootdrv]
		int 13h
		jc FindSector

	RET

; ##########################
; 		    DATA 
; ##########################

bootdrv db 0

; ##########################
;	      SIGNATURE
; ##########################
TIMES 510 - ($ - $$) db 0
dw 0x0AA55