#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fun()
{
    printf("%d", strlen("13654914070187343873.uadd.0.123.2400101234001*"));

    char* str = "13654914070187343873.uadd.0.123.2400101234001";
    char* msg = malloc(45);

    memcpy(msg, str, strlen(str));

    printf("%s:%d\n", msg, strlen(msg));
}

int main()
{
    printf("%u\n", strlen("12345"));

    char buf[] = "12345";

    printf("%u %d\n", strlen(buf), sizeof(buf));
}
