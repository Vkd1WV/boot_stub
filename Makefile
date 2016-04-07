#
# Whole System Makefile
#

############################# PRELIMINARIES ####################################

CWARNINGS:=	-Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
			-Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
			-Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
			-Wuninitialized -Wstrict-prototypes #-Wconversion


SHELL:=		/bin/bash
CC:=		i686-elf-gcc
CFLAGS:=	$(CWARNINGS) -I./header -ffreestanding -nostdlib -lgcc -std=c11 -g
#-mno-red-zone (x86_64 only)
AS:=		nasm
ASFLAGS:=	-f elf32
LFLAGS:=	-ffreestanding -nostdlib

PROJDIRS:= fs header kernel mm net

.PHONEY: clean test


# Build Object Files
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@
%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

############################### KERNEL BUILD ###################################

k_src:=			kernel/*.c kernel/*.s
k_headers:=		kernel/*.h

k_objects:=		$(shell echo \
	kernel/{boot.o,kernel.o,io.o,global.o})

k_cleanfiles:=	kernel/kernel $(k_objects)

.PHONEY: kernel

kernel: kernel/kernel

kernel/kernel: $(k_objects) $(k_headers)
	$(CC) $(LFLAGS) -T kernel/link.ld $(k_objects) -o kernel/kernel

# Build Object Files
kernel/%.o: kernel/%.c $(k_headers)
	$(CC) $(CFLAGS) -c $< -o $@
kernel/%.o: kernel/%.s
	$(AS) $(ASFLAGS) $< -o $@

########################### BUILD INSTALLATION MEDIA ###########################

.PHONEY: disk
disk: iso/boot/kernel os.iso

iso/boot/kernel: kernel/kernel
	cp kernel/kernel iso/boot/


os.iso: iso/boot/kernel iso/boot/grub/menu.lst
# -R			Rock Ridge filesystem
# -A			application ID used in disk header
# -no-emul-boot	BIOS will load the boot image directly without emulating a disk
	genisoimage                      \
		-R                           \
		-A OmniSYS                   \
		-no-emul-boot                \
		-b boot/grub/stage2_eltorito \
		-boot-load-size 4            \
		-input-charset utf8          \
		-boot-info-table             \
		-o os.iso iso

################################ RUN SYSTEM TEST ###############################

test: disk bochsrc.txt
	bochs -f bochsrc.txt -q

#################################### UTILITY ###################################

cleanfiles=*.iso $(k_cleanfiles)

clean:
	rm -f $(cleanfiles)

todolist:
	-@for file in $(ALLFILES:Makefile=); do fgrep -H -e TODO -e FIXME $$file; done; true


