#
# Kernel makefile
#

CFLAGS=-I../header -Wall -Wextra -pedantic -std=c11 \
		-fno-builtin -fno-stack-protector -nostartfiles \
		-nodefaultlibs -nostdlib -nostdinc
LDFLAGS=-T link.ld --fatal-warnings
ASFLAGS=-f elf32

OBJECTS= io.o framebuffer.o loader.o main.o

k_headers=cfg.h typedefs.h const.h global.h proto.h
cleanfiles=*.out *.o kernel loader

.PHONEY: clean

clean:
	rm -f $(cleanfiles)


test: test.c
	gcc $(options) -o test test.c

kernel: $(OBJECTS) link.ld
	ld $(LDFLAGS) $(OBJECTS) -o kernel


# Build Object Files
%.o: %.c %.h
	gcc $(CFLAGS) -c $< -o $@
%.o: %.s
	nasm $(ASFLAGS) $< -o $@

