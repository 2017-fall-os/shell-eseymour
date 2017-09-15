CFLAGS = -std=c11 -Wall -Werror -pedantic

.PHONY: all
all: sh

.PHONY: clean
clean:
	rm -rf sh *.o

sh: sh.o token.o

token.o: token.c token.h

sh.o: sh.c token.h
