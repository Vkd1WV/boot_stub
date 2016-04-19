/******************************************************************************/
//                              MULTIBOOT STUFF
/******************************************************************************/
// Multiboot bootloaders leave the system in 32bit mode so 64bit types are not
// allowed here.


#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <sys/elf.h>

#define MB_MAGIC_NUMBER ((uint32_t) 0x2BADB002)

// FLAG MASKS
#define MB_MEM      0x00000001 // flag 0
#define MB_BOOT_DEV 0x00000002 // flag 1
#define MB_CMD_LINE 0x00000004 // flag 2
#define MB_MODS     0x00000008 // flag 3
#define MB_AOUT     0x00000010 // flag 4
#define MB_ELF      0x00000020 // flag 5
#define MB_MMAP     0x00000040 // flag 6
#define MB_DRIVES   0x00000080 // flag 7
#define MB_CFG_TBL  0x00000100 // flag 8
#define MB_BL_NAME  0x00000200 // flag 9
#define MB_APM_TBL  0x00000400 // flag 10
#define MB_VBE      0x00000800 // flag 11

struct __attribute__((packed)) mmap_entry {
	uint32_t size;		// size of the remaining fields of this structure
	uint32_t base_addr_low;
	uint32_t base_addr_high;
	uint32_t length_low;	// size of memory region in bytes
	uint32_t length_high;
	uint32_t type;		// type of memory region. 1 is normal memory.
};

struct __attribute__((packed)) drive_entry {
	uint32_t size;		// total size of drive entry
	uint8_t  drive_number;
	uint8_t  drive_mode;
	uint16_t drive_cylinders;
	uint16_t drive_heads;
	uint16_t drive_sectors;
	uint16_t ports[];
};

typedef struct drive_entry* drive_pt;
typedef struct mmap_entry*  mmap_pt;

struct __attribute__((packed)) multiboot_info {
	uint32_t flags;
	uint32_t mem_lower;		// flags[0]
	uint32_t mem_upper;		// amount of lower and upper memory in kB
	uint8_t  boot_device[4];	// BIOS Boot device.	flags[1]
	char*    cmdline;			// flags[2] null terminated string
	uint32_t mods_count;
	uint32_t mods_addr;		// flags[3]
	uint32_t    shdr_num;
	uint32_t    shdr_size;
	Elf32_Shdr* shdr_addr;
	uint32_t    shndx;			// flags[5]
	uint32_t mmap_length;
	mmap_pt  mmap_addr;		// flags[6]
	uint32_t drives_length;
	drive_pt drives_addr;	// flags[7]
	uint32_t config_table;	// flags[8]
	char*    boot_loader_name;	// flags[9]
	uint32_t apm_table;			// flags[10]
	uint32_t vbe_control_info;
	uint32_t vbe_mode_info;
	uint16_t vbe_mode;
	uint16_t vbe_interface_seg;
	uint16_t vbe_interface_off;
	uint16_t vbe_interface_len;
};
typedef struct multiboot_info* mb_info_pt;

struct __attribute__((packed)) multiboot_module {
	uint32_t mod_start;
	uint32_t mod_end;
	uint32_t string;	// arbitrary null terminated string
	uint32_t reserved;
};

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
};


#endif //MULTIBOOT_H
