#include "builtin.h"

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int builtinCd(int argc, char **argv, char **envp);
int builtinExit(int argc, char **argv, char **envp);

Command builtins[] = {
  {"cd", &builtinCd},
  {"exit", &builtinExit},
  {0}
};

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
