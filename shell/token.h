#ifndef SHELLLAB_TOKEN_H
#define SHELLLAB_TOKEN_H

#include <stddef.h>

/* Tokenizes the str delimited by delim. Returns a zero terminated token vector
 * of strings. */
char ** mytok(const char *str, char delim);

/* Computes the number of tokens in the given string */
size_t numtok(const char *str, char delim);

/* Computes the length of the token starting at str */
size_t toklen(const char *str, char delim);

/* Copies the characters of the token starting at delim */
char * tokcpy(char *dest, const char *src, char delim);

/* Compares two token vectors returning 0 if they are the same */
int tokcmp(char **tok1, char** tok2);

/* Frees the token vector */
void freetok(char **tok);

#endif // TOKENIZERLAB_TOKEN_H
