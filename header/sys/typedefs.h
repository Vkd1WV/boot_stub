// System-wide data type and macro definitions

#ifndef _TYPEDEF_H
#define _TYPEDEF_H

#include "cfg.h"

//hopefully these are compiler constructs, otherwise check inttypes.h

//SIGNED
typedef char     int8_t;
typedef short    int16_t;
typedef int      int32_t;
typedef long int int64_t;

//UNSIGNED
typedef unsigned char     uint8_t;
typedef unsigned short    uint16_t;
typedef unsigned int      uint32_t;
typedef unsigned long int uint64_t;

/* Minimum of signed integral types.  */
#define INT8_MIN		(-0x80)
#define INT16_MIN		(-0x8000)
#define INT32_MIN		(-0x80000000)
#define INT64_MIN		(-0x8000000000000000)

/* Maximum of signed integral types.  */
#define INT8_MAX		(0x7F)
#define INT16_MAX		(0x7FFF)
#define INT32_MAX		(0x7FFFFFFF)
#define INT64_MAX		(0x7FFFFFFFFFFFFFFF)

/* Maximum of unsigned integral types.  */
#define UINT8_MAX		(0xFF)
#define UINT16_MAX		(0xFFFF)
#define UINT32_MAX		(0xFFFFFFFF)
#define UINT64_MAX		(0xFFFFFFFFFFFFFFFF)

#if _WORD_SIZE == 2
#define INT_MIN   INT16_MIN		/* minimum value of a 16-bit int */
#define INT_MAX   INT16_MAX		/* maximum value of a 16-bit int */
#define UINT_MAX  UINT16_MAX	/* maximum value of an unsigned 16-bit int */
#endif

#if _WORD_SIZE == 4
#define INT_MIN   INT32_MIN		/* minimum value of a 32-bit int */
#define INT_MAX   INT32_MAX		/* maximum value of a 32-bit int */
#define UINT_MAX  UINT32_MAX	/* maximum value of an unsigned 32-bit int */
#endif

#if _WORD_SIZE == 8
#define INT_MIN   INT64_MIN		/* minimum value of a 32-bit int */
#define INT_MAX   INT64_MAX		/* maximum value of a 32-bit int */
#define UINT_MAX  UINT64_MAX	/* maximum value of an unsigned 32-bit int */
#endif

#if _MAX_SIZE == 2
typedef int16_t  int_max;
typedef uint16_t uint_max;
#endif

#if _MAX_SIZE == 4
typedef int32_t  int_max;
typedef uint32_t uint_max;
#endif

#if _MAX_SIZE == 8
typedef int64_t  int_max;
typedef uint64_t uint_max;
#endif

typedef unsigned int uint;

#define NULL    ((void *)0)
#define EXIT_FAILURE       1	/* standard error return using exit() */
#define EXIT_SUCCESS       0	/* successful return using exit() */

#define TRUE  1
#define FALSE 0
typedef enum {false, true} bool;

#ifndef _SIZE_T
#define _SIZE_T
typedef uint_max size_t;
#endif

#ifndef _SSIZE_T
#define _SSIZE_T
typedef int ssize_t;
#endif

#ifndef _WCHAR_T
#define _WCHAR_T
typedef char wchar_t;		/* type expanded character set */
#endif

#ifndef _TIME_T
#define _TIME_T
typedef int_max time_t;		   /* time in sec since 1 Jan 2000 0000 GMT */
#endif

#ifndef _CLOCK_T
#define _CLOCK_T
typedef int_max clock_t;		   /* unit for system accounting */
#endif

#ifndef _SIGSET_T
#define _SIGSET_T
typedef uint_max sigset_t;
#endif

/* Types used in disk, inode, etc. data structures. */
typedef int16_t  dev_t;	   /* holds (major|minor) device pair */
typedef int8_t   gid_t;	   /* group id */
typedef int      pid_t;	   /* process id (must be signed) */
typedef int16_t  uid_t;	   /* user id */
typedef uint16_t ino_t; 	   /* i-node number */
typedef uint16_t mode_t;	   /* file type and permissions bits */
typedef int8_t   nlink_t;	   /* number of links to a file */
typedef uint_max off_t;	   /* offset within a file */
typedef uint_max zone_t;	   /* zone number */
typedef uint_max block_t;	   /* block number */
typedef uint_max bit_t;	   /* bit number in a bit map */
typedef uint16_t zone1_t;	   /* zone number for V1 file systems */
typedef uint16_t bitchunk_t; /* collection of bits in a bitmap */


/* ANSI C makes writing down the promotion of unsigned types very messy.  When
 * sizeof(short) == sizeof(int), there is no promotion, so the type stays
 * unsigned.  When the compiler is not ANSI, there is usually no loss of
 * unsignedness, and there are usually no prototypes so the promoted type
 * doesn't matter.  The use of types like Ino_t is an attempt to use ints
 * (which are not promoted) while providing information to the reader.
 */

//#if _EM_WSIZE == 2 || !defined(_ANSI)
//typedef unsigned int      Ino_t;
//typedef unsigned int    Zone1_t;
//typedef unsigned int Bitchunk_t;
//typedef unsigned int      U16_t;
//typedef unsigned int  Mode_t;

//#else /* _EM_WSIZE == 4, or _EM_WSIZE undefined, or _ANSI defined */
//typedef int	          Ino_t;
//typedef int 	        Zone1_t;
//typedef int	     Bitchunk_t;
//typedef int	          U16_t;
//typedef int           Mode_t;

//#endif /* _EM_WSIZE == 2, etc */
 
// Signal handler type, e.g. SIG_IGN   why is this here?"????
typedef void (*sighandler_t) (int);


/* Type definitions. */
typedef unsigned int vir_clicks; /* virtual  addresses and lengths in clicks */
typedef unsigned long phys_bytes;/* physical addresses and lengths in bytes */
typedef unsigned int phys_clicks;/* physical addresses and lengths in clicks */

#if (CHIP == INTEL)
typedef unsigned int vir_bytes;	/* virtual addresses and lengths in bytes */
#endif

#if (CHIP == M68000)
typedef unsigned long vir_bytes;/* virtual addresses and lengths in bytes */
#endif

#if (CHIP == SPARC)
typedef unsigned long vir_bytes;/* virtual addresses and lengths in bytes */
#endif

/* Types relating to messages. */
#define M1                 1
#define M3                 3
#define M4                 4
#define M3_STRING         14

typedef struct {int m1i1, m1i2, m1i3; char *m1p1, *m1p2, *m1p3;} mess_1;
typedef struct {int m2i1, m2i2, m2i3; long m2l1, m2l2; char *m2p1;} mess_2;
typedef struct {int m3i1, m3i2; char *m3p1; char m3ca1[M3_STRING];} mess_3;
typedef struct {long m4l1, m4l2, m4l3, m4l4, m4l5;} mess_4;
typedef struct {char m5c1, m5c2; int m5i1, m5i2; long m5l1, m5l2, m5l3;}mess_5;
typedef struct {int m6i1, m6i2, m6i3; long m6l1; sighandler_t m6f1;} mess_6;

typedef struct {
  int m_source;			/* who sent the message */
  int m_type;			/* what kind of message is it */
  union {
	mess_1 m_m1;
	mess_2 m_m2;
	mess_3 m_m3;
	mess_4 m_m4;
	mess_5 m_m5;
	mess_6 m_m6;
  } m_u;
} message;

/* The following defines provide names for useful members. */
#define m1_i1  m_u.m_m1.m1i1
#define m1_i2  m_u.m_m1.m1i2
#define m1_i3  m_u.m_m1.m1i3
#define m1_p1  m_u.m_m1.m1p1
#define m1_p2  m_u.m_m1.m1p2
#define m1_p3  m_u.m_m1.m1p3

#define m2_i1  m_u.m_m2.m2i1
#define m2_i2  m_u.m_m2.m2i2
#define m2_i3  m_u.m_m2.m2i3
#define m2_l1  m_u.m_m2.m2l1
#define m2_l2  m_u.m_m2.m2l2
#define m2_p1  m_u.m_m2.m2p1

#define m3_i1  m_u.m_m3.m3i1
#define m3_i2  m_u.m_m3.m3i2
#define m3_p1  m_u.m_m3.m3p1
#define m3_ca1 m_u.m_m3.m3ca1

#define m4_l1  m_u.m_m4.m4l1
#define m4_l2  m_u.m_m4.m4l2
#define m4_l3  m_u.m_m4.m4l3
#define m4_l4  m_u.m_m4.m4l4
#define m4_l5  m_u.m_m4.m4l5

#define m5_c1  m_u.m_m5.m5c1
#define m5_c2  m_u.m_m5.m5c2
#define m5_i1  m_u.m_m5.m5i1
#define m5_i2  m_u.m_m5.m5i2
#define m5_l1  m_u.m_m5.m5l1
#define m5_l2  m_u.m_m5.m5l2
#define m5_l3  m_u.m_m5.m5l3

#define m6_i1  m_u.m_m6.m6i1
#define m6_i2  m_u.m_m6.m6i2
#define m6_i3  m_u.m_m6.m6i3
#define m6_l1  m_u.m_m6.m6l1
#define m6_f1  m_u.m_m6.m6f1

struct mem_map {
  vir_clicks mem_vir;		/* virtual address */
  phys_clicks mem_phys;		/* physical address */
  vir_clicks mem_len;		/* length */
};

struct iorequest_s {
  long io_position;		/* position in device file (really off_t) */
  char *io_buf;			/* buffer in user space */
  int io_nbytes;		/* size of request */
  unsigned short io_request;	/* read, write (optionally) */
};

typedef struct {
  vir_bytes iov_addr;		/* address of an I/O buffer */
  vir_bytes iov_size;		/* sizeof an I/O buffer */
} iovec_t;

typedef struct {
  vir_bytes cpv_src;		/* src address of data */
  vir_bytes cpv_dst;		/* dst address of data */
  vir_bytes cpv_size;		/* size of data */
} cpvec_t;

/* MM passes the address of a structure of this type to KERNEL when
 * do_sendsig() is invoked as part of the signal catching mechanism.
 * The structure contain all the information that KERNEL needs to build
 * the signal stack.
 */
struct sigmsg {
  int sm_signo;			/* signal number being caught */
  unsigned long sm_mask;	/* mask to restore when handler returns */
  vir_bytes sm_sighandler;	/* address of handler */
  vir_bytes sm_sigreturn;	/* address of _sigreturn in C library */
  vir_bytes sm_stkptr;		/* user stack pointer */
};

#define MESS_SIZE (sizeof(message))	/* might need usizeof from fs here */
#define NIL_MESS ((message *) 0)

struct psinfo {		/* information for the ps(1) program */
  uint16_t nr_tasks, nr_procs;	/* NR_TASKS and NR_PROCS constants. */
  vir_bytes proc, mproc, fproc;	/* addresses of the main process tables. */
};



#endif
