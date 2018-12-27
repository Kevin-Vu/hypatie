/* ------------------- */
/* --- util_file.h --- */
/* ------------------- */

#ifndef UTIL_FILE_
#define UTIL_FILE_

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 	256

#define DELETE_EMPTY 	-1

#define TEMP_FILE		((const char *)"doc/tmp.txt")

/* -------------------------------------------------------------------------------------- */
/* --------------------------------------- read ----------------------------------------- */
int countLine(const char * filename);
/* -------------------------------------------------------------------------------------- */
/* ------------------------------------ modify file ------------------------------------- */
void modifyFile(const char * filename, char * newline, int lno);

void replaceLine(FILE * fptr1, FILE * fptr2, char * newline, int lno);
void removeLine(FILE * fptr1, FILE * fptr2, int lno);
void removeEmptyLines(FILE * fptr1, FILE * fptr2);
void insertLine(const char * filename, char * id, char * password, char * account);

#endif // UTIL_FILE_