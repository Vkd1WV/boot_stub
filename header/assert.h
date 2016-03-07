/* The <assert.h> header contains a macro called "assert" that allows 
 * programmers to put assertions in the code.  These assertions can be verified
 * at run time.  If an assertion fails, an error message is printed and the
 * program aborts.
 * Assertion checking can be disabled by adding the statement
 *
 *	#define NDEBUG
 *
 * to the program before the 
 *
 *	#include <assert.h>
 *
 * statement.
 */

#undef assert

#ifdef DEBUG

#define	__str(x)	# x
#define	__xstr(x)	__str(x)

void __bad_assertion (const char *_mess);

#define	assert(expr)	((expr)? (void)0 : \
				__bad_assertion("Assertion \"" #expr \
					"\" failed, file " __xstr(__FILE__) \
					", line " __xstr(__LINE__) "\n"))


#else
	#define assert(expr)  ((void) 0)
#endif
