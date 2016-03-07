/* The <errno.h> header defines the numbers of the various errors that can
 * occur during program execution.  They are visible to user programs and 
 * should be small positive integers.  However, they are also used within 
 * MINIX, where they must be negative.  For example, the READ system call is 
 * executed internally by calling do_read().  This function returns either a 
 * (negative) error number or a (positive) number of bytes actually read.
 *
 * To solve the problem of having the error numbers be negative inside the
 * the system and positive outside, the following mechanism is used.  All the
 * definitions are are the form:
 *
 *	#define EPERM		(_SIGN 1)
 *
 * If the macro _SYSTEM is defined, then  _SIGN is set to "-", otherwise it is
 * set to "".  Thus when compiling the operating system, the  macro _SYSTEM
 * will be defined, setting EPERM to (- 1), whereas when when this
 * file is included in an ordinary user program, EPERM has the value ( 1).
 */

#ifndef _ERRNO_H		/* check if <errno.h> is already included */
#define _ERRNO_H		/* it is not included; note that fact */

/* Now define _SIGN as "" or "-" depending on _SYSTEM. */
#ifdef _SYSTEM
#   define _SIGN         -
#   define OK            0
#else
#   define _SIGN         
#endif

extern int errno;		  /* place where the error numbers go */

/* Here are the numerical values of the error numbers. */
#define _NERROR               70  /* number of errors */  

#define EGENERIC      (_SIGN 0x0001)  /* generic error */

// Permission errors
#define EPERM         (_SIGN 0x0010)  /* operation not permitted */
#define EACCES        (_SIGN 0x0010)  /* permission denied */

// Kernel Errors
#define ESRCH         (_SIGN 0x0020)  /* no such process */
#define ENOSYS        (_SIGN 0x0021)  /* function not implemented */
#define EINTR         (_SIGN 0x0022)  /* interrupted function call */
#define E2BIG         (_SIGN 0x0023)  /* arg list too long */
#define ENOEXEC       (_SIGN 0x0024)  /* exec format error */
#define ECHILD        (_SIGN 0x0025)  /* no child process */
#define EAGAIN        (_SIGN 0x0026)  /* resource temporarily unavailable */
#define EBUSY         (_SIGN 0x0027)  /* resource busy */
#define EXDEV         (_SIGN 0x0028)  /* improper link */
#define EINVAL        (_SIGN 0x0029)  /* invalid argument */
#define EDOM          (_SIGN 0x002a)  /* domain error    	(from ANSI C std) */
#define ERANGE        (_SIGN 0x002b)  /* result too large	(from ANSI C std) */
#define EDEADLK       (_SIGN 0x002c)  /* resource deadlock avoided */
#define ENOLCK        (_SIGN 0x002d)  /* no locks available */

#define ESPIPE        (_SIGN 0x0030)  /* invalid seek */
#define EPIPE         (_SIGN 0x0031)  /* broken pipe */
#define ELOCKED       (_SIGN 0x0032)  /* can't send message */
#define EBADCALL      (_SIGN 0x0033)  /* error on send/receive */

// IO Errors
#define EIO           (_SIGN 0x0040)  /* input/output error */
#define ENODEV        (_SIGN 0x0041)  /* no such device */
#define ENXIO         (_SIGN 0x0042)  /* no such device or address */
#define ENOTBLK       (_SIGN 0x0043)  /* Extension: not a block special file */
#define ENOSPC        (_SIGN 0x0044)  /* no space left on device */
#define ENOTTY        (_SIGN 0x0045)  /* inappropriate I/O control operation */

// Memmory Errors
#define EFAULT        (_SIGN 0x0050)  /* bad address */
#define ENOMEM        (_SIGN 0x0051)  /* not enough space */


// File Errors
#define ENOENT        (_SIGN 0x0060)  /* no such file or directory */
#define EBADF         (_SIGN 0x0061)  /* bad file descriptor */
#define EEXIST        (_SIGN 0x0062)  /* file exists */
#define ENOTDIR       (_SIGN 0x0063)  /* not a directory */
#define EISDIR        (_SIGN 0x0064)  /* is a directory */
#define ENFILE        (_SIGN 0x0065)  /* too many open files in system */
#define EMFILE        (_SIGN 0x0066)  /* too many open files */
#define EROFS         (_SIGN 0x0067)  /* read-only file system */
#define EMLINK        (_SIGN 0x0068)  /* too many links */
#define ENAMETOOLONG  (_SIGN 0x0069)  /* file name too long */
#define ENOTEMPTY     (_SIGN 0x006a)  /* directory not empty */
#define EFBIG         (_SIGN 0x006b)  /* file too large */


/* The following errors relate to networking. */
#define EPACKSIZE     (_SIGN 0x0070)  /* invalid packet size for some protocol */
#define EOUTOFBUFS    (_SIGN 0x0071)  /* not enough buffers left */
#define EBADIOCTL     (_SIGN 0x0072)  /* illegal ioctl for device */
#define EBADMODE      (_SIGN 0x0073)  /* badmode in ioctl */
#define EWOULDBLOCK   (_SIGN 0x0074)
#define EBADDEST      (_SIGN 0x0075)  /* not a valid destination address */
#define EDSTNOTRCH    (_SIGN 0x0076)  /* destination not reachable */
#define EISCONN	      (_SIGN 0x0077)  /* all ready connected */
#define EADDRINUSE    (_SIGN 0x0078)  /* address in use */
#define ECONNREFUSED  (_SIGN 0x0079)  /* connection refused */
#define ECONNRESET    (_SIGN 0x007a)  /* connection reset */
#define ETIMEDOUT     (_SIGN 0x007b)  /* connection timed out */
#define EURG	      (_SIGN 0x007c)  /* urgent data present */
#define ENOURG	      (_SIGN 0x007d)  /* no urgent data present */
#define ENOTCONN      (_SIGN 0x007e)  /* no connection (yet or anymore) */
#define ESHUTDOWN     (_SIGN 0x0080)  /* a write call to a shutdown connection */
#define ENOCONN       (_SIGN 0x0081)  /* no such connection */



/* The following error codes are generated by the kernel itself. */
#ifdef _SYSTEM
#define E_BAD_DEST     -1001	/* destination address illegal */
#define E_BAD_SRC      -1002	/* source address illegal */
#define E_TRY_AGAIN    -1003	/* can't send-- tables full */
#define E_OVERRUN      -1004	/* interrupt for task that is not waiting */
#define E_BAD_BUF      -1005	/* message buf outside caller's addr space */
#define E_TASK         -1006	/* can't send to task */
#define E_NO_MESSAGE   -1007	/* RECEIVE failed: no message present */
#define E_NO_PERM      -1008	/* ordinary users can't send to tasks */
#define E_BAD_FCN      -1009	/* only valid fcns are SEND, RECEIVE, BOTH */
#define E_BAD_ADDR     -1010	/* bad address given to utility routine */
#define E_BAD_PROC     -1011	/* bad proc number given to utility */
#endif /* _SYSTEM */

#endif /* _ERRNO_H */
