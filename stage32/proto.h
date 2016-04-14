/* Function prototypes. */

#ifndef PROTO_H
#define PROTO_H

#include "typedefs.h"

/******************************* framebuffer.o ********************************/

// set the color of text to be printed
void set_color (enum vga_color fg, enum vga_color bg);

/* Clear the framebuffer */
void clear_vga(void);

/* Write to the framebuffer */
uint kputs(const char *buf);
void kputc(char c);

/********************************** io.o **************************************/

/** outb:
 *  Sends the given data to the given I/O port. Defined in io.s
 */
void outb(uint8_t* port, uint8_t data);

#endif /* PROTO_H */
