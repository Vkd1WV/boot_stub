; These are constants to make the mutliboot header
ALIGNP			equ 1			; align loaded modules on page boundaries
MEMINFO			equ 1 << 1			; provide memory map
MAGIC_NUMBER	equ 0x1BADB002
FLAGS			equ ALIGNP | MEMINFO
CHECKSUM		equ -(MAGIC_NUMBER + FLAGS)

BOOTSTRAP_STACK_SIZE equ 4096

section .mutliboot ; this is the multiboot header for GRUB to find
	align 4
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM

section .text
	global _start
	extern kernel_entry

	_start:
	mov esp, stack_top	; initialize the stack
	call kernel_entry			; call c entry fuction
	
	cli			; clear interrupts
	_hang:
	hlt			; halt the proccessor
	jmp _hang

section .bss	; reserve space for a stack
	align 4
	stack_bottom:
	resb BOOTSTRAP_STACK_SIZE
	stack_top:
