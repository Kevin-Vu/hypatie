#include "parse_prop.h"

/* --------------------- */
P_PROP * P_PROParray(int n)
/* --------------------- */
{
    int i = 0;
    P_PROP * p = malloc(n * sizeof(PROP));
    for(i = 0; i < n; i++) p[i] = malloc(sizeof(PROP));
    return p; 
}
/* ---------------------------------- */
void free_P_PROParray(P_PROP * p, int n)
/* ---------------------------------- */
{
    int i = 0;
    for(i = 0; i < n; i++) free(p[i]);
    free(p);
}
/* --------------------------------------------- */
P_PROP * file_to_P_PROParray(char const * filename)
/* --------------------------------------------- */
{
    char * line = NULL;
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
    for(i = 0; i < nbLine; i++)
    {
        if(getline(&line, &len, fp) != -1)
            sscanf(line, "%s %s %s",p[i] -> key, p[i] -> value, p[i] -> email);
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
    sscanf(p[lno] -> value, "%s", cont -> value);
    sscanf(p[lno] -> email, "%s", cont -> email);
    return cont;
}
/* ------------------------------------ */
void displayArrayP_PROP(P_PROP * p, int l)
/* ------------------------------------ */
{
    int i = 0;
	for(i = 0; i < l; i++) 
		printf("key : %s - value : %s - email : %s \n", 
			   p[i] -> key, p[i] -> value, p[i] -> email );
}
/* ---------------------------------- */
void displayKeyP_PROP(P_PROP * p, int l)
/* ---------------------------------- */
{
    int i = 0;
    for(i = 0; i < l; i++) 
    {
        if(cstrlen(p[i] -> email) > 30 && cstrlen(p[i] -> key) > 30)
            printf("| %-22.22s... | %-27.27s... | [%3d]  |\n", p[i] -> key, p[i] -> email, i);
        else if(cstrlen(p[i] -> email) > 30 && cstrlen(p[i] -> key) <= 30)
            printf("| %-25.25s | %-27.27s... | [%3d]  |\n", p[i] -> key, p[i] -> email, i);
        else if(cstrlen(p[i] -> email) <=30 && cstrlen(p[i] -> key) > 30)
            printf("| %-22.22s... | %-30.30s... | [%3d]  |\n", p[i] -> key, p[i] -> email, i);
        else
            printf("| %-25.25s | %-30.30s | [%3d]  |\n", p[i] -> key, p[i] -> email, i);
    }
}
