#include <stdio.h>
#include <string.h>

unsigned long my_strlen(const char *buf, unsigned long max_size)
{
    unsigned long len;
    const char *p = buf + max_size -1;
    for(len = max_size; *p == '\0'; --p, --len)
        printf("*p == 0\n");
    return len;
}

int main()
{
    char *p = "hello";
    int len = my_strlen(p,6);
    printf("buf len is : %d\n", len);
    printf("strlen(buf) is : %d\n", strlen(p));
    return 0;
}