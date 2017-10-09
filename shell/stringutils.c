#include "stringutils.h"

/* Copy at most n characters of string src to dest; return dest. Pad with '\0'
   if src has fewer than n characters. */
char * stringncpy(char *dest, const char *src, size_t n) {
  size_t i;

  // Copy src into dest
  for (i = 0; i < n && src[i] != '\0'; ++i) {
    dest[i] = src[i];
  }

  // Pad rest of dest with '\0'
  for (; i < n; ++i) {
    dest[i] = '\0';
  }

  return dest;
}

/* Concatenate string src to the end of string dest; return dest. */
char * stringcat(char *dest, const char *src) {
  size_t i;
  size_t destLen = stringlen(dest);

  // Concatenate src
  for (i = 0; src[i] != '\0'; ++i) {
    dest[destLen + i] = src[i];
  }

  // Terminate string
  dest[destLen+i] = '\0';

  return dest;
}

/* Compare str1 to str2; return < 0 if str1 < str2, 0 if str1 == str2 or > 0 if
   str1 > str2. */
int stringcmp(const char *str1, const char *str2) {
  size_t i;

  // Seek until different char or end of string
  for (i = 0; str1[i] == str2[i] && str1[i] != '\0'; i++);

  return str1[i] - str2[i];
}

/* Return length of str */
size_t stringlen(const char *str) {
  size_t length = 0;

  while (*str != '\0') {
    ++str;
    ++length;
  }

  return length;
}
