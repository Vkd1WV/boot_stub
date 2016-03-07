#include "sys/cfg.h"
#include "sys/typedefs.h"
#include "sys/const.h"
#include "sys/errno.h"
#include "sys/file.h"
#include "sys/sigcontext.h"
#include "sys/syscalls.h"

#include "sys/elf.h"
#include "sys/syslib.h"

#include "assert.h"
#include "ctype.h"
#include "math.h"
#include "signal.h"
#include "stdlib.h"
#include "string.h"


#include <stdio.h>

#include "time.h"

int main (){
	printf("_WORD_SIZE: %d == %lu\n\n", _WORD_SIZE, sizeof(int));
	
	printf("int16_t : %lu\n"  , sizeof(int16_t));
	printf("int32_t : %lu\n"  , sizeof(int32_t));
	printf("int64_t : %lu\n"  , sizeof(int64_t));
	printf("int_max : %lu\n\n", sizeof(int_max));
	
	printf("uint16_t: %lu\n", sizeof(uint16_t));
	printf("uint32_t: %lu\n", sizeof(uint32_t));
	printf("uint64_t: %lu\n", sizeof(uint64_t));
	printf("uint_max: %lu\n", sizeof(uint_max));
	
	return 0;
}
