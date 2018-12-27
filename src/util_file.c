#include "util_file.h"

/* ------------------------------ */
int countLine(const char * filename)
/* ------------------------------ */
{
    int nbr     = 0;
    char * line = NULL;
    size_t len  = 0;
    FILE * fp = fopen(filename, "r");
    if(fp == NULL)
        return 0;   /* No line read */
    while (getline(&line, &len, fp) != -1) nbr++;
    free(line);
    fclose(fp);
    return nbr;
}
/* --------------------------------------------------------------- */
void replaceLine(FILE * fptr1, FILE * fptr2, char * newline, int lno)
/* --------------------------------------------------------------- */
{
    char str[BUFFER_SIZE];
    int ctr = 0;
    while ((fgets(str, BUFFER_SIZE, fptr1)) != NULL)
    {
        if (ctr == lno)
            fputs(newline, fptr2);
        else
            fputs(str,fptr2);
        ctr++;
    }
}
/* ---------------------------------------------- */
void removeLine(FILE * fptr1, FILE * fptr2, int lno)
/* ---------------------------------------------- */
{
	char str[BUFFER_SIZE];
    int ctr = 0;
    while ((fgets(str, BUFFER_SIZE, fptr1)) != NULL)
    {
        if (ctr != lno)
            fputs(str, fptr2);
        ctr++;
    }
}
/* ------------------------------------------- */
void removeEmptyLines(FILE * fptr1, FILE * fptr2)
/* ------------------------------------------- */
{
    char buffer[BUFFER_SIZE];
    while ((fgets(buffer, BUFFER_SIZE, fptr1)) != NULL)
    {
        /* Cf ASCII table */
        if(buffer[0] >= 41 && buffer[0] <= 126) 
            fputs(buffer, fptr2);
    }
}
/* --------------------------------------------------------- */
void modifyFile(const char * filename, char * newline, int lno)
/* --------------------------------------------------------- */
{
    FILE * fptr1 = fopen(filename, "r");
    FILE * fptr2 = fopen(TEMP_FILE, "w+");   
    
    if(fptr1 == NULL)
    {
        fprintf(stderr, "ERROR : %s No such file \n",filename);
        fclose(fptr2);
        remove(TEMP_FILE);
        return;
    }
    
    /* Select the action to perform */
    if(newline == NULL && lno != DELETE_EMPTY)
        removeLine(fptr1, fptr2, lno);
    else if(newline == NULL && lno == DELETE_EMPTY)
        removeEmptyLines(fptr1, fptr2);
    else
        replaceLine(fptr1, fptr2, newline, lno);

    fclose(fptr1);
    fclose(fptr2);
    remove(filename);
    rename(TEMP_FILE, filename);
}

/* ---------------------------------------------------------------------------- */
void insertLine(const char * filename, char * id, char * password, char * account)
/* ---------------------------------------------------------------------------- */
{
	FILE * fp = fopen(filename, "a");
    if(fp == NULL) return;
    char newline[BUFFER_SIZE];
    sprintf(newline, "%s %s %s", id, password, account);
	fprintf(fp, "\n%s", newline);
	fclose(fp);
}