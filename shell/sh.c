#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "token.h"

#define BUFLEN 4096
char buffer[BUFLEN];

char *exitTok[] = {"exit", (char *) 0};
char *nullTok[] = {(char *) 0};

int main(int argc, char *argv[], char *envp[]) {
  for (int keepLooping = 1; keepLooping;) {
    write(STDOUT_FILENO, "$ ", 2);
    size_t bufRead = read(STDIN_FILENO, buffer, BUFLEN);
    buffer[bufRead - 1] = '\0';

    char **tokens = mytok(buffer, ' ');

    keepLooping = tokcmp(exitTok, tokens);

    if (keepLooping && tokcmp(tokens, nullTok) != 0) {
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

    freetok(tokens);
  }
}
