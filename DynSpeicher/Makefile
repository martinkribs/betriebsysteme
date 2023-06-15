CC=gcc
CFLAGS=-ansi -pedantic -D_POSIX_SOURCE -D_XOPEN_SOURCE -Wall
CFLAGS+=-DDEBUG -g

malloctest: malloctest.c nextfit.c nextfit.h
	$(CC) $(CFLAGS) -o malloctest malloctest.c nextfit.c

clean:
	rm -f malloctest

.PHONY: clean
