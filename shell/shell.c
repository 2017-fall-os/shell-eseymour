#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <readline/readline.h>

#include <sys/types.h>
#include <sys/wait.h>

#include "builtin.h"
#include "stringutils.h"
#include "token.h"

char *exitTok[] = {"exit", (char *) 0};
char *nullTok[] = {(char *) 0};

char *prompt = "$ ";

char ** getPathTok(char *envp[]) {
  for (; *envp != 0; envp++) {
    char **varTok = tokenize(*envp, '=');

    if (stringcmp(varTok[0], "PATH") == 0) {
      char **pathTok = tokenize(varTok[1], ':');
      tokenFree(varTok);
      return pathTok;
    }

    tokenFree(varTok);
  }

  write(STDERR_FILENO, "PATH enviornment variable not defined\n", 38);
  // Return empty path
  return (char **) calloc(sizeof(char **), 1);
}

void shellLoop(char *envp[]) {
  for (;;) {
    char *line = readline(prompt);

    if (line == 0) {
      // Reached EOF: exit loop, nothing to clean up
      //write(STDIN_FILENO, "\n", 1);
      break;
    }

    char **tokens = tokenize(line, ' ');
    shellExec(tokens, envp);

    tokenFree(tokens);
    free(line);
  }
}

void shellExec(char **tokens, char *envp[]) {
  if (tokenCmp(tokens, nullTok) != 0) {
    // Check if builtin
    BuiltinFunc builtin = getBuiltinFunc(tokens[0]);
    if (builtin != NULL) {
      // Excecute builtin function and return
      builtin(tokenLen(tokens), tokens, envp);

      return;
    }

    pid_t fpid = fork();
    if (fpid < 0) {
      // Failed to fork
      write(STDERR_FILENO, "Failed to fork.\n", 16);
      exit(EXIT_FAILURE);
    } else if (fpid == 0) {
      // Child process
      size_t commandLen = stringlen(tokens[0]);
      for (char **pathTok = getPathTok(envp); *pathTok != 0; pathTok++) {
        char *curPath = *pathTok;
        size_t curPathLen = stringlen(curPath);
        curPath = realloc(curPath, curPathLen + commandLen + 2);

        curPath[curPathLen] = '/';
        for (int i = 0; i <= commandLen; i++) {
          curPath[curPathLen + i + 1] = tokens[0][i];
        }

        execve(curPath, tokens, envp);
      }
      execve(tokens[0], tokens, envp);
      write(STDERR_FILENO, "command not found\n", 18);
      exit(EXIT_SUCCESS);
    } else {
      // Parent process
      int status;
      wait(&status);
      if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
        fprintf(stderr, "program terminated with exit code: %d\n", WEXITSTATUS(status));
      }
    }
  }
}
