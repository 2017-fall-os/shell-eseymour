CFLAGS = -std=c11 -Wall -Werror -pedantic
LDLIBS = -lreadline

.PHONY: all
all: sesh

.PHONY: clean
clean:
	rm -rf sesh testLog.txt *.o

sesh: sesh.o builtin.o shell.o stringutils.o token.o

sesh.o: sesh.c shell.h
builtin.o: builtin.c builtin.h
shell.o: shell.c shell.h stringutils.h token.h
stringutils.o: stringutils.c stringutils.h
token.o: token.c token.h stringutils.h
