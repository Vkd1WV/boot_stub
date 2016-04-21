#ifndef _STDIO_H
#define _STDIO_H 1

#include <sys/typedefs.h>

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);

#ifdef __cplusplus
}
#endif

// We will not be providing scanf() or fscanf()
// in fact, scanf() isn't even an exclusively io function
// we'll consider sscanf() but it's still not io

/*

Sorry Konrad, but I recommend: never on pain of death, never never never (is that clear enough? :-) read formatted data from a file. Just don't.

There is only one correct way to do input of formatted data: read chunks of characters (typically lines but you can also read fixed length blocks).

Then parse the input text. You're not going to do a cursory check, you going to use a parser that guarantees to catch any formatting error, and report that error in a comprehensible way, take appropriate action (termination, skip the line and continue, whatever).

Separate input (the I/O operation) from parsing.

This advice from decades of experience as a commerical programmer: reading formatted input is for micky mouse proof-of-principal programs. Even if you have exclusive control of the creation of the file, always parse and check and report errors: after all, stuff changes, it may work today but not tomorrow.

I've been writing C++ for decades and I've never read an integer.

*/

char* grabline(FILE*);
/**	Get the next newline terminated line of text and store it in an array.
 *	The newline is discarded and the array is \0 teriminated.
 *	whitespace is NL, CR, spaces, and tabs.
 *	Discards leading and terminating whitespace
 *	returns NULL on failure
 */

char* grabword(FILE*);
/**	Get the next alphanumeric word from the input stream
 *	Discards leading and terminating whitespace
 *	whitespace is NL, CR, spaces, and tabs
 *	the program must free the array provided by grabword()
 *	returns NULL on failure
 */
 
char* grabfield(FILE*);
/**	Get the next tab or newline terminated string from the input stream
 *	Discards leading and terminating whitespace
 *	whitespace is newlines, tabs, and leading spaces
 *	the program must free the array provided by grabfield()
 *	returns NULL on failure
 */


#endif
