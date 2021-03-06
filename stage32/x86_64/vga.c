/*
 * A Text mode VGA driver
 */

/******************************************************************************/
//                                 INCLUDES
/******************************************************************************/

#include "../stage32.h"

/******************************************************************************/
//                         DEFINITIONS & CONSTANTS
/******************************************************************************/


// locations
#define VGA_BUF      ((uint16_t*) 0xB8000)
#define VGA_ADDR_REG ((uint8_t*)  0x3D4)
#define VGA_DATA_REG ((uint8_t*)  0x3D5)

// sizes and limits
#define VGA_WIDTH  ((uint) 80)
#define VGA_HEIGHT ((uint) 25)
#define VGA_SIZE   (VGA_HEIGHT*VGA_WIDTH*sizeof(uint16_t))
#define TAB_WIDTH  8

// Cursor Commands
#define VGA_CUR_HB ((uint8_t) 14)
#define VGA_CUR_LB ((uint8_t) 15)


/******************************************************************************/
//                            PRIVATE PROTOTYPES
/******************************************************************************/


//static void     _scroll    (void);
static void     _set_cursor(uint pos);
static uint16_t _mk_vgacell(char c);


/******************************************************************************/
//                             GLOBAL VARIABLES
/******************************************************************************/


static struct {
	uint pos;	// linear position in the buffer
	uint8_t  color;
} cursor;


/******************************************************************************/
//                             PUBLIC FUNCTIONS
/******************************************************************************/


// Set the background and foreground color of characters to be written after
void set_color(enum vga_color fg, enum vga_color bg) {
	cursor.color = fg | (bg << 4);
}

// Clear the screen
void clear_vga(){
	uint16_t  cell;
	uint16_t* pos;
	
	set_color(BLACK, WHITE);
	cell = _mk_vgacell(' ');
	
	for(pos=VGA_BUF; pos < VGA_BUF+VGA_SIZE; pos++){
		*pos = cell;
	}
	
	_set_cursor(0);
}

// Print a character at the cursor position
void kputc(char c){
	uint16_t* pos;
	
	pos = VGA_BUF+cursor.pos;
	
	*pos = _mk_vgacell(c);
	_set_cursor(cursor.pos+1);
}

// Print a string on the next line after the cursor position
uint kputs(const char *buf){
	uint i;
	uint16_t* pos;
	
//	if (start => VGA_SIZE) {
//		_scroll();
//		start =- VGA_WIDTH;
//	}
	pos = VGA_BUF+cursor.pos;
	
	for(i=0; buf[i] != '\0'; i++){
		if (buf[i] == '\n') {
			cursor.pos = (cursor.pos/VGA_WIDTH)*VGA_WIDTH + VGA_WIDTH;
			pos = VGA_BUF + cursor.pos;
		}
		else if (buf[i] == '\t'){
			cursor.pos = (cursor.pos/TAB_WIDTH)*TAB_WIDTH + TAB_WIDTH;
			pos = VGA_BUF + cursor.pos;
		}
		else{
			*pos = _mk_vgacell(buf[i]);
			pos++;
			cursor.pos++;
		}
	}
	
	_set_cursor(cursor.pos);
	
	return i;
}

void kputn(uint32_t number){
	uint32_t temp;
	bool zero = true;
	
	kputs("0x");
	for(uint i=0; i<8; i++){
		temp = (number & 0xf0000000) >> 28;
		if(zero && !temp); // do nothing on leading 0's
		else{
			zero = false;
			if (temp < 0xa) kputc('0'+temp);
			else            kputc('A'+ temp - 0xa);
		}
		number <<= 4;
	}
	
	if(zero) kputc('0');
}

void kputb(uint32_t number){
	uint32_t bit_mask =0x80000000;
	bool zero = true;
	
	kputs("0b");
	for (uint i=0; i< 32; i++){
		if(zero && !(number & bit_mask)); // do nothing on leading 0's
		else{
			if (!(i % 8)) kputc(' ');
			if (number & bit_mask){
				zero = false;
				kputc('1');
			}
			else kputc('0');
		}
		
		
		bit_mask >>= 1;
	}
	
	if(zero) kputc('0');
}

/******************************************************************************/
//                             PRIVATE FUNCTIONS
/******************************************************************************/


static void _set_cursor(uint pos) {
	cursor.pos=pos;
	outb(VGA_ADDR_REG, VGA_CUR_HB           );
	outb(VGA_DATA_REG, ((pos >> 8) & 0x00FF)); // & for masking
	outb(VGA_ADDR_REG, VGA_CUR_LB           );
	outb(VGA_DATA_REG, pos         & 0x00FF );
}

static uint16_t _mk_vgacell(char c) {
	uint16_t c16 = c;
	uint16_t color16 = cursor.color << 8;
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

