#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

/** outb:
 *  Sends the given data to the given I/O port. Defined in io.s
 */
void outb(unsigned short port, unsigned char data);

#endif /* INCLUDE_IO_H */
