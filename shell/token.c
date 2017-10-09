// Edward Seymour 2017
#include "token.h"

#include <stdbool.h> // for bool, false
#include <stdlib.h> // for free

#include "stringutils.h"

/* Tokenizes the str delimited by delim. Returns a zero terminated array
 * of token strings. */
char ** tokenize(const char *str, char delim) {
  // First pass: calculate the number of tokens.
  size_t numTokens = strNumTokens(str, delim);

  char **tokens = (char **)calloc(numTokens + 1, sizeof(char *));

  // Second pass: add each token to tokens.
  for (int i = 0; i < numTokens; ++i) {
    // Find start of token
    for (; *str == delim; ++str);

    size_t tokenLength = strTokenLen(str, delim);
    char *token = (char *)calloc(tokenLength + 1, 1);
    tokenCpy(token, str, delim);

    tokens[i] = token;

    // Jump one element past end of token
    str += tokenLength;
  }

  return tokens;
}

/* Computes the number of tokens in the given string */
size_t strNumTokens(const char *str, char delim) {
  size_t count = 0;

  for (bool inToken = false; *str != '\0'; ++str) {
    if (*str != delim && !inToken) {
      // Found beginning of token
      ++count;
    }

    inToken = *str != delim;
  }

  return count;
}

/* Computes the length of the token */
size_t numTokens(char **tok) {
  size_t count = 0;

  for (size_t i = 0; tok[i] != NULL; ++i) {
    ++count;
  }

  return count;
}

/* Computes the length of the token starting at str */
size_t strTokenLen(const char *str, char delim) {
  size_t tokenLength = 0;

  for (size_t i = 0; str[i] != '\0' && str[i] != delim; ++i) {
    ++tokenLength;
  }

  return tokenLength;
}

/* Copies the characters of the token starting at delim */
char * tokenCpy(char *dest, const char *src, char delim) {
  size_t i;

  for (i = 0; src[i] != '\0' && src[i] != delim; ++i) {
    dest[i] = src[i];
  }

  // Null-terminate string
  dest[i] = '\0';

  return dest;
}

/* Computes the length of the token */
size_t tokenLen(char **tok) {
  size_t length = 0;

  for (size_t i = 0; tok[i] != NULL; ++i) {
    ++length;
  }

  return length;
}

/* Compares two token vectors returning 0 if they are the same */
int tokenCmp(char **tok1, char** tok2) {
  for (; *tok1 != 0 && *tok2 != 0; ++tok1, ++tok2) {
    int result = stringcmp(*tok1, *tok2);
    if (result != 0) return result;
  }

  return  *tok1 == *tok2 ? 0 : *tok1 < *tok2 ? -1 : 1;
}

/* Frees the token vector */
void tokenFree(char **tok) {
  // Free token strings in vector
  for (size_t i = 0; tok[i] != NULL; ++i) {
    free(tok[i]);
  }

  free(tok);
}
