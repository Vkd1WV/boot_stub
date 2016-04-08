

#include "kernel.h"


/*===========================================================================*
 *                       The Kernel Entry                                  *
 *===========================================================================*/

void kernel_entry(uint32_t mb_magic, void* mb_data);

void kernel_entry(uint32_t mb_magic, void* mb_data){
	clear_vga();
	//kputs("Kernel Booted", 13); //FIXME: this line prevents booting
	kputc('&');
}


/*===========================================================================*
 *                                   panic                                   *
 *===========================================================================*/

