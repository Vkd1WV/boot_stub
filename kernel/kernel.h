/* This is the master header for the kernel.  It includes some other files
 * and defines the principal constants.
 */
#define _POSIX_SOURCE      1	/* tell headers to include POSIX stuff */
#define _MINIX             1	/* tell headers to include MINIX stuff */
#define _SYSTEM            1	/* tell headers that this is the kernel */

/* The following are so basic, all the *.c files get them automatically. */
#include <sys/cfg.h>			/* MUST be first */
#include <sys/typedefs.h>
#include <sys/syslib.h>
#include <sys/errno.h>
#include <string.h>

#include "typedefs.h"




#include "const.h"
#include "proto.h"
#include "glo.h"


