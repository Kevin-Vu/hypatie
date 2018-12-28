/* --------------------------------------------------------------------------------------------------------- */
/* Adapted from :                                                                                            */
/* Source : William Morris https://codereview.stackexchange.com/questions/29198/random-string-generator-in-c */
/* --------------------------------------------------------------------------------------------------------- */
#include "util_string.h"

char charsetAlphaNum[]     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
char charsetAlphaSpecNum[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!\"#$%&'()*+-./,:;<=>?@[\\]^_`{|}~";
/* ----------------------------------------- */
char* randomString(char charset[], size_t size)
/* ----------------------------------------- */
{
    srand(time(NULL));
    char buf[1024];
    sprintf(buf, "%s", charset);
    size_t n = 0;
    char * str = malloc(size * sizeof(char) + 1);
    size++;
    if (size) {
        --size;
        for (n = 0; n < size; n++) {
            int key = rand() % strlen(buf);
            str[n] = buf[key];
        } 
        str[size] = '\0';
    }
    return str;
}
/* ---------------------------- */
char * randomAlphaNum(size_t size)
/* ---------------------------- */
{
    return randomString(charsetAlphaNum, size);
}
/* -------------------------------- */
char * randomAlphaSpecNum(size_t size)
/* -------------------------------- */
{
    return randomString(charsetAlphaSpecNum, size);
}

