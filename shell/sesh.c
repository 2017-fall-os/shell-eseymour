#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <readline/readline.h>

#include "shell.h"

int main(int argc, char *argv[], char *envp[]) {
  // Initialize
  if (!isatty(STDIN_FILENO)) {
    // Stop readline from echoing to stdout if not run interactively.
    // Pretty hacky, should implement own line reading functionality.
    int devNull = open("/dev/null", O_WRONLY);
    rl_outstream = fdopen(devNull, "w");
  }

  shellLoop(envp);
}
