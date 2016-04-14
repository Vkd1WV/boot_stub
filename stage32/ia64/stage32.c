

#include "../stage32.h"


/******************************************************************************/
//                       The Kernel Entry                                  *
/*===========================================================================*/

void stage_entry(uint32_t mb_magic, mb_info_pt mb_data);

void stage_entry(uint32_t mb_magic, mb_info_pt mb_data){
	uint32_t bit_mask =0x80000000;
	
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
	
	kputs("MULTIBOOT FLAGS: ");
	for (uint i=0; i< 8 * sizeof(mb_data->flags); i++){
		if (mb_data->flags & bit_mask) kputc('1');
		else kputc('0');
		if (i == 15) kputc(' ');
		bit_mask = bit_mask >> 1;
	}
	kputs("\n");
	
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
		
	}
	
	// Module and image data
	
	if (mb_data->flags & MB_MODS){
		
	}
	if (mb_data->flags & MB_ELF){
		
	}
	
	// Memory information
	
	if (mb_data->flags & MB_MEM){
		
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


