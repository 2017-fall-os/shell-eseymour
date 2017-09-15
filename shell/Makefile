CFLAGS = -std=c11 -Wall -Werror -pedantic

.PHONY: all
all: shell

.PHONY: clean
clean:
	rm -rf shell *.o

shell: shell.o token.o

token.o: token.c token.h

shell.o: shell.c token.h
