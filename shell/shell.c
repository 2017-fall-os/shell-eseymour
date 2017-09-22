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

char ** getPathTok(char *envp[]) {
  for (; *envp != 0; envp++) {
    char **varTok = mytok(*envp, '=');

    if (stringcmp(varTok[0], "PATH") == 0) {
      char **pathTok = mytok(varTok[1], ':');
      freetok(varTok);
      return pathTok;
    }

    freetok(varTok);
  }

  write(STDERR_FILENO, "PATH enviornment variable not defined\n", 38);
  exit(EXIT_FAILURE);
}

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
      size_t commandLen = toklen(tokens[0], '\0');
      for (char **pathTok = getPathTok(envp); *pathTok != 0; pathTok++) {
        char *curPath = *pathTok;
        size_t curPathLen = toklen(curPath, '\0');
        curPath = realloc(curPath, curPathLen + commandLen + 2);

        curPath[curPathLen] = '/';
        for (int i = 0; i <= commandLen; i++) {
          curPath[curPathLen + i + 1] = tokens[0][i];
        }

        execve(curPath, tokens, envp);
      }
      execve(tokens[0], tokens, envp);
      write(STDERR_FILENO, "command not found\n", 18);
      exit(EXIT_FAILURE);
    } else {
      // Parent process
      int status;
      wait(&status);
      if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
        fprintf(stderr, "program terminated with exit code: %d\n", WEXITSTATUS(status));
      }
    }
  }

  return !isExit;
}
