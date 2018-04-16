.POSIX:
CC     = cc
CFLAGS = -ansi -pedantic -O3 -g3 -Wall -Wextra

test: test.c bmp.h
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ test.c

clean:
	rm -f test test.bmp
