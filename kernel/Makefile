#
# Shop Sys : a shopping system
#


cleanfiles=*.out *.o test
options=-I../header -Wall -Wextra -pedantic -std=c11 -g

test: test.c kernel.h
	gcc $(options) -o test test.c

kernel:
	gcc $(options) -o kernel

clean:
	rm -f $(cleanfiles)
