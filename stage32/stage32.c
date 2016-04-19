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
#include <sys/multiboot.h>


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
	
	
	// report bootloader stuff
	kputs("==BOOTLOADER==\n");
	if (mb_magic == MB_MAGIC_NUMBER)
		kputs("Multiboot Detected.\n");
	
	// print the multiboot flags to the screen
	kputs("MULTIBOOT FLAGS: ");
	kputb(mb_data->flags);
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
	
	// drive stuff
	kputs("\n==DRIVES==\n");
	if (mb_data->flags & MB_BOOT_DEV){
		kputs("BIOS BOOT DEVICE: ");
		kputn(mb_data->boot_device[0]);
		for(uint i=1; mb_data->boot_device[i] < 0xff && i<4; i++){
			kputs(" Partition: ");
			kputn(mb_data->boot_device[i]);
		}
		kputs("\n");
	}
	
	
	if (mb_data->flags & MB_DRIVES && mb_data->drives_length){
		void* entry=mb_data->drives_addr;
		/*
			drive list can have variable length entries so we can't statically
			increment the entry pointer. so I'm using a void pointer, and
			incrementing by the given size.
			see multiboot.h and the multiboot specification for some details
		*/
		
		kputs("==DRIVES==\n");
		kputs("NUM\tMODE\tC/H/S\t\tPORTS\n");
		for(uint i=0; i<mb_data->drives_length;){
			kputn(((drive_pt)entry)->drive_number);
			kputs("\t");
			kputn(((drive_pt)entry)->drive_mode);
			kputs("\t");
			kputn(((drive_pt)entry)->drive_cylinders);
			kputs("/");
			kputn(((drive_pt)entry)->drive_heads);
			kputs("/");
			kputn(((drive_pt)entry)->drive_sectors);
			kputs("\t");
			kputn(((uint16_t*)entry)[5]);
			kputs("\n");
			
			i += ((drive_pt)entry)->size;
			entry += ((drive_pt)entry)->size;
		}
	} // TODO: this if statement has not been tested yet
	
	// Module and image data
	kputs("\n==BOOT IMAGES==\n");
	if (mb_data->flags & MB_ELF){
		kputs("BOOT IMAGE: ");
		kputn(mb_data->shdr_num);
		kputs(" sections of size ");
		kputn(mb_data->shdr_size);
		kputs("\n");
		
		for(uint i=0; i<mb_data->shdr_num; i++){
			kputs((char*)((mb_data->shdr_addr)[i]).sh_name);
		}
		kputs("\n");
	}
	if (mb_data->flags & MB_MODS){
		//TODO: read module data
	}
	
	// Memory information
	kputs("\n==MEMORY==\n");
	if (mb_data->flags & MB_MEM){
		kputs("LOW MEMORY: ");
		kputn(mb_data->mem_lower);
		kputs("   HIGH MEMORY: ");
		kputn(mb_data->mem_upper);
		kputs("\n");
	}
	
	// memory map
	if (mb_data->flags & MB_MMAP){
		void* entry=mb_data->mmap_addr;
		/*
			memory map can have variable length entries so we can't statically
			increment the entry pointer. so I'm using a void pointer, and
			incrementing by the given size.
			see multiboot.h and the multiboot specification for some details
		*/
		
		kputs("OFFSET\t\t\tSIZE\t\t\tTYPE\n");
		for(uint i=0; i< mb_data->mmap_length;){
			kputn( ((mmap_pt)entry)->base_addr_high);
			kputc(' ');
			kputn( ((mmap_pt)entry)->base_addr_low);
			kputs("\t\t\t");
			kputn( ((mmap_pt)entry)->length_high);
			kputc(' ');
			kputn( ((mmap_pt)entry)->length_low);
			kputs("\t\t\t");
			kputn( ((mmap_pt)entry)->type);
			kputs("\n");
			
			i += ((mmap_pt)entry)->size +4;
			entry += ((mmap_pt)entry)->size +4;
		}
	}
	
	// TODO: clear the page table
	// TODO: setup memory maps in the page table
	
	// TODO: enable paging
}


