#ifndef SHELLLAB_BUILTIIN_H
#define SHELLLAB_BUILTIIN_H

typedef struct {
  char *commandName;
  int (*commandFunc)(int, char **, char **);
} Command;

extern Command builtins[];

#endif
