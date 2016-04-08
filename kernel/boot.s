; These are constants to make the mutliboot header

	; FLAGS	required by OS
PALIGN		equ 1 << 0		; align loaded modules on page boundaries
MEMINFO		equ 1 << 1		; provide memory map
VMODE		equ 0 << 2		; video mode table
	; FLAGS	optional
AOUTKLUG	equ 0 << 16		; enable load address header fields. not for ELF

FLAGS			equ PALIGN | MEMINFO | VMODE | AOUTKLUG
MAGIC_NUMBER	equ 0x1BADB002		; 1 bad boot

BOOTSTRAP_STACK_SIZE equ 0x1000

section .multiboot ; this is the multiboot header for GRUB to find
	align 4
	dd MAGIC_NUMBER
	dd FLAGS
	dd -(MAGIC_NUMBER + FLAGS)


;The layout of the Multiboot header must be as follows:
;Offset	Type	Field Name		Note
;0		u32		magic			required
;4		u32		flags			required
;8		u32		checksum		required
;12		u32		header_addr		if flags[16] is set
;16		u32		load_addr		if flags[16] is set
;20		u32		load_end_addr	if flags[16] is set
;24		u32		bss_end_addr	if flags[16] is set
;28		u32		entry_addr		if flags[16] is set
;32		u32		mode_type		if flags[2] is set
;36		u32		width			if flags[2] is set
;40		u32		height			if flags[2] is set
;44		u32		depth			if flags[2] is set

section .bss	; reserve space for a stack
	align 4
	stack_bottom:
	resb BOOTSTRAP_STACK_SIZE
	stack_top:

section .text
	global _start
	extern kernel_entry

;	MACHINE STATE
; EAX    must contain 0x0x2BADB002
; EBX    contains the address of the multiboot information structure
; Sregs  Must be a 32-bit segment with an offset of ‘0’ and a limit of ‘0xFFFFFFFF’
; A20    gate Must be enabled.
; CR0    Bit 31 (PG) cleared. Bit 0 (PE) set.
; EFLAGS Bit 17 (VM) cleared. Bit 9 (IF) cleared.
; All other processor registers and flag bits are undefined.

	_start:
	; setup the stack
	mov esp, stack_top
	
	; push EBX & EAX to the stack
	push ebx
	push eax
	
	call kernel_entry			; call c entry fuction
	
	cli			; clear interrupts
	_hang:
	hlt			; halt the proccessor
	jmp _hang


