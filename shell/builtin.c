#include "builtin.h"

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include "stringutils.h"

typedef struct {
  char *commandName;
  BuiltinFunc commandFunc;
} Command;

/* Builtin command functions. Defined at the end of the file */
int builtinCd(int argc, char **argv, char **envp);
int builtinExit(int argc, char **argv, char **envp);

/* The command vector. It's NULL terminated to make it easy to add commands */
static Command *builtins[] = {
  &(Command) {"cd", &builtinCd},
  &(Command) {"exit", &builtinExit},
  NULL
};

/* Searches builtin command vector for command matching the string commandName.
 * If a matching command is found, a function that excecutes that command is
 * returned. If no matching command is found, NULL is returned instead. */
BuiltinFunc getBuiltinFunc(char *commandName) {
  for (int i = 0; builtins[i] != NULL; i++) {
    Command *builtin = builtins[i];

    if (stringcmp(builtin->commandName, commandName) == 0) {
      return builtin->commandFunc;
    }
  }
  return NULL;
}

int builtinCd(int argc, char **argv, char **envp){
  if (argc == 1) {
    // Change directory to home directory
  } else {
    if(chdir(argv[1]) != 0) {
      return errno;
    }
  }
  return 0;
}

int builtinExit(int argc, char **argv, char **envp) {
  exit(EXIT_SUCCESS);
}
