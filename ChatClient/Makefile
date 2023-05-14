CC=gcc
CFLAGS=-Wall -ansi -pedantic -D_XOPEN_SOURCE -D_POSIX_SOURCE

all: chatclient chatserver

chatclient: chatclient.c chatshm.c chatshm.h sync.c sync.h
	$(CC) $(CFLAGS) -o chatclient chatclient.c chatshm.c sync.c
	
chatserver: chatserver.c chatshm.c chatshm.h sync.c sync.h
	$(CC) $(CFLAGS) -o chatserver chatserver.c chatshm.c sync.c
	
clean:
	rm -f chatclient chatserver *.o

.PHONY: all clean
