

#include "kernel.h"


/*===========================================================================*
 *                       The Kernel Entry                                  *
 *===========================================================================*/

void kernel_entry(uint32_t mb_magic, void* mb_data);

void kernel_entry(uint32_t mb_magic, void* mb_data){
	clear_vga();
	kputs("Kernel Booted.", 14); //FIXME: this line prevents booting
	if (mb_magic == MB_MAGIC_NUMBER)
		kputs("Booted with a Multiboot compliant boot loader.", 46);
	
	for(;;);
}


/*===========================================================================*
 *                                   panic                                   *
 *===========================================================================*/

