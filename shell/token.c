// Edward Seymour 2017
#include "token.h"

#include <assert.h> // for assert
#include <stdbool.h> // for false
#include <stdlib.h> // for free

/* Tokenizes the str delimited by delim. Returns a zero terminated array
 * of token strings. */
 char ** mytok(const char *str, char delim) {
  // First pass: calculate the number of tokens.
  size_t numTokens = numtok(str, delim);

  char **tokens = (char **)calloc(numTokens + 1, sizeof(char *));

  // Second pass: add each token to tokens.
  for (int i = 0; i < numTokens; ++i) {
    // Find start of token
    for (; *str == delim; ++str);

    size_t tokenLength = toklen(str, delim);
    char *token = (char *)calloc(tokenLength + 1, 1);
    tokcpy(token, str, delim);

    tokens[i] = token;

    // Jump one element past end of token
    str += tokenLength;
  }

  // No tokens should be left
  #ifndef NDEBUG
  // Skip past any remaining delimiters
  for (; *str == delim; ++str);

  assert(*str == '\0');
  #endif // NDEBUG

  return tokens;
}

/* Computes the number of tokens in the given string */
size_t numtok(const char *str, char delim) {
  size_t numTokens = 0;

  for (int inToken = false; *str != '\0'; ++str) {
    if (*str != delim && !inToken) {
      // Found beginning of token
      ++numTokens;
    }

    inToken = *str != delim;
  }

  return numTokens;
}

/* Computes the length of the token starting at str */
size_t toklen(const char *str, char delim) {
  assert(*str != delim && *str != '\0');

  size_t tokenLength = 0;
  for (; *str != '\0' && *str != delim; ++str) {
    ++tokenLength;
  }

  return tokenLength;
}

/* Copies the characters of the token starting at delim */
char * tokcpy(char *dest, const char *src, char delim) {
  assert(*src != delim && *src != '\0');

  char *destCursor = dest;
  for (; *src != '\0' && *src != delim; ++src, ++destCursor) {
    *destCursor = *src;
  }

  // Null-terminate string
  *(destCursor) = '\0';

  return dest;
}

/* Compares two token vectors returning 0 if they are the same */
int tokcmp(char **tok1, char** tok2) {
  for (; *tok1 != 0 && *tok2 != 0; ++tok1, ++tok2) {
    const char *str1 = *tok1;
    const char *str2 = *tok2;

    for (; *str1 != 0 && *str2 != 0; ++str1, ++str2) {
      if (*str1 != *str2) {
        return *str1 - *str2;
      }
    }
    if (*str1 != *str2) {
      return *str1 - *str2;
    }
  }

  return  *tok1 == *tok2 ? 0 : *tok1 < *tok2 ? -1 : 1;
}

/* Frees the token vector */
void freetok(char **tok) {
  // Free token strings in vector
  for (char **tokCursor = tok; *tokCursor != 0; ++tokCursor) {
    free(*tokCursor);
  }

  free(tok);
}
