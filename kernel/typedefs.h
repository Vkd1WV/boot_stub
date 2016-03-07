#ifndef TYPE_H
#define TYPE_H

#include <sys/typedefs.h>

typedef void task_t (void );
typedef int (*rdwt_t) (message *m_ptr );
typedef void (*watchdog_t) (void );

struct tasktab {
	task_t *initial_pc;
	int stksize;
	char name[8];
};

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
typedef unsigned port_t;
typedef unsigned segm_t;
typedef unsigned reg_t;		/* machine register */

/* The stack frame layout is determined by the software, but for efficiency
 * it is laid out so the assembly code to use it is as simple as possible.
 * 80286 protected mode and all real modes use the same frame, built with
 * 16-bit registers.  Real mode lacks an automatic stack switch, so little
 * is lost by using the 286 frame for it.  The 386 frame differs only in
 * having 32-bit registers and more segment registers.  The same names are
 * used for the larger registers to avoid differences in the code.
 */
struct stackframe_s {           /* proc_ptr points here */
#if _WORD_SIZE == 4
  uint16_t gs;                     /* last item pushed by save */
  uint16_t fs;                     /*  ^ */
#endif
  uint16_t es;                     /*  | */
  uint16_t ds;                     /*  | */
  reg_t di;			/* di through cx are not accessed in C */
  reg_t si;			/* order is to match pusha/popa */
  reg_t fp;			/* bp */
  reg_t st;			/* hole for another copy of sp */
  reg_t bx;                     /*  | */
  reg_t dx;                     /*  | */
  reg_t cx;                     /*  | */
  reg_t retreg;		/* ax and above are all pushed by save */
  reg_t retadr;		/* return address for assembly code save() */
  reg_t pc;			/*  ^  last item pushed by interrupt */
  reg_t cs;                     /*  | */
  reg_t psw;                    /*  | */
  reg_t sp;                     /*  | */
  reg_t ss;                     /* these are pushed by CPU during interrupt */
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

#if (CHIP == M68000)
typedef _PROTOTYPE( void (*dmaint_t), (void) );

typedef uint32_t reg_t;		/* machine register */

/* The name and fields of this struct were chosen for PC compatibility. */
struct stackframe_s {
	reg_t retreg;			/* d0 */
	reg_t d1;
	reg_t d2;
	reg_t d3;
	reg_t d4;
	reg_t d5;
	reg_t d6;
	reg_t d7;
	reg_t a0;
	reg_t a1;
	reg_t a2;
	reg_t a3;
	reg_t a4;
	reg_t a5;
	reg_t fp;			/* also known as a6 */
	reg_t sp;			/* also known as a7 */
	reg_t pc;
	uint16_t psw;
	uint16_t dummy;			/* make size multiple of reg_t for system.c */
};

struct fsave {
	struct cpu_state {
		uint16_t i_format;
		uint32_t i_addr;
		uint16_t i_state[4];
	} cpu_state;
	struct state_frame {
		uint8_t frame_type;
		uint8_t frame_size;
		uint16_t reserved;
		uint8_t frame[212];
	} state_frame;
	struct fpp_model {
		uint32_t fpcr;
		uint32_t fpsr;
		uint32_t fpiar;
		struct fpN {
			uint32_t high;
			uint32_t low;
			uint32_t mid;
		} fpN[8];
	} fpp_model;
};
#endif /* (CHIP == M68000) */

#endif /* TYPE_H */
