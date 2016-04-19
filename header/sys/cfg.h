#ifndef OS_CONFIG_H
#define OS_CONFIG_H

/*===========================================================================*
 *		This section contains user-settable parameters		     *
 *===========================================================================*/


//GENERAL

/* Minix release and version numbers. */
#define OS_RELEASE "0"
#define OS_VERSION "0"
#define OS_NAME

// System application options
#define _SYS_APPLICATION DESKTOP

#define DESKTOP  0
#define SERVER   1
#define MOBILE   2
#define EMBEDDED 3

#define _REAL_TIME 0	// build specifically for realtime system

#ifndef __i386__
#error "This needs to be compiled with a ix86-elf compiler"
#endif

#ifdef __arm__
#endif // __arm__

#ifdef __x86_64__
#endif // __x86_64__


#endif /* OS_CONFIG_H */
