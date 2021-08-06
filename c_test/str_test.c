#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    char str[100];
    memset(str, 0, sizeof(str)/sizeof(char));

    char copy[] = "hello world!";

    printf("length: %d, sizeof(copy): %d\n", strlen(copy), sizeof(copy));

    //strncpy(str, copy, sizeof(copy));
    strncpy(str, copy, strlen(copy));
    str[strlen(copy)+1] = '\0';

    printf("str: ==%s==\n", str);

    u_int64_t id = strtoull("310012241094379", NULL, 0);

    printf("id is %ld\n", id);
}
