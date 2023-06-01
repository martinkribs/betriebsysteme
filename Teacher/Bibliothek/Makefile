# Variablendefinieren
# Welchen Compiler verwenden wir?
CC=gcc
# Welche Flags sollen gesetzt werden?
CFLAGS=-Wall -D_XOPEN_SOURCE -D_POSIX_SOURCE
# optional die harten Flags
CFLAGS_HARD=-Werror -ansi -pedantic

# Targets
bibliothek1: bibliothek_1.c sync.c sync.h
	$(CC) $(CFLAGS) -o bibliothek1 bibliothek_1.c sync.c
bibliothek2: bibliothek_2.c sync.c sync.h
	$(CC) $(CFLAGS) -o bibliothek2 bibliothek_2.c sync.c
bibliothek3: bibliothek_3.c sync.c sync.h
	$(CC) $(CFLAGS) -o bibliothek3 bibliothek_3.c sync.c
bibliothek_hard: bibliothek_3.c sync.c sync.h
	$(CC) $(CFLAGS) $(CFLAGS_HARD) -o bibliothek bibliothek_3.c sync.c

clean:
	rm -f bibliothek

.PHONY: clean
