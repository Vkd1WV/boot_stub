global _start					; indicates where execution should start below
;extern main

; define constants
MAGIC_NUMBER equ 0x1BADB002
FLAGS        equ 0x0
CHECKSUM     equ -MAGIC_NUMBER

KERNEL_STACK_SIZE equ 4096 ; static stack size

section .bss
align 4
kernel_stack:
	resb KERNEL_STACK_SIZE ; grub reserves space for the stack

section .text:
align 4					; indicates 4-byte alignment
	dd MAGIC_NUMBER		; don't know what these are doing?
	dd FLAGS
	dd CHECKSUM

_start:					; this is where the program starts
	mov eax, 0xCAFEBABE
	mov ebx, 0x0
	mov ecx, 0x0
	mov edx, 0x0
	mov esp, kernel_stack + KERNEL_STACK_SIZE ; setup the stack
	
	;call main

;.loop:
;	jmp .loop ; busy waiting
