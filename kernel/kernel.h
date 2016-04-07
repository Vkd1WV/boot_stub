/* This is the master header for the kernel.  It includes some other files
 * and defines the principal constants.
 */

#ifndef KERNEL_H
#define KERNEL_H

#define _KERNEL 1	// This is the Kernel

#include "cfg.h"

// Freestanding Compiler headers
//#include <iso646.h>
//#include <stdarg.h>

// Kernel Headers
#include "typedefs.h"
#include "proto.h"
#include "global.h"

#ifndef __i386__
#error "This needs to be compiled with a ix86-elf compiler"
#endif

#endif // KERNEL_H
