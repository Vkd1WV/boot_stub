#
# Whole System Makefile
#

############################# PRELIMINARIES ####################################

SHELL:=		/bin/bash

ARCH:=		x86_64
ARCHDIR:=arch/$(ARCH)

CWARNINGS:=	-Wall -Wextra -pedantic \
	-Wmissing-prototypes -Wstrict-prototypes -Wmissing-declarations \
	-Wredundant-decls -Wnested-externs -Wshadow \
	-Wpointer-arith -Wcast-align \
	-Wuninitialized -Wmaybe-uninitialized \
	-Winline -Wno-long-long \
	-Wwrite-strings #-Wconversion


CC32:=		i686-elf-gcc
CC64:=		$(ARCH)-elf-gcc
CFLAGS:=	$(CWARNINGS) -I./header -ffreestanding -nostdlib -lgcc -std=c11 -g -DDEBUG
#-mno-red-zone (x86_64 only)

AS:=		nasm
ASF32:=	-f elf32
ASF64:=	-f elf64

LFLAGS:=	-ffreestanding -nostdlib

PROJDIRS:= fs header kernel mm net

.PHONEY: clean test


################################ STAGE BUILD ###################################

s32_headers:=		stage32/*.h
s32_objects:=		$(shell echo \
	stage32/$(ARCH)/{boot.o,io.o,vga.o} stage32/stage32.o)

s32_cleanfiles:=	stage32/stage $(s32_objects)

.PHONEY: stage
stage: stage32/stage

stage32/stage: $(s32_objects) $(s32_headers)
	$(CC32) $(LFLAGS) -T stage32/link.ld $(s32_objects) -o stage32/stage

# Build Object Files
stage32/%.o: stage32/%.c $(s32_headers)
	$(CC32) $(CFLAGS) -c $< -o $@
stage32/%.o: stage32/%.s
	$(AS) $(ASF32) $< -o $@

############################### KERNEL BUILD ###################################

#k_src:=			kernel/*.c kernel/*.s
#k_headers:=		kernel/*.h

#k_objects:=		$(shell echo \
#	kernel/{boot.o,kernel.o,io.o,framebuffer.o,global.o})

#k_cleanfiles:=	kernel/kernel $(k_objects)

#.PHONEY: kernel
#kernel: kernel/kernel

#kernel/kernel: $(k_objects) $(k_headers)
#	$(CC64) $(LFLAGS) -T kernel/link.ld $(k_objects) -o kernel/kernel

## Build Object Files
#kernel/%.o: kernel/%.c $(k_headers)
#	$(CC64) $(CFLAGS) -c $< -o $@
#kernel/%.o: kernel/%.s
#	$(AS) $(ASFLAG64) $< -o $@

########################### BUILD INSTALLATION MEDIA ###########################

.PHONEY: disk
disk: os.iso

iso/boot/stage: stage32/stage  
	cp stage32/stage iso/boot/

os.iso: iso/boot/stage iso/boot/grub/grub.cfg
	grub-mkrescue -o os.iso iso

################################ RUN SYSTEM TEST ###############################

test: disk bochsrc.txt
	bochs -f bochsrc.txt -q

#################################### UTILITY ###################################

cleanfiles=*.iso $(s32_cleanfiles)

clean:
	rm -f $(cleanfiles)

todolist:
	-@for file in $(ALLFILES:Makefile=); do fgrep -H -e TODO -e FIXME $$file; done; true


