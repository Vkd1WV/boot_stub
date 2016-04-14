#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#define MB_MAGIC_NUMBER ((uint32_t) 0x2BADB002)

struct __attribute__((packed)) multiboot_info {
	uint32_t flags;
	uint32_t mem_lower;
	uint32_t mem_upper;		// flags[0]
	// amount of lower and upper memory in kB
	
	// BIOS Boot device.	flags[1]
	uint32_t boot_device;
	
	uint32_t cmdline;		// flags[2] null terminated string
	
	uint32_t mods_count;
	uint32_t mods_addr;		// flags[3]
	uint32_t num;
	uint32_t size;
	uint32_t addr;
	uint32_t shndx;			// flags[5]
	uint32_t mmap_length;
	uint32_t mmap_addr;		// flags[6]
	uint32_t drives_length;
	uint32_t drives_addr;	// flags[7]
	uint32_t config_table;	// flags[8]
	uint32_t boot_loader_name;	// flags[9]
	uint32_t apm_table;			// flags[10]
	
	uint32_t vbe_control_info;
	uint32_t vbe_mode_info;
	uint16_t vbe_mode;
	uint16_t vbe_interface_seg;
	uint16_t vbe_interface_off;
	uint16_t vbe_interface_len;
};

struct __attribute__((packed)) multiboot_module {
	uint32_t mod_start;
	uint32_t mod_end;
	char*    string;	// arbitrary null terminated string
	uint32_t reserved;
}

struct __attribute__((packed)) mmap_entry {
	uint32_t size;
	uint64_t base_addr;
	uint64_t length;	// size of memory region in bytes
	uint32_t type;		// type of memory region. 1 is normal memory.
}

struct __attribute__((packed)) apm_table {
	uint16_t version;
	uint16_t cseg;
	uint32_t offset;
	uint16_t cseg_16;
	uint16_t dseg;
	uint16_t flags;
	uint16_t cseg_len;
	uint16_t cseg_16_len;
	uint16_t dseg_len;
}

#endif // MULTIBOOT_H
