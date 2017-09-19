CFLAGS = -std=c11 -Wall -Werror -pedantic

.PHONY: all
all: sh

.PHONY: clean
clean:
	rm -rf sh *.o

sh: sh.o shell.o token.o
	cc $(LDFLAGS) $^ -lreadline -o $@

sh.o: sh.c shell.h
shell.o: shell.c shell.h token.h
token.o: token.c token.h
