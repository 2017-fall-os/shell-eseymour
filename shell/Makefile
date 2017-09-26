CFLAGS = -std=c11 -Wall -Werror -pedantic
LDLIBS = -lreadline

.PHONY: all
all: sesh

.PHONY: clean
clean:
	rm -rf sesh *.o

sesh: sesh.o shell.o stringutils.o token.o

sesh.o: sesh.c shell.h
shell.o: shell.c shell.h stringutils.h token.h
stringutils.o: stringutils.c stringutils.h
token.o: token.c token.h stringutils.h
