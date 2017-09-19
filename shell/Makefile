CFLAGS = -std=c11 -Wall -Werror -pedantic
LDLIBS = -lreadline

.PHONY: all
all: sesh

.PHONY: clean
clean:
	rm -rf sesh *.o

sesh: sesh.o shell.o token.o

sesh.o: sesh.c shell.h
shell.o: shell.c shell.h token.h
token.o: token.c token.h
