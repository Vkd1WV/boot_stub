#ifndef _CONFIG_H
#define _CONFIG_H

/*===========================================================================*
 *		This section contains user-settable parameters		     *
 *===========================================================================*/


//GENERAL

/* Minix release and version numbers. */
#define OS_RELEASE "2.0"
#define OS_VERSION "0"

// System application options
#define _SYS_APPLICATION DESKTOP

#define DESKTOP  0
#define SERVER   1
#define MOBILE   2
#define EMBEDDED 3

#define _REAL_TIME 0	// build specifically for realtime system


#endif /* _CONFIG_H */
