CFLAGS = -std=c99 -Wall -Werror -pedantic -D_POSIX_SOURCE
LDLIBS = -lreadline

.PHONY: all
all: sesh

.PHONY: clean
clean:
	rm -rf sesh testLog.txt *.o

sesh: sesh.o builtin.o shell.o stringutils.o token.o

sesh.o: sesh.c shell.h
builtin.o: builtin.c builtin.h stringutils.h
shell.o: shell.c shell.h builtin.h stringutils.h token.h
stringutils.o: stringutils.c stringutils.h
token.o: token.c token.h stringutils.h
