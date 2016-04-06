/*
A Framebuffer driver
*/

#include "typedefs.h"

/* Clear the framebuffer */
void clear_fb();

/* Write a line to the framebuffer */
int kwrite(char *buf, uint len);
