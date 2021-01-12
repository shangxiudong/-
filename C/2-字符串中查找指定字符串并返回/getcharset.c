#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHAR_SET_LEN  128
char *get_charset(const char* buf)
{
    char *p = NULL, *charset = NULL;
    p = strstr(buf, "charset=");
    if(p != NULL) {
        char *q = (char *) malloc (CHAR_SET_LEN);
        charset = q;
        memset(charset, 0, CHAR_SET_LEN);
        for(; *p != '\"' && *p != '\0'; ++p, ++q)
            *q = *p;
        *q = '\0';
    }
    return charset;
}

int main() 
{
    char *p = "uuuudsdfcharset=world";
    char *q = get_charset(p);
    if(q)
        printf("%s\n", q);
    else
        printf("could not find charset\n");
    return 0;
}