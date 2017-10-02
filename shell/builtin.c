#include "builtin.h"

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int builtinExit(int argc, char **argv, char **envp);
int builtinCd(int argc, char **argv, char **envp);

Command builtins[] = {
  {"exit", &builtinExit},
  {"cd", &builtinCd},
  {0}
};

int builtinExit(int argc, char **argv, char **envp) {
  exit(EXIT_SUCCESS);
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
