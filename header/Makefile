#
# Shop Sys : a shopping system
#


cleanfiles=*.out *.o test
options=-Wall -Wextra -pedantic -std=c11 -g
filelist=sys/cfg.h sys/const.h

test: test.c $(filelist)
	gcc $(options) -o test test.c

clean:
	rm -f $(cleanfiles)
