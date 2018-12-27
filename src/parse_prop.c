#include "parse_prop.h"

/* --------------------- */
P_PROP * P_PROParray(int n)
/* --------------------- */
{
    P_PROP * p = malloc(n * sizeof(PROP));
    for(int i = 0; i < n; i++) p[i] = malloc(sizeof(PROP));
    return p; 
}
/* ---------------------------------- */
void free_P_PROParray(P_PROP * p, int n)
/* ---------------------------------- */
{
    for(int i = 0; i < n; i++) free(p[i]);
    free(p);
}
/* --------------------------------------------- */
P_PROP * file_to_P_PROParray(char const * filename)
/* --------------------------------------------- */
{
    char * token = NULL;
    char * line  = NULL;
    size_t len   = 0;

    int nbLine = countLine(filename);
    P_PROP * p = P_PROParray(nbLine);

    FILE * fp = fopen(filename, "r");
    if(fp == NULL)
    {
        free_P_PROParray(p, nbLine);
        return NULL;
    }
    int i = 0;
    while (getline(&line, &len, fp) != -1) {
        token = strtok(line, " ");
        strcpy(p[i] -> key, token);
        token = strtok(NULL, " ");
        strcpy(p[i] -> value , token);
        token = strtok(NULL, " ");
        token[strcspn(token, "\n")] = '\0';
        strcpy(p[i] -> email , token);
        i++;
    }
    free(line);
    fclose(fp);

    return p;
}
/* ------------------------------------------- */
P_CONT getContent(P_PROP *p, int length, int lno)
/* ------------------------------------------- */
{
    if(lno > length - 1 || lno < 0 || length == 0)
        return NULL;
    P_CONT cont = malloc(sizeof(CONT));
    strcpy(cont -> value , p[lno] -> value);
    strcpy(cont -> email , p[lno] -> email);
    return cont;
}
/* ------------------------------------ */
void displayArrayP_PROP(P_PROP * p, int l)
/* ------------------------------------ */
{
	for(int i = 0; i < l; i++) 
		printf("key : %s - value : %s - email : %s \n", 
			   p[i] -> key, p[i] -> value, p[i] -> email );
}
/* ---------------------------------- */
void displayKeyP_PROP(P_PROP * p, int l)
/* ---------------------------------- */
{
    for(int i = 0; i < l; i++) 
        printf("| %-25.25s | %-25.25s | [%3d]  |\n", p[i] -> key, p[i] -> email, i);
}