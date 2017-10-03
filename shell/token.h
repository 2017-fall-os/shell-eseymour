#ifndef SHELLLAB_TOKEN_H
#define SHELLLAB_TOKEN_H

#include <stddef.h>

/* Tokenizes the str delimited by delim. Returns a zero terminated token vector
 * of strings. */
char ** tokenize(const char *str, char delim);

/* Computes the number of tokens in the given string */
size_t strNumTokens(const char *str, char delim);

/* Computes the length of the token starting at str */
size_t strTokenLen(const char *str, char delim);

/* Computes the length of the token */
size_t tokenLen(char **tok);

/* Copies the characters of the token starting at delim */
char * tokenCpy(char *dest, const char *src, char delim);

/* Compares two token vectors returning 0 if they are the same */
int tokenCmp(char **tok1, char** tok2);

/* Frees the token vector */
void tokenFree(char **tok);

#endif // SHELLLAB_TOKEN_H
