#include <stdio.h>

union myStruct
{
    short s;
    char cs[2];
};

int main()
{
    union myStruct ms;

    ms.s = 0x0102;

    printf("cs[0] address is :%lld\n", &ms.cs[0]);
    printf("cs[1] address is :%lld\n", &ms.cs[1]);

    if (ms.cs[0] == 0x02)
    {
        printf("little endian!\n");
    }
    else if (ms.cs[0] == 0x01)
    {
        printf("bit endian!\n");
    }
    else
    {
        printf("unknow endian\n");
    }



}
