#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <readline/readline.h>

#include <sys/types.h>
#include <sys/wait.h>

#include "token.h"

char *exitTok[] = {"exit", (char *) 0};
char *nullTok[] = {(char *) 0};

char *prompt = "$ ";

void shellLoop(char *envp[]) {
  for (int keepLooping = 1; keepLooping;) {
    char *line = readline(prompt);

    if (line == 0) {
      // Reached EOF: exit loop, nothing to clean up
      write(STDOUT_FILENO, "\n", 1);
      break;
    }

    char **tokens = mytok(line, ' ');
    keepLooping = shellExec(tokens, envp);

    freetok(tokens);
    free(line);
  }
}

int shellExec(char **tokens, char *envp[]) {
  int isExit = !tokcmp(exitTok, tokens);

  if (!isExit && tokcmp(tokens, nullTok) != 0) {
    pid_t fpid = fork();
    if (fpid < 0) {
      // Failed to fork
      write(STDERR_FILENO, "Failed to fork.\n", 16);
      exit(EXIT_FAILURE);
    } else if (fpid == 0) {
      // Child process
      execve(tokens[0], tokens, envp);
      write(STDERR_FILENO, "command not found\n", 18);
      exit(EXIT_FAILURE);
    } else {
      // Parent process
      wait(NULL);
    }
  }

  return !isExit;
}
