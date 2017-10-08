#ifndef SHELLLAB_BUILTIIN_H
#define SHELLLAB_BUILTIIN_H

/* A builtin function takes in the same arguments as main. */
typedef int (*BuiltinFunc)(int, char **, char **);

/* Searches builtin command vector for command matching the string commandName.
 * If a matching command is found, a function that excecutes that command is
 * returned. If no matching command is found, NULL is returned instead. */
BuiltinFunc getBuiltinFunc(char *commandName);

#endif
