#ifndef SHELLLAB_SHELL_H
#define SHELLLAB_SHELL_H

void shellLoop(char *envp[]);
int shellExec(char **tokens, char *envp[]);

#endif // SHELLLAB_SHELL_H
