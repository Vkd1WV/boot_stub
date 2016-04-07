// This file contains all the kernel's global variables

/* In the *.h files, declared variables appear with EXTERN in front of them,
 * as in
 *
 *    EXTERN int x;
 *
 * Normally EXTERN is defined as extern, so when they are included in another
 * file, no storage is allocated. Here, by redefining EXTERN as the null string,
 * all the variables are actually declared. All the initialized  variables are
 * also declared here, since
 *
 * extern int x = 4;
 *
 * is not allowed.  If such variables are shared, they must also be declared
 * in one of the *.h files without the initialization.
 */

#define _GLOBAL

#include "kernel.h"
