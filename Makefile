#
# Whole System Makefile
#

################################ PRELIMINARIES #################################

include config.mk


CFLAGS+=	$(CWARNINGS) -I./header -ffreestanding -nostdlib -lgcc 

#look for include files in each of the modules
CFLAGS += $(patsubst %,-I%, $(MODULES))
#-mno-red-zone (x86_64 only)

LFLAGS:=	-ffreestanding -nostdlib


.PHONEY: clean test

#extra libraries if required
LIBS :=

#each module will add to this
SRC :=

cleanfiles=*.iso bochslog.txt snapshot.txt

#include the description for each module
include $(patsubst %, %/module.mk, $(MODULES))


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

os.iso: stage32/stage32 stage32/grub.cfg
	mkdir -p $(CFGDIR) $(DOCDIR) $(EXEDIR) $(LIBDIR) $(HDRDIR)
	cp stage32/stage32    $(EXEDIR)/
	cp stage32/grub.cfg $(CFGDIR)/
	grub-mkrescue --product-name=$(OS_NAME) --product-version=$(OS_VERSION) \
		-o $@ $(PREFIX)

################################ RUN SYSTEM TEST ###############################

test: disk bochsrc.txt
	bochs -f bochsrc.txt -q

#################################### UTILITY ###################################



clean:
	rm -f $(cleanfiles)
	rm -fr $(PREFIX)

todolist:
	-@for file in $(ALLFILES:Makefile=); do fgrep -H -e TODO -e FIXME $$file; done; true


