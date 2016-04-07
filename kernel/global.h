/* Global variables used in the kernel. */

#ifndef _GLOBAL_H
#define _GLOBAL_H

/* EXTERN is defined as extern except in table.c. */
#ifdef _GLOBAL
#undef  EXTERN
#define EXTERN

#else
#define EXTERN extern
#endif

// variables go here

#endif // _GLOBAL_H
