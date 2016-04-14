// System-wide data type and macro definitions

#ifndef S_TYPEDEF_H
#define S_TYPEDEF_H

// Freestanding type headers provided by the compiler
#include <stdbool.h>	// bool types
#include <stddef.h>		// size_t & NULL
#include <stdint.h>		// intx_t
#include <limits.h>		// type size limits

typedef unsigned int uint;
typedef long long int maxint;
typedef unsigned long long int maxuint;

#define MAXINT_MAX
#define MIXINT_MIN
#define MAXUINT_MAX

// VGA framebuffer color settings
enum vga_color {
	BLACK   = 0,
	BLUE    = 1,
	GREEN   = 2,
	CYAN    = 3,
	RED     = 4,
	MAGENTA = 5,
	BROWN   = 6,
	LIGHT_GREY    = 7,
	DARK_GREY     = 8,
	LIGHT_BLUE    = 9,
	LIGHT_GREEN   = 10,
	LIGHT_CYAN    = 11,
	LIGHT_RED     = 12,
	LIGHT_MAGENTA = 13,
	LIGHT_BROWN   = 14,
	WHITE = 15
};

#endif // S_TYPEDEF_H
