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

    char **tokens = tokenize(line, '|');
    shellExec(tokens, envp);

    tokenFree(tokens);
    free(line);
  }
}

void shellExec(char **commands, char *envp[]) {
  int numCommands = tokenLen(commands);

  if (numCommands <= 1 && strNumTokens(commands[0], ' ') == 0) {
    // No command typed in.
    return;
  }

  int infile = -1;
  for (int i = 0; i < numCommands - 1; i++) {
    // On left side of a pipe, open a pipe
    int pipedes[2];
    pipe(pipedes);

    char **args = tokenize(commands[i], ' ');
    shellCommandExec(args, envp, infile, pipedes[1]);
    tokenFree(args);
    
    // Close left side of pipe and last input file
    close(pipedes[1]);
    if (infile != -1) close(infile);

    infile = pipedes[0];
  }

  // Excecute last command without opening a pipe
  char **args = tokenize(commands[numCommands - 1], ' ');
  pid_t lastPid = shellCommandExec(args, envp, infile, -1);
  tokenFree(args);

  if (infile != -1) close(infile);

  int exitStatus;
  if (lastPid > 0) {
    // Last command was an external program
    int status;
    waitpid(lastPid, &status, 0);
    if (WIFEXITED(status)) {
      exitStatus = WEXITSTATUS(status);
    }
    else {
      // Did not exit, use a different exit status
      exitStatus = -1;
    }
  }
  else {
    // Last command was a builtin
    exitStatus = -lastPid;
  }

  if (exitStatus != 0) {
    fprintf(stderr, "command terminated with exit code: %d\n", exitStatus);
  }
}

pid_t shellCommandExec(char **args, char *envp[], int indes, int outdes) {
  BuiltinFunc builtin = getBuiltinFunc(args[0]);
  if (builtin != NULL) {
    // Is a builtin function, excecute and return negative exit condition
    return -builtin(tokenLen(args), args, envp);
  }

  // Not a builtin function
  pid_t fpid = fork();
  if (fpid < 0) {
    // Failed to fork
    write(STDERR_FILENO, "Failed to fork.\n", 16);
    exit(EXIT_FAILURE);
  }
  else if (fpid == 0) {
    // Child process

    // Change descripors if necessary
    if (indes != -1) {
      dup2(indes, STDIN_FILENO);
      close(indes);
    }
    if (outdes != -1) {
      dup2(outdes, STDOUT_FILENO);
      close(outdes);
    }
    
    // Find command in path
    size_t commandLen = stringlen(args[0]);
    for (char **pathTok = getPathTok(envp); *pathTok != 0; pathTok++) {
      char *curPath = *pathTok;
      size_t curPathLen = stringlen(curPath);
      curPath = realloc(curPath, curPathLen + commandLen + 2);

      curPath[curPathLen] = '/';
      for (int i = 0; i <= commandLen; i++) {
        curPath[curPathLen + i + 1] = args[0][i];
      }

      execve(curPath, args, envp);
    }
    execve(args[0], args, envp);
    write(STDERR_FILENO, "command not found\n", 18);
    exit(EXIT_SUCCESS);
  }
  
  return fpid;
}
