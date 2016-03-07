/* Copyright (C) 1995 by Prentice-Hall, Inc.  Permission is hereby granted
 * to redistribute the binary and source programs of this system for
 * educational or research purposes.  For other use, written permission from
 * Prentice-Hall is required.  
 */

#ifndef CONST_H
#define CONST_H

#define HZ	          60	/* clock freq (software settable on IBM-PC) */
#define BLOCK_SIZE      1024	/* # bytes in a disk block */
#define SUPER_USER (uid_t) 0	/* uid_t of superuser */

#define MAJOR	           8	/* major device = (dev>>MAJOR) & 0377 */
#define MINOR	           0	/* minor device = (dev>>MINOR) & 0377 */

#define NULL     ((void *)0)	/* null pointer */
#define CPVEC_NR          16	/* max # of entries in a SYS_VCOPY request */
#define NR_IOREQS	MIN(NR_BUFS, 64)
				/* maximum number of entries in an iorequest */

#define NR_SEGS            3	/* # segments per process */
#define T                  0	/* proc[i].mem_map[T] is for text */
#define D                  1	/* proc[i].mem_map[D] is for data */
#define S                  2	/* proc[i].mem_map[S] is for stack */

/* Process numbers of some important processes. */
#define MM_PROC_NR         0	/* process number of memory manager */
#define FS_PROC_NR         1	/* process number of file system */
#define INET_PROC_NR       2	/* process number of the TCP/IP server */
#define INIT_PROC_NR	(INET_PROC_NR + ENABLE_NETWORKING)
				/* init -- the process that goes multiuser */
#define LOW_USER	(INET_PROC_NR + ENABLE_NETWORKING)
				/* first user not part of operating system */

/* Miscellaneous */
#define BYTE            0377	/* mask for 8 bits */
#define READING            0	/* copy data to user */
#define WRITING            1	/* copy data from user */
#define NO_NUM        0x8000	/* used as numerical argument to panic() */
#define HAVE_SCATTERED_IO  1	/* scattered I/O is now standard */

/* Macros. */
#define MAX(a, b)   ((a) > (b) ? (a) : (b))
#define MIN(a, b)   ((a) < (b) ? (a) : (b))
#define BUILD_BUG_ON(condition) ((void) sizeof(char[1-2*!!(condition)]))

/* Number of tasks. */
#define NR_TASKS	(9 + ENABLE_WINI + ENABLE_SCSI + ENABLE_CDROM \
			+ ENABLE_NETWORKING + 2 * ENABLE_AUDIO)

/* Memory is allocated in clicks. */
#if (CHIP == INTEL)
#define CLICK_SIZE       256	/* unit in which memory is allocated */
#define CLICK_SHIFT        8	/* log2 of CLICK_SIZE */
#endif

#if (CHIP == SPARC) || (CHIP == M68000)
#define CLICK_SIZE	4096	/* unit in which memory is alocated */
#define CLICK_SHIFT	  12	/* 2log of CLICK_SIZE */
#endif

#define click_to_round_k(n) \
	((unsigned) ((((unsigned long) (n) << CLICK_SHIFT) + 512) / 1024))
#if CLICK_SIZE < 1024
#define k_to_click(n) ((n) * (1024 / CLICK_SIZE))
#else
#define k_to_click(n) ((n) / (CLICK_SIZE / 1024))
#endif

#define ABS             -999	/* this process means absolute memory */

/* Flag bits for i_mode in the inode. */
#define I_TYPE          0170000	/* this field gives inode type */
#define I_REGULAR       0100000	/* regular file, not dir or special */
#define I_BLOCK_SPECIAL 0060000	/* block special file */
#define I_DIRECTORY     0040000	/* file is a directory */
#define I_CHAR_SPECIAL  0020000	/* character special file */
#define I_NAMED_PIPE	0010000 /* named pipe (FIFO) */
#define I_SET_UID_BIT   0004000	/* set effective uid_t on exec */
#define I_SET_GID_BIT   0002000	/* set effective gid_t on exec */
#define ALL_MODES       0006777	/* all bits for user, group and others */
#define RWX_MODES       0000777	/* mode bits for RWX only */
#define R_BIT           0000004	/* Rwx protection bit */
#define W_BIT           0000002	/* rWx protection bit */
#define X_BIT           0000001	/* rwX protection bit */
#define I_NOT_ALLOC     0000000	/* this inode is free */

/* Some limits. */
#define MAX_BLOCK_NR  ((block_t) 077777777)	/* largest block number */
#define HIGHEST_ZONE   ((zone_t) 077777777)	/* largest zone number */
#define MAX_INODE_NR      ((ino_t) 0177777)	/* largest inode number */
#define MAX_FILE_POS ((off_t) 037777777777)	/* largest legal file offset */

#define NO_BLOCK              ((block_t) 0)	/* absence of a block number */
#define NO_ENTRY                ((ino_t) 0)	/* absence of a dir entry */
#define NO_ZONE                ((zone_t) 0)	/* absence of a zone number */
#define NO_DEV                  ((dev_t) 0)	/* absence of a device numb */


/* Minimum sizes required by the POSIX P1003.1 standard (Table 2-3). */
#ifdef _POSIX_SOURCE		/* these are only visible for POSIX */
//#define _POSIX_ARG_MAX    4096	/* exec() may have 4K worth of args */
//#define _POSIX_CHILD_MAX     6	/* a process may have 6 children */
//#define _POSIX_LINK_MAX      8	/* a file may have 8 links */
//#define _POSIX_MAX_CANON   255	/* size of the canonical input queue */
//#define _POSIX_MAX_INPUT   255	/* you can type 255 chars ahead */
//#define _POSIX_NAME_MAX     14	/* a file name may have 14 chars */
//#define _POSIX_NGROUPS_MAX   0	/* supplementary group IDs are optional */
//#define _POSIX_OPEN_MAX     16	/* a process may have 16 files open */
//#define _POSIX_PATH_MAX    255	/* a pathname may contain 255 chars */
//#define _POSIX_PIPE_BUF    512	/* pipes writes of 512 bytes must be atomic */
//#define _POSIX_STREAM_MAX    8	/* at least 8 FILEs can be open at once */
//#define _POSIX_TZNAME_MAX    3	/* time zone names can be at least 3 chars */
//#define _POSIX_SSIZE_MAX 32767	/* read() must support 32767 byte reads */

/* Values actually implemented by MINIX (Tables 2-4, 2-5, 2-6, and 2-7). */
/* Some of these old names had better be defined when not POSIX. */
#define _NO_LIMIT        100	/* arbitrary number; limit not enforced */

#define NGROUPS_MAX        0	/* supplemental group IDs not available */
#if _EM_WSIZE > 2
#define ARG_MAX        16384	/* # bytes of args + environ for exec() */
#else
#define ARG_MAX         4096	/* args + environ on small machines */
#endif
#define CHILD_MAX  _NO_LIMIT    /* MINIX does not limit children */
#define LINK_MAX         127	/* # links a file may have */
#define MAX_CANON        255	/* size of the canonical input queue */
#define MAX_INPUT        255	/* size of the type-ahead buffer */
#define PATH_MAX         255	/* # chars in a path name */
#define PIPE_BUF        7168	/* # bytes in atomic write to a pipe */
#define STREAM_MAX        20	/* must be the same as FOPEN_MAX in stdio.h */
#define TZNAME_MAX         3	/* maximum bytes in a time zone name is 3 */
#define SSIZE_MAX      32767	/* max defined byte count for read() */

#endif /* _POSIX_SOURCE */

// arbitrary limits?
#define	BUFSIZ		1024
#define	FOPEN_MAX	20
#define	FILENAME_MAX	256
#define RAND_MAX       32767	/* largest value generated by rand() */
#define MB_CUR_MAX         1	/* max value of multibyte character in MINIX */

#define	DIRBLKSIZ	512	/* size of directory block */

#ifndef DIRSIZ
#define DIRSIZ	FILENAME_MAX
#endif

#endif //CONST_H

