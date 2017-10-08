#ifndef SHELLLAB_SHELL_H
#define SHELLLAB_SHELL_H

#include <sys/types.h>

void shellLoop(char *envp[]);
void shellExec(char **commands, char *envp[]);
pid_t shellCommandExec(char **args, char *envp[], int indes, int outdes);

#endif // SHELLLAB_SHELL_H
