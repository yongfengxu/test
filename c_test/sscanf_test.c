#include <stdio.h>
#include <string.h>
#include <stdint.h>

void test1()
{
    int pn, bn, dn;
    int count = sscanf("1d/2/3/", "%d/%d/%d", &pn, &bn, &dn);

    if (count != 3)
    {
        printf("something error\n");
    }
    else
    {
        printf("pn:%d, bn:%d, dn:%d\n", pn, bn ,dn);
    }
}

void test2()
{
    int id;

    int count = sscanf("12", "%d", &id);

    if (count == 1)
    {
        printf("id = %d\n", id);
    }
    else
    {
        printf("something error\n");
    }
}

int main()
{
    uint8_t addr[6];
    int count = sscanf("A1A2A3A4A5A6", "%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx", &addr[0], &addr[1], &addr[2], &addr[3], &addr[4], &addr[5]);

    printf("%x:%x:%x:%x:%x:%x\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
}
