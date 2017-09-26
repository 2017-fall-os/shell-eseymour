#ifndef SHELLLAB_STRINGUTILS_H
#define SHELLLAB_STRINGUTILS_H

#include <stddef.h>

/* Copy at most n characters of string src to dest; return dest. Pad with '\0'
   if src has fewer than n characters. */
char * stringncpy(char *dest, const char *src, size_t n);

/* Concatenate string src to the end of string dest; return dest. */
char * stringcat(char *dest, const char *src);

/* Compare str1 to str2; return < 0 if str1 < str2, 0 if str1 == str2 or > 0 if
   str1 > str2. */
int stringcmp(const char *str1, const char *str2);

/* Return length of str */
size_t stringlen(const char *str);


#endif // SHELLLAB_STRINGUTILS_H
