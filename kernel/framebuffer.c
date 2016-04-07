/*
 * A Framebuffer driver
 */

/********************************** INCLUDES **********************************/

#include "kernel.h"

/********************************* DEFINITIONS ********************************/

/* The I/O ports */
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT    0x3D5
#define FB              0x000B8000

/* The I/O port commands */
#define FB_HIGH_BYTE_CMD    14
#define FB_LOW_BYTE_CMD     15

static const uint16_t VGA_WIDTH  = 80;
static const uint16_t VGA_HEIGHT = 25;


/***************************** PRIVATE PROTOTYPES *****************************/

//static void _scroll(void);
static void _set_cursor(uint8_t x, uint8_t y);
static void _inc_cursor(void);
uint16_t _mk_vgacell(char c);

/*********************************** GLOBALS **********************************/

 static struct {
	uint8_t  x;
	uint8_t  y;
	uint16_t l_pos;
} cursor_pos;

static uint8_t _color;

/****************************** PUBLIC FUNCTIONS ******************************/

// Set the color
void set_color(enum vga_color fg, enum vga_color bg) {
	_color = fg | (bg << 4);
}

/* Clear the framebuffer */
void clear_vga(){
	uint16_t* fb;
	uint16_t cell;
	
	_set_cursor(0,0);
	set_color(WHITE, BLACK);
	cell = _mk_vgacell(' ');
	
	for(fb=(uint16_t*)FB; fb < (uint16_t*)(FB+VGA_HEIGHT*VGA_WIDTH); fb++){
		*fb = cell;
	}
}

void kputc(char c){
	uint16_t* fb;
	
	fb = (uint16_t*)(FB+cursor_pos.l_pos);
	
	*fb = _mk_vgacell(c);
	_inc_cursor();
}

/* Write a line to the framebuffer */
uint kputs(char *buf, uint len){
	uint i;
	
	if (len > VGA_WIDTH) return 0;
	
	_set_cursor(0, cursor_pos.y+1);
	//if (cursor_pos.y => VGA_HEIGHT) _scroll();
	
	for(i=0; i<len; i++)
		kputc(buf[i]);
	
	return i;
}

/***************************** PRIVATE FUNCTIONS ******************************/


/******************************************************************************/
//                         SET THE CURSOR POSITION
/******************************************************************************/
static void _set_cursor(uint8_t x, uint8_t y) {
	cursor_pos.l_pos = y * VGA_WIDTH + x;
	cursor_pos.x=x;
	cursor_pos.y=y;
	
	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_CMD );
	outb(FB_DATA_PORT   , ((cursor_pos.l_pos >> 8) & 0x00FF)); // & for masking
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_CMD  );
	outb(FB_DATA_PORT   , cursor_pos.l_pos & 0x00FF         );
}

static void _inc_cursor(void){
	cursor_pos.l_pos++;
	cursor_pos.y =cursor_pos.l_pos / VGA_WIDTH;
	cursor_pos.x =cursor_pos.l_pos % VGA_WIDTH;
	
	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_CMD );
	outb(FB_DATA_PORT   , ((cursor_pos.l_pos >> 8) & 0x00FF)); // & for masking
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_CMD  );
	outb(FB_DATA_PORT   , cursor_pos.l_pos & 0x00FF         );
}

uint16_t _mk_vgacell(char c) {
	uint16_t c16 = c;
	uint16_t color16 = _color << 8;
	return color16 | c16;
}

/* Scroll the contents of the framebuffer by one line */
/*static void _scroll(){*/
/*	uint16_t* fb;*/
/*	*/
/*	for(fb = (uint16_t*)FB; fb <= (uint16_t*)((MAX_ROW-1)* MAX_COL); fb++) {*/
/*		*fb = *(fb +ROW);*/
/*	}*/
/*	*/
/*	_move_cursor((cursor_pos - ROW) / MAX_ROW);*/
/*}*/

