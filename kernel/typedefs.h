#ifndef TYPE_H
#define TYPE_H

#include <sys/typedefs.h>

typedef void task_t        (void );
typedef int  (*rdwt_t)     (message *m_ptr );
typedef void (*watchdog_t) (void );


struct tasktab {
	task_t *initial_pc;
	int stksize;
	char name[8];
};

// memory is mesured (and allocated?) in clicks
// this structure is used to designate an extent of physical memory

// processes access memory in local addresses called vir_clicks
struct memory {
	phys_clicks base;
	phys_clicks size;
};

/* Administration for clock polling. */
struct milli_state {
	unsigned long accum_count;	/* accumulated clock ticks */
	unsigned prev_count;		/* previous clock value */
};

#if (CHIP == INTEL)
/*
Intel chips have:
16x 64-bit General Purpose Registers
	RAX		Accumulator
	RBX
	RCX		Counter for string and loop operations
	RDX		I/O port address
	RSI
	RDI
	RBP		Base Pointer (use to keep track of return instruction pointer)
	RSP		Stack Pointer (Hard)
	R8-15
6x Segment registers         (16-bit) 
	CS		NU
	DS		NU
	SS		NU
	ES		NU
	FS		may be used in 64-bit
	GS		may be used in 64-bit
1x RFLAGS  register          (64-bit)
	Bits 1, 3, 5, 15, and 22 through 31 of this register are reserved.
	0x0000 0000
	ititialized to:
	0x0000 0002
	automatically saved to the Task State Segment on context switch

1x (RIP) Instruction pointer (64-bit)

PUSH / POP decrement & increment the SP
CALL / RET push & pop IP into SP

The first thing each new function should do is set BP to SP
and just before RET set SP to BP
so as not to lose the return instruction pointer

*/
typedef uint16_t sreg_t; // Segment Registers
typedef uint64_t  reg_t; // Other Registers

typedef unsigned port_t;
typedef unsigned segm_t;


/* The stack frame layout is determined by the software, but for efficiency
 * it is laid out so the assembly code to use it is as simple as possible.
 * 80286 protected mode and all real modes use the same frame, built with
 * 16-bit registers.  Real mode lacks an automatic stack switch, so little
 * is lost by using the 286 frame for it.  The 386 frame differs only in
 * having 32-bit registers and more segment registers.  The same names are
 * used for the larger registers to avoid differences in the code.
 */
 
/* A stackframe is used to store the state of the processor whenever there is a
 * context switch. In the case of a function call the stackframe is created,
 * populated, and pushed into the procedure stack at SP. When the OS intterupts a
 * stackframe is stored in the process table.
 */
 
// how does 64-bit affect this?
struct stackframe_s {           /* proc_ptr points here */
	sreg_t gs;      /* last item pushed by save */
	sreg_t fs;      /*  ^ */

	reg_t  di;      /* di through cx are not accessed in C */
	reg_t  si;      /* order is to match pusha/popa */
	reg_t  fp;      /* bp */
	reg_t  st;      /* hole for another copy of sp */
	reg_t  bx;      /*  | */
	reg_t  dx;      /*  | */
	reg_t  cx;      /*  | */
	reg_t  retreg;  /* ax and above are all pushed by save */

	reg_t  retadr;  /* return address for assembly code save() */
	reg_t  pc;      /*  ^  last item pushed by interrupt */
	sreg_t cs;      /*  | NOT USED*/
	reg_t  psw;     /*  | ? */
	reg_t  sp;      /*  | stack pointer*/
	reg_t  ss;      /* these are pushed by CPU during interrupt */

//	reg_t  r8;
//	reg_t  r9;
//	reg_t  r10;
//	reg_t  r11;
//	reg_t  r12;
//	reg_t  r13;
//	reg_t  r14;
//	reg_t  r15;
};

struct segdesc_s {		/* segment descriptor for protected mode */
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_middle;
  uint8_t access;			/* |P|DL|1|X|E|R|A| */
#if _WORD_SIZE == 4
  uint8_t granularity;		/* |G|X|0|A|LIMT| */
  uint8_t base_high;
#else
  uint16_t reserved;
#endif
};

typedef int (*irq_handler_t) (int irq);

#endif /* (CHIP == INTEL) */

#endif /* TYPE_H */
