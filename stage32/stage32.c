/******************************************************************************/
//
// stage32.c
//
// This is the 32-bit boot stage
// Everything in this file should be hardware independent
// This stage does system sanity checks, reads information left by the
// bootloader, and gets the processor into IA-32e mode before jumping into the
// 64 bit kernel
//
/******************************************************************************/

#include "stage32.h"


/******************************************************************************/
//                       The stage32 Entry point
/******************************************************************************/

void stage_entry(uint32_t mb_magic, mb_info_pt mb_data);

void stage_entry(uint32_t mb_magic, mb_info_pt mb_data){
	
	clear_vga();
	
#ifdef DEBUG
	/* bss sanity check */
	// we really don't need a runtime sanity check
	static int bss_test; // used only in sanity check
	if (!bss_test == 0)
		kputs("Data space not zeroed!\n");
#endif
	
	kputs("Stage32 Booted.\n");
	if (mb_magic == MB_MAGIC_NUMBER)
		kputs("Multiboot Detected.\n");
	
	// print the multiboot flags to the screen
	kputs("MULTIBOOT FLAGS: ");
	kputb(mb_data->flags);
	kputs("\n");
	
	// report bootloader stuff
	
	if (mb_data->flags & MB_BL_NAME){
		kputs("BOOTED BY: ");
		kputs(mb_data->boot_loader_name);
		kputs("\n");
	}
	if (mb_data->flags & MB_CMD_LINE && *(mb_data->cmdline) != '\0'){
		kputs("COMMAND LINE: ");
		kputs(mb_data->cmdline);
		kputs("\n");
	}
	if (mb_data->flags & MB_BOOT_DEV){
		kputs("BIOS BOOT DEVICE: ");
		kputn(mb_data->boot_device);
		kputs("\n");
	}
	
	// Module and image data
	kputs("\n");
	if (mb_data->flags & MB_MODS){
		
	}
	if (mb_data->flags & MB_ELF){
		
	}
	
	// Memory information
	kputs("\n");
	if (mb_data->flags & MB_MEM){
		kputs("LOW MEMORY: ");
		kputn(mb_data->mem_lower);
		kputs("   HIGH MEMORY: ");
		kputn(mb_data->mem_upper);
		kputs("\n");
	}
	if (mb_data->flags & MB_MMAP){
		
	}
	
	// Drives
	
	if (mb_data->flags & MB_DRIVES){
		
	}
	
	// TODO: at this point I would like to read the multiboot data and dump it
	// to the screen.
	
	// TODO: clear the page table
	// TODO: setup memory maps in the page table
	
	// TODO: enable paging
}


