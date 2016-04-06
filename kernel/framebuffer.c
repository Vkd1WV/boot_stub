/*
 * A Framebuffer driver
 */

/********************************** INCLUDES **********************************/

#include "io.h"
#include "framebuffer.h"

/*********************************** MACROS ***********************************/

/* The I/O ports */
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT    0x3D5
#define FB              0x000B8000

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

/* Framebuffer dimentions */
#define ROW 25
#define COL 80
#define FB_LIM (char*)((COL * ROW)*2 + FB) // this is actually the first address after the framebuffer
#define FB_SIZE MAX_COL * MAX_ROW

#define B_W         (char) 0xf0

/* BG colors:
 * e	orange
 * f	light gray / white
 * 
 * FG colors:
 * 0	black
 */


/***************************** PRIVATE PROTOTYPES *****************************/

static void _scroll();
static void _move_cursor(uint16_t pos);

/*********************************** GLOBALS **********************************/

uint16_t cursor_pos;

/****************************** PUBLIC FUNCTIONS ******************************/

/* Clear the framebuffer */
void clear_fb(){
	char* fb;
	
	_move_cursor(0);
	
	for(fb = (char*)FB; fb < FB_LIM; fb += 2){
		fb[0] = ' ';
		fb[1] = B_W;
	}
}

/* Write a line to the framebuffer */
int kwrite(char *buf, uint len){
	char* fb;
	uint i;
	
	fb = (char*) (FB + cursor_pos *2);
	
	if (len > COL) return 0;
	
	//if (cursor_pos / MAX_COL > MAX_ROW-2) _scroll();
	
	for(i=0; i<len; i++){
		fb[0]=buf[i];
		fb[1] = B_W;
	}
	
	return i;
}

/***************************** PRIVATE FUNCTIONS ******************************/

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


/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
static void _move_cursor(uint16_t pos) {
	extern uint16_t cursor_pos;
	
	cursor_pos=pos;
	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND );
	outb(FB_DATA_PORT   , ((pos >> 8) & 0x00FF)); // & for masking
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND  );
	outb(FB_DATA_PORT   , pos & 0x00FF         );
}
