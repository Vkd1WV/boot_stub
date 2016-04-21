s32_headers:=		stage32/*.h
s32_objects:=		$(shell echo \
	stage32/$(ARCH)/{boot.o,io.o,vga.o} stage32/stage32.o)

cleanfiles+=	stage32/stage32 $(s32_objects)

.PHONEY: stage32
stage32: stage32/stage32

stage32/stage32: $(s32_objects) $(s32_headers)
	$(CC32) $(LFLAGS) -T stage32/link.ld $(s32_objects) -o $@

# Build Object Files
stage32/%.o: stage32/%.c $(s32_headers)
	$(CC32) $(CFLAGS) -c $< -o $@
stage32/%.o: stage32/%.s
	$(AS) $(ASF32) $< -o $@
