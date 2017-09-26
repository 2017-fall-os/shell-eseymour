#include "stringutils.h"

/* Copy at most n characters of string src to dest; return dest. Pad with '\0'
   if src has fewer than n characters. */
char * stringncpy(char *dest, const char *src, size_t n) {
  char *curChar = dest;

  // Copy src into dest
  while (n > 0 && *src != '\0') {
    *curChar = *src;

    ++curChar;
    ++src;
    --n;
  }

  // Pad rest of dest with '\0'
  while (n > 0) {
    *curChar = '\0';

    --n;
  }

  return dest;
}

/* Concatenate string src to the end of string dest; return dest. */
char * stringcat(char *dest, const char *src) {
  char *curChar = dest;

  // Seek to end of dest
  while (*curChar != '\0') {
    ++curChar;
  }

  // Concatenate src
  while (*src != '\0') {
    *curChar = *src;
    ++curChar;
    ++src;
  }

  // Terminate string
  *curChar = '\0';

  return dest;
}

/* Compare str1 to str2; return < 0 if str1 < str2, 0 if str1 == str2 or > 0 if
   str1 > str2. */
int stringcmp(const char *str1, const char *str2) {
  while (*str1 == *str2 && *str1 != '\0') {
    ++str1;
    ++str2;
  }

  return *str1 - *str2;
}

/* Return length of str */
size_t stringlen(const char *str) {
  int length = 0;

  while (*str != '\0') {
    ++str;
    ++length;
  }

  return length;
}
