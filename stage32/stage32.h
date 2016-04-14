/* This is the master header for the kernel.  It includes some other files
 * and defines the principal constants.
 */

#ifndef STAGE32_H
#define STAGE32_H

#define _KERNEL 1	// This is the Kernel

#include "cfg.h"

// Freestanding Compiler headers
//#include <iso646.h>
//#include <stdarg.h>

// Kernel Headers
#include "typedefs.h"
#include "proto.h"
#include "global.h"
#include "debug.h"


#endif // STAGE32_H
