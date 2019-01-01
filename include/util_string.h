/* ----------------------- */
/* ---- util_string.h ---- */
/* ----------------------- */

#ifndef UTIL_STRING_
#define UTIL_STRING_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

char * randomString(char charset[], size_t size);
char * randomAlphaNum(size_t size);
char * randomAlphaSpecNum(size_t size);
int containSpaces(char * str);
int cstrlen(char * str);

extern char charsetAlphaNum[];
extern char charsetAlphaSpecNum[];

#endif
