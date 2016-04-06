/* This file contains the main program of MINIX.  The routine main()
 * initializes the system and starts the ball rolling by setting up the proc
 * table, interrupt vectors, and scheduling each task to run to initialize
 * itself.
 *
 * The entries into this file are:
 *   main:		MINIX main program
 *   panic:		abort MINIX due to a fatal error
 */

/*	PROCESSOR INITIAL STATE
EFLAGS			0x0000 0002
EIP				0x0000 FFF0
CR0				0x6000 0010
CR{1,2,3}		0x0000 0000
CS				0xF000, Base=0xFFFF 0000, Limit=0xFFFF, AR=present, R/W
SS,DS,ES,FS,GS	0x0000, Base=0x0000 0000, Limit=0xFFFF, AR=present, R/W
EDX				0xxxxx xxxx contains model information
EAX				0x0000 0000 if BIST is run and finds no faults
EBX,ECX,
ESI,EDI,
EBP,ESP			0x0000 0000

GDTR,IDTR		Base=0x0000 0000, Limit=0xFFFF, AR=present, R/W
LDTR,
Task Register	0x0000, Base=0x0000 0000, Limit=0xFFFF, AR=present, R/W

APIC			Enabled

The first instruction executed is at 0xFFFF FFF0
That code must not contain a far jump, or far call,
or allow an interrupt to occur.
It is an initialization vector that points to memory mapped BIOS

set EM=1, MP=0, NE=1 to disable FPU

caching

interrupt vector table should be loaded at address IDTR for real-mode
before interrupts can be enabled

NMI (non-masking interrupt) must be handled early
*/


/*
Before entering protected mode some data structures must be in memory
a IDT
a GDT
a TSS
a LDT (optional)
at least one page directory

code segment to be executed from protected mode

interrupt and exception hanlers

Initalize registers:
GDTR
IDTR
CR1-4
the MTRR

protected mode is then entered by setting PE=0
*/

/*
Memory Models:
	Flat
	Flat with paging
	Segmented
	Segmented with paging
*/


/*
Processor must be in protected mode with paging enabled to start IA-32e

1. Disable Paging in CR0
2. Enable PAE in CR4
3. Load CR3 (PDBR) with address of Level 4 page map
4. Enable IA-32e by setting IA32_EFER.LME = 1
5. Enable Paging

Update GDTR, IDTR, LDTR, TR to 64-bit tables
interrupts must be disabled for this. including NMI?

*/

#include "main.h"
//#include <signal.h>
//#include <unistd.h>
//#include <minix/callnr.h>
//#include <minix/com.h>
//#include "proc.h"



/*===========================================================================*
 *                                   main                                    *
 *===========================================================================*/
/*int stuff() {*/
/*	clear_fb();*/
/*	(void) kwrite("Kernel Booted", 13);*/
/*	*/
/*	return 0;*/
/*}*/
void main(){
	clear_fb();
	kwrite("Kernel Booted", 13); //FIXME: this line prevents booting
	
	for(;;);
	
}


/*===========================================================================*
 *                                   panic                                   *
 *===========================================================================*/

